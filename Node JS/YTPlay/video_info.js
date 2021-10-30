const utils = require('./utils');
const FORMATS = require('./formats');

// Use these to help sort formats, higher index is better.
const audioEncodingRanks = [
    'mp4a',
    'mp3',
    'vorbis',
    'aac',
    'opus',
    'flac',
];
const videoEncodingRanks = [
    'mp4v',
    'avc1',
    'Sorenson H.283',
    'MPEG-4 Visual',
    'VP8',
    'VP9',
    'H.264',
];


const parseTimestamp = time => {
    let a = time.split(':'); // split it at the colons
    // minutes are worth 60 seconds. Hours are worth 60 minutes.
    return (+a[0]) * 60 * 60 + (+a[1]) * 60 + (+a[2]);
}

const getText = obj => obj ? obj.runs ? obj.runs[0].text : obj.simpleText : null;
const isVerified = badges => !!(badges && badges.find(b => b.metadataBadgeRenderer.tooltip === 'Verified'));

/**
 * Sort formats by a list of functions.
 *
 * @param {Object} a
 * @param {Object} b
 * @param {Array.<Function>} sortBy
 * @returns {number}
 */
const sortFormatsBy = (a, b, sortBy) => {
    let res = 0;
    for (let fn of sortBy) {
        res = fn(b) - fn(a);
        if (res !== 0) {
            break;
        }
    }
    return res;
};

const getVideoBitrate = format => format.bitrate || 0;
const getVideoEncodingRank = format =>
    videoEncodingRanks.findIndex(enc => format.codecs && format.codecs.includes(enc));
const getAudioBitrate = format => format.audioBitrate || 0;
const getAudioEncodingRank = format =>
    audioEncodingRanks.findIndex(enc => format.codecs && format.codecs.includes(enc));

const sortFormatsByVideo = (a, b) => sortFormatsBy(a, b, [
    format => parseInt(format.qualityLabel),
    getVideoBitrate,
    getVideoEncodingRank,
]);

const sortFormatsByAudio = (a, b) => sortFormatsBy(a, b, [
    getAudioBitrate,
    getAudioEncodingRank,
]);

/**
 * Gets related videos
 *
 * @param {Object} details
 * @param {Object} rvsParams
 * @returns {Object}
 */
const parseRelatedVideo = (details, rvsParams) => {
    if (!details) return;
    try {
        let viewCount = getText(details.viewCountText);
        let shortViewCount = getText(details.shortViewCountText);
        let rvsDetails = rvsParams.find(elem => elem.id === details.videoId);
        if (!/^\d/.test(shortViewCount)) {
            shortViewCount = (rvsDetails && rvsDetails.short_view_count_text) || '';
        }
        viewCount = (/^\d/.test(viewCount) ? viewCount : shortViewCount).split(' ')[0];
        let browseEndpoint = details.shortBylineText.runs[0].navigationEndpoint.browseEndpoint;
        let channelId = browseEndpoint.browseId;
        let name = getText(details.shortBylineText);
        let user = (browseEndpoint.canonicalBaseUrl || '').split('/').slice(-1)[0];
        let video = {
            id: details.videoId,
            title: getText(details.title),
            published: getText(details.publishedTimeText),
            author: {
                id: channelId,
                name,
                user,
                channel_url: `https://www.youtube.com/channel/${channelId}`,
                user_url: `https://www.youtube.com/user/${user}`,
                thumbnails: details.channelThumbnail.thumbnails.map(thumbnail => {
                    thumbnail.url = new URL(thumbnail.url, utils.BASE_URL).toString();
                    return thumbnail;
                }),
                verified: isVerified(details.ownerBadges),
            },
            short_view_count_text: shortViewCount.split(' ')[0],
            view_count: viewCount.replace(/,/g, ''),
            length_seconds: details.lengthText ? parseTimestamp(getText(details.lengthText)) : rvsParams && `${rvsParams.length_seconds}`,
            thumbnails: details.thumbnail.thumbnails,
            richThumbnails: details.richThumbnail ?
                details.richThumbnail.movingThumbnailRenderer.movingThumbnailDetails.thumbnails : [],
            isLive: !!(details.badges && details.badges.find(b => b.metadataBadgeRenderer.label === 'LIVE NOW')),
        };
        return video;
    } catch (err) {
        // Skip.
    }
};


exports.getRelatedVideos = info => {
    let rvsParams = [],
        secondaryResults = [];
    try {
        rvsParams = info.initData.webWatchNextResponseExtensionData.relatedVideoArgs.split(',').map(e => qs.parse(e));
    } catch (err) {
        // Do nothing.
    }
    try {
        secondaryResults = info.initData.contents.twoColumnWatchNextResults.secondaryResults.secondaryResults.results;
    } catch (err) {
        return [];
    }
    let videos = [];
    for (let result of secondaryResults || []) {
        let details = result.compactVideoRenderer;
        if (details) {
            let video = parseRelatedVideo(details, rvsParams);
            if (video) videos.push(video);
            // } else {
            //   let autoplay = result.compactAutoplayRenderer || result.itemSectionRenderer;
            //   if (!autoplay || !Array.isArray(autoplay.contents)) continue;
            //   for (let content of autoplay.contents) {
            //     let video = parseRelatedVideo(content.compactVideoRenderer, rvsParams);
            //     if (video) videos.push(video);
            //   }
        }
    }
    return videos;
};

//Format stuff

/**
 * @param {Object} format
 * @returns {Object}
 */
exports.addFormatMeta = format => {
    format = Object.assign({}, FORMATS[format.itag], format);
    format.hasVideo = !!format.qualityLabel;
    format.hasAudio = !!format.audioBitrate;
    format.container = format.mimeType ?
        format.mimeType.split(';')[0].split('/')[1] : null;
    format.codecs = format.mimeType ?
        utils.between(format.mimeType, 'codecs="', '"') : null;
    format.videoCodec = format.hasVideo && format.codecs ?
        format.codecs.split(', ')[0] : null;
    format.audioCodec = format.hasAudio && format.codecs ?
        format.codecs.split(', ').slice(-1)[0] : null;
    format.isLive = /\bsource[/=]yt_live_broadcast\b/.test(format.url);
    format.isHLS = /\/manifest\/hls_(variant|playlist)\//.test(format.url);
    format.isDashMPD = /\/manifest\/dash\//.test(format.url);
    return format;
};

/**
 * @param {Object} playerRes
 * @returns {Array.<Object>}
 */
exports.parseFormats = playerRes => {
    let formats = [];
    if (playerRes && playerRes.streamingData) {
        formats = formats
            .concat(playerRes.streamingData.formats || [])
            .concat(playerRes.streamingData.adaptiveFormats || []);
    }
    return formats;
};

/**
 * Choose a format depending on the given options.
 *
 * @param {Array.<Object>} formats
 * @param {Object} options
 * @returns {Object}
 * @throws {Error} when no format matches the filter/format rules
 */
exports.chooseFormat = (formats, options) => {
    if (typeof options.format === 'object') {
        if (!options.format.url) {
            throw Error('Invalid format given, did you use `ytdl.getInfo()`?');
        }
        return options.format;
    }

    if (options.filter) {
        formats = exports.filterFormats(formats, options.filter);
    }

    // We currently only support HLS-Formats for livestreams
    // So we (now) remove all non-HLS streams
    if (formats.some(fmt => fmt.isHLS)) {
        formats = formats.filter(fmt => fmt.isHLS || !fmt.isLive);
    }

    let format;
    const quality = options.quality || 'highestaudio';
    switch (quality) {
        case 'highest':
            format = formats[0];
            break;

        case 'lowest':
            format = formats[formats.length - 1];
            break;

        case 'highestaudio': {
            formats = exports.filterFormats(formats, 'audio');
            formats.sort(sortFormatsByAudio);
            // Filter for only the best audio format
            const bestAudioFormat = formats[0];
            formats = formats.filter(f => sortFormatsByAudio(bestAudioFormat, f) === 0);
            // Check for the worst video quality for the best audio quality and pick according
            // This does not loose default sorting of video encoding and bitrate
            const worstVideoQuality = formats.map(f => parseInt(f.qualityLabel) || 0).sort((a, b) => a - b)[0];
            format = formats.find(f => (parseInt(f.qualityLabel) || 0) === worstVideoQuality);
            break;
        }

        case 'lowestaudio':
            formats = exports.filterFormats(formats, 'audio');
            formats.sort(sortFormatsByAudio);
            format = formats[formats.length - 1];
            break;

        case 'highestvideo': {
            formats = exports.filterFormats(formats, 'video');
            formats.sort(sortFormatsByVideo);
            // Filter for only the best video format
            const bestVideoFormat = formats[0];
            formats = formats.filter(f => sortFormatsByVideo(bestVideoFormat, f) === 0);
            // Check for the worst audio quality for the best video quality and pick according
            // This does not loose default sorting of audio encoding and bitrate
            const worstAudioQuality = formats.map(f => f.audioBitrate || 0).sort((a, b) => a - b)[0];
            format = formats.find(f => (f.audioBitrate || 0) === worstAudioQuality);
            break;
        }

        case 'lowestvideo':
            formats = exports.filterFormats(formats, 'video');
            formats.sort(sortFormatsByVideo);
            format = formats[formats.length - 1];
            break;

        default:
            format = getFormatByQuality(quality, formats);
            break;
    }

    if (!format) {
        throw Error(`No such format found: ${quality}`);
    }
    return format;
};

/**
 * @param {Array.<Object>} formats
 * @param {Function} filter
 * @returns {Array.<Object>}
 */
exports.filterFormats = (formats, filter) => {
    let fn;
    switch (filter) {
        case 'videoandaudio':
        case 'audioandvideo':
            fn = format => format.hasVideo && format.hasAudio;
            break;

        case 'video':
            fn = format => format.hasVideo;
            break;

        case 'videoonly':
            fn = format => format.hasVideo && !format.hasAudio;
            break;

        case 'audio':
            fn = format => format.hasAudio;
            break;

        case 'audioonly':
            fn = format => !format.hasVideo && format.hasAudio;
            break;

        default:
            if (typeof filter === 'function') {
                fn = filter;
            } else {
                throw TypeError(`Given filter (${filter}) is not supported`);
            }
    }
    return formats.filter(format => !!format.url && fn(format));
};
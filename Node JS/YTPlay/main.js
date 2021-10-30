// native Node.js module
const decipher = require("./decipher");
const JSON_Search = require("./JSON_search");
const video_info = require("./video_info");
const html_fetch = require("./html_fetch");
const utils = require("./utils");
const PassThrough = require("stream").PassThrough;

//I am too lazy to keep this just use m3u8stream
//npm install miniget
const miniget = require('miniget');


//YTplay
const createStream = (options) => {
    const stream = new PassThrough({
        highWaterMark: (options && options.highWaterMark) || 1024 * 512,
    });
    stream._destroy = () => {
        stream.destroyed = true;
    };
    return stream;
};


const pipeAndSetEvents = (req, stream, end) => {
    // Forward events from the request to the stream.
    [
        'abort', 'request', 'response', 'error', 'redirect', 'retry', 'reconnect',
    ].forEach(event => {
        req.prependListener(event, stream.emit.bind(stream, event));
    });
    req.pipe(stream, {
        end
    });
};

/**
 * @param {string} link
 * @param {!Object} options
 * @returns {ReadableStream}
 */
const ytplay = (link, options) => {
    const stream = createStream(options);
    ytplay.getInfo(link, options).then((info) => {
        downloadFromInfoCallback(stream, info, options);
    }, stream.emit.bind(stream, "error"));
    return stream;
};

ytplay.getInfo = async (url) => {
    let html = await html_fetch.fetch("GET", url);
    let info = {
        html5Res: utils.getHTML5player(html),
        playerRes: JSON_Search.findJSON(
            "watch.html",
            "player_response",
            html,
            utils.regx.playerRes,
            "</script>",
            "{"
        ),
        initData: JSON_Search.findJSON(
            "watch.html",
            "response",
            html,
            utils.regx.InitialData,
            "</script>",
            "{"
        ),
    };

    Object.assign(info, {
        formats: video_info.parseFormats(info.playerRes),
        related_videos: video_info.getRelatedVideos(info),
        base_url: url,
    });

    //move up some important things for easy access
    info.videoDetails = info.playerRes.videoDetails;
    info.videoDetails.thumbnail = info.videoDetails.thumbnail.thumbnails;
    delete info.playerRes.videoDetails;

    //decriph
    let funcs = [];
    if (info.formats.length) {
        if (!info.html5Res) {
            throw Error("Unable to find html5player file");
        }
        const html5player = new URL(info.html5Res, utils.BASE_URL).toString();
        funcs.push(decipher.Formats(info.formats, html5player));
    }

    //
    let results = await Promise.all(funcs);
    info.formats = Object.values(Object.assign({}, ...results));
    info.formats = info.formats.map(video_info.addFormatMeta);
    info.formats.sort(video_info.sortFormats);
    info.full = true;
    return info;
};
let url = "https://www.youtube.com/watch?v=NkFCliab274";
let options = {
    filter: "audioonly"
}
ytplay.getInfo(url);
ytplay(url, options)



/**
 * Chooses a format to download.
 *
 * @param {stream.Readable} stream
 * @param {Object} info
 * @param {Object} options
 */
const downloadFromInfoCallback = (stream, info, options) => {
    options = options || {};
    let err = utils.playError(info.player_response, [
        "UNPLAYABLE",
        "LIVE_STREAM_OFFLINE",
        "LOGIN_REQUIRED",
    ]);

    if (err) {
        stream.emit("error", err);
        return;
    }

    if (!info.formats.length) {
        stream.emit("error", Error("This video is unavailable"));
        return;
    }

    let format;
    try {
        format = video_info.chooseFormat(info.formats, options);
    } catch (e) {
        stream.emit("error", e);
        return;
    }
    stream.emit("info", info, format);
    if (stream.destroyed) {
        return;
    }

    let contentLength,downloaded = 0;
    const ondata = (chunk) => {
        downloaded += chunk.length;
        stream.emit("progress", chunk.length, downloaded, contentLength);
    };

    // Download the file in chunks, in this case the default is 10MB,
    // anything over this will cause youtube to throttle the download
    const dlChunkSize = options.dlChunkSize || 1024 * 1024 * 10;
    let req;
    let shouldEnd = true;


    const requestOptions = Object.assign({}, options.requestOptions, {
        maxReconnects: 6,
        maxRetries: 3,
        backoff: { inc: 500, max: 10000 },
      });
  
      let shouldBeChunked = dlChunkSize !== 0 && (!format.hasAudio || !format.hasVideo);
  
      if (shouldBeChunked) {
        let start = (options.range && options.range.start) || 0;
        let end = start + dlChunkSize;
        const rangeEnd = options.range && options.range.end;
  
        contentLength = options.range ?
          (rangeEnd ? rangeEnd + 1 : parseInt(format.contentLength)) - start :
          parseInt(format.contentLength);
  
        const getNextChunk = () => {
          if (!rangeEnd && end >= contentLength) end = 0;
          if (rangeEnd && end > rangeEnd) end = rangeEnd;
          shouldEnd = !end || end === rangeEnd;
  
          requestOptions.headers = Object.assign({}, requestOptions.headers, {
            Range: `bytes=${start}-${end || ''}`,
          });
  
          req = miniget(format.url, requestOptions);
          req.on('data', ondata);
          req.on('end', () => {
            if (stream.destroyed) { return; }
            if (end && end !== rangeEnd) {
              start = end + 1;
              end += dlChunkSize;
              getNextChunk();
            }
          });
          pipeAndSetEvents(req, stream, shouldEnd);
        };
        getNextChunk();
    } else {
        // Audio only and video only formats don't support begin
        if (options.begin) {
            format.url += `&begin=${parseTimestamp(options.begin)}`;
        }
        if (options.range && (options.range.start || options.range.end)) {
            requestOptions.headers = Object.assign({}, requestOptions.headers, {
                Range: `bytes=${options.range.start || "0"}-${
            options.range.end || ""
          }`,
            });
        }
        req = miniget(format.url, requestOptions);
        req.on("response", (res) => {
            if (stream.destroyed) {
                return;
            }
            contentLength =
                contentLength || parseInt(res.headers["content-length"]);
        });
        req.on("data", ondata);
        pipeAndSetEvents(req, stream, shouldEnd);
    }


    stream._destroy = () => {
        stream.destroyed = true;
        req.destroy();
        req.end();
    };
};
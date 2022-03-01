exports.regx = {
    watchlink: /watch\?v=.{11}/g,
    playerRes: /\bytInitialPlayerResponse\s*=\s*\{/i,
    player: /\bytplayer\.config\s*=\s*{/,
    InitialData: /\bytInitialData("\])?\s*=\s*\{/i,
    contents: /\bitemSectionRenderer":{/i,
    jsonClosingChars: /^[)\]}'\s]+/,
    html5playerRes: /<script\s+src="([^"]+)"(?:\s+type="text\/javascript")?\s+name="player_ias\/base"\s*>|"jsUrl":"([^"]+)"/,
}
exports.BASE_URL = 'https://www.youtube.com/watch?v=';

exports.between = (haystack, left, right) => {
    let pos;
    if (left instanceof RegExp) {
        const match = haystack.match(left);
        if (!match) {
            return '';
        }
        pos = match.index + match[0].length;
    } else {
        pos = haystack.indexOf(left);
        if (pos === -1) {
            return '';
        }
        pos += left.length;
    }
    haystack = haystack.slice(pos);
    pos = haystack.indexOf(right);
    if (pos === -1) {
        return '';
    }
    haystack = haystack.slice(0, pos);
    return haystack;
};


//HTML5
exports.getHTML5player = body => {
    let html5playerRes = exports.regx.html5playerRes.exec(body);
    return html5playerRes ? html5playerRes[1] || html5playerRes[2] : null;
};

/**
 * Checks if there is a playability error.
 *
 * @param {Object} player_response
 * @param {Array.<string>} statuses
 * @param {Error} ErrorType
 * @returns {!Error}
 */
 exports.playError = (player_response, statuses, ErrorType = Error) => {
    let playability = player_response && player_response.playabilityStatus;
    if (playability && statuses.includes(playability.status)) {
      return new ErrorType(playability.reason || (playability.messages && playability.messages[0]));
    }
    return null;
  };
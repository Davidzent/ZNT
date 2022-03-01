const utils = require("./utils");

//JSON Shit
const parseJSON = (source, varName, json) => {
    if (!json || typeof json === "object") {
        return json;
    } else {
        try {
            json = json.replace(utils.regx.jsonClosingChars, "");
            return JSON.parse(json);
        } catch (err) {
            throw Error(`Error parsing ${varName} in ${source}: ${err.message}`);
        }
    }
};

const cutAfterJSON = (mixedJson) => {
    let open, close;
    if (mixedJson[0] === "[") {
        open = "[";
        close = "]";
    } else if (mixedJson[0] === "{") {
        open = "{";
        close = "}";
    }

    if (!open) {
        throw new Error(
            `Can't cut unsupported JSON (need to begin with [ or { ) but got: ${mixedJson[0]}`
        );
    }

    // States if the loop is currently in a string
    let isString = false;

    // States if the current character is treated as escaped or not
    let isEscaped = false;

    // Current open brackets to be closed
    let counter = 0;

    let i;
    for (i = 0; i < mixedJson.length; i++) {
        // Toggle the isString boolean when leaving/entering string
        if (mixedJson[i] === '"' && !isEscaped) {
            isString = !isString;
            continue;
        }

        // Toggle the isEscaped boolean for every backslash
        // Reset for every regular character
        isEscaped = mixedJson[i] === "\\" && !isEscaped;

        if (isString) continue;

        if (mixedJson[i] === open) {
            counter++;
        } else if (mixedJson[i] === close) {
            counter--;
        }

        // All brackets have been closed, thus end of JSON is reached
        if (counter === 0) {
            // Return the cut JSON
            return mixedJson.substr(0, i + 1);
        }
    }

    // We ran through the whole string and ended up with an unclosed bracket
    throw Error("Can't cut unsupported JSON (no matching closing bracket found)");
};

//find JSON
exports.findJSON = (source, varName, body, left, right, prependJSON) => {
    let jsonStr = utils.between(body, left, right);
    if (!jsonStr) {
        throw Error(`Could not find ${varName} in ${source}`);
    }
    return parseJSON(source, varName, cutAfterJSON(`${prependJSON}${jsonStr}`));
};
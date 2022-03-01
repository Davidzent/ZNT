const https = require('https');
// custom fetch for Node.js
exports.fetch = (method, url, payload=undefined) => new Promise((resolve, reject) => {
    https.get(
        url,
        res => {
            const dataBuffers = []
            res.on('data', data => dataBuffers.push(data.toString('utf8')))
            res.on('end', () => resolve(dataBuffers.join('')))
        }
    ).on('error', reject)
});


//trying to create something similar to miniget
exports.play = (options) => https.get(options, function(response) {
    res.pipe(stream, {
        end
    });
});
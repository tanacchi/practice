var debug = process.env.NODE_ENV !== "production";
var webpack = require("webpack");

module.exports = {
    context: __dirname,
    entry: "./js/scripts.js",
    devtool: debug ? "inline-source-map" : false,
    output: {
        path: __dirname + "/js",
        filename: "scripts.min.js"
    },
    plugins: debug ? [] : [
        new webpack.optimize.OccurenceOrderPlugin(),
        new webpack.optimize.UglifyJsPlugin({
            mangle: false,
            sourcemap: false,
        })
    ]
};

/*
 * @Description: 使用jimp和qrcode-reader识别解析二维码
 * @Author: your name
 * @Date: 2019-07-15 09:33:49
 * @LastEditTime: 2019-07-15 10:02:36
 * @LastEditors: Please set LastEditors
 */

const decodeImage = require('jimp').read;
const qrcodeReader = require('qrcode-reader');

/**
 * @description: 二维码图片解析
 * @param {type} 
 * @return: 
 */
function qrDecode(data,callback){
    decodeImage(data,function(err,image){
        if(err){
            callback(false);
            return;
        }
        let decodeQR = new qrcodeReader();
        decodeQR.callback = function(errorWhenDecodeQR, result) {
            if (errorWhenDecodeQR) {
                callback(false);
                return;
            }
            if (!result){
                callback(false);
                return;
            }else{
                callback(result.result)
            }
        };
        decodeQR.decode(image.bitmap);
    });
}

qrDecode("test.png",function(data){
  console.log(data);
});


// const posenet = require("@tensorflow-models/posenet");
// const fs = require("fs");
// const Canvas = require("canvas");
// require("@tensorflow/tfjs-node");

// async function estimatePoseOnImage(imageElement) {
//   // load the posenet model from a checkpoint
//   const net = await posenet.load({
//     architecture: "MobileNetV1",
//     outputStride: 16,
//     inputResolution: 513,
//     multiplier: 0.75
//   });

//   let start = new Date();
//   const poses = await net.estimatePoses(imageElement, {
//     flipHorizontal: false,
//     decodingMethod: "single-person"
//   });

//   let end = new Date() - start;
//   console.info("Execution time: %dms", end);

//   const pose = poses[0];
//   return pose;
// }

// fs.readFile("./pic/fullbody.png", function(err, data) {
//   if (err) throw err;
//   let img = new Canvas.Image(); // Create a new Image
//   img.src = data;

//   // Initialize a new Canvas with the same dimensions
//   // as the image, and get a 2D drawing context for it.
//   let canvas = Canvas.createCanvas(img.width, img.height);
//   let ctx = canvas.getContext("2d");
//   canvas.width = img.width;
//   canvas.height = img.height;
//   ctx.drawImage(img, 0, 0);

//   estimatePoseOnImage(canvas).then(pose => {
//     console.log(pose);
//   });
// });

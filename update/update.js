/*
 * @Description: 下载文件
 * @Author: your name
 * @Date: 2019-07-25 17:06:07
 * @LastEditTime: 2019-07-30 15:01:53
 * @LastEditors: Please set LastEditors
 */


// 下载
// 解压zip(2个文件，tar、tar.md5)
// MD5校验
// 备份
// 解压
// 添加权限
// 启动成功，删除下载包，删除上上个备份
// 启动失败，恢复数据，删除下载包

//升级包
var UPDATE_PACK_NAME = "update.tar.gz"
//升级包MD5
var UPDATE_PACK_MD5_FILE_NAME = "update.md5"
//升级脚本
var UPDATE_CMD = "update.sh"

var request = require('request');
var fs = require('fs');
var unzip = require("unzip");
var crypto = require('crypto');
var exec = require('child_process').exec; 


/**
 * @description: 运行shell脚本
 * @param {type} 
 * @return: 
 */
function exec_shell(cmdStr) {
    exec(cmdStr, function(err,stdout,stderr){
        if(err) {
            console.log('get weather api error:'+stderr);
        } else {
            console.log(stdout);
        }
    });
}


/**
 * @description: 删除字符串的空格
 * @param {type} 
 * @return: 
 */
function trim(str){ //
    return str.replace(/(^\s*)|(\s*$)/g, "");
}
function ltrim(str){ //删除左边的空格
    return str.replace(/(^\s*)/g,"");
}
function rtrim(str){ //删除右边的空格
    return str.replace(/(\s*$)/g,"");
}


 /**
  * @description: 下载文件
  * @param {type} 
  * @return: 
  */
 function downloadFileByHttp(url, fileName, callback){
    var options = {
        url: url
    };
    
    // http.get(options, function(res) {
    //     res.pipe(fileName);
    // });

    request
        .get(options)
        .on('error', function(err) {
            console.log(err)
        })
        .pipe(fs.createWriteStream(fileName))
 }

 
/**
 * @description: 下载文件
 * @param {type} 
 * @return: 
 */
function downloadFile(url, fileName, callback) {
    var options = {
        method: 'GET',
        url: url,
        // headers: {
        //   'User-Agent': 'request'
        // }
        encoding: null//当请求的是二进制文件时，一定要设置
    };

    var stream = fs.createWriteStream(fileName);
    
    request(options, function(error, response, body) {
        if (!error && response.statusCode == 200) {
            //var info = JSON.parse(body);
            console.log('ok');
        } else {
            console.log('error:', error);
            console.log('statusCode:', response && response.statusCode); 
            console.log('body:', body); 
        }
    })
    .pipe(stream)
    .on('close', function() {
        callback(fileName);
    })
    .on('error', function() {

    });
}


/**
 * @description: 解压
 * @param {type} 
 * @return: 
 */
function unzipFile(zipFileName, unzipFinish) {
    console.log(zipFileName);

    var start = zipFileName.lastIndexOf('/');
    var end = zipFileName.lastIndexOf('.');
    if (start >= 0 && end > start) {
        var dirName = zipFileName.substring(start+1, end);
        console.log(dirName);

        fs.createReadStream(zipFileName).pipe(unzip.Extract({ path: '.' }));//解压到当前目录
        console.log("文件解压完成。");
        
        unzipFinish();
    }
    
}


/**
 * @description: md5校验
 * @param {type} 
 * @return: 
 */
function check_md5(fileName, callback) {
    var start = new Date().getTime();

    var md5sum = crypto.createHash('md5');
    var stream = fs.createReadStream(fileName);
    
    stream.on('data', function(chunk) {
        md5sum.update(chunk);
    });
    stream.on('end', function() {
        var str = md5sum.digest('hex').toLowerCase();
        console.log('文件:'+fileName+',MD5签名为:'+str+'.耗时:'+(new Date().getTime()-start)/1000.00+"秒");
        callback(str);
    });
}


/**
 * @description: 从md5文件中读取
 * @param {type} 
 * @return: 
 */
function get_md5_from_file(fileName) {
    var data = fs.readFileSync(fileName, "utf-8");
    console.log("读取文件成功,内容是" + data);
    if (null != data) {
        var regex=/[0-9a-zA-Z]+\s/;
        var temp = regex.exec(data)[0];
        return trim(temp);
    }
    return null;
}


/**
 * @description: 下载完成回调 
 * @param {type} 
 * @return: 
 */
function download_finish(fileName) {
    console.log(fileName + '下载完毕');
    //解压
    unzipFile(fileName, function(dirPath) {
        //MD5校验文件
        check_md5(dirPath+"/"+UPDATE_PACK_NAME, function(md5Str) {
            //原始MD5
            var md5Value = get_md5_from_file(dirPath+"/"+UPDATE_PACK_MD5_FILE_NAME);
            if (null != md5Valuea && md5Value === md5Str) {
                var cmd = dirPath+"/"+UPDATE_CMD;
                fs.exists(cmd, function(exists) {
                    if(exists) {
                        exec_shell(cmd);
                    }
                });
            } else {

            }
        });

    });
}


/**
 * @description: 更新安装包
 * @param {type} 
 * @return: 
 */
function update() {
    //防止连接中有中文字符出错使用decodeURI
    //var url = decodeURI('https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1564731031&di=d44abbd550849729524dc894d8b91cc5&imgtype=jpg&er=1&src=http%3A%2F%2Fwww.cnr.cn%2Fent%2Fgd%2F20160907%2FW020160907267641854004.jpg');
    var url ="https://github.com/lhgcs/opencv-demo/archive/master.zip";
    var fileName = __dirname + "/" + url.split("/").reverse()[0];
    downloadFile(url, fileName, download_finish);
}

update();

// var tZipHost = tZipUrl.match(/http.+?com/)[0].split("http://")[1];
#!/bin/bash

###
 # @Description: 打包应用
 # @Author: your name
 # @Date: 2019-07-25 12:01:23
 # @LastEditTime: 2019-08-01 15:24:16
 # @LastEditors: Please set LastEditors
###


# 升级包
UPDATE_PACK_NAME="update.tar.gz"
# 升级包MD5
UPDATE_PACK_MD5_FILE_NAME="update.tar.gz.md5"


###
 # @description: 如果目录不存在，创建目录
 # @param {type} 
 # @return: 
###
function create_dir() {
    if [ ! -d $1 ]; then
        mkdir -p $1
    fi
}


###
 # @description: 清空目录下的所有文件（目录还在）
 # @param {type} 
 # @return: 
###
function clear_dir() {
    if [ -d $1 ]; then
        rm -rf $1/*
    fi
}


###
 # @description: 生成md5
 # @param {type} 
 # @return: 
###
function gennerate_md5() {
    if [ -f $1 ]; then
        md5sum $1 > $1.md5  #将MD5码写入md5文件
    fi
}


###################### run ######################

# 脚本当前路径
current_dir=$(cd $(dirname $0); pwd -P)
current_time=$(date +%Y-%m-%d)

tar_dir="./update"
zip_dir="./${current_time}"

rm -rf *.tar.gz
rm -rf *.md5
rm -rf *.zip

clear_dir ${tar_dir}
clear_dir ${zip_dir}

# 打包tar.gz(用绝对路径有警告)
create_dir ${tar_dir}
cp ./temp/* ${tar_dir} -a
tar -zcf ${UPDATE_PACK_NAME} ${tar_dir} --remove-files

# md5
gennerate_md5 ${current_dir}/${UPDATE_PACK_NAME}

# 打包zip
create_dir ${zip_dir}
mv *.tar.gz ${zip_dir}
mv *.md5 ${zip_dir}
cp -a unpack.sh ${zip_dir}
zip -rqm ${zip_dir} ${zip_dir}

exit 0
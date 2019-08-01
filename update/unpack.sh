#!/bin/bash

###
 # @Description: 更新应用
 # @Author: your name
 # @Date: 2019-07-25 12:01:23
 # @LastEditTime: 2019-08-01 15:57:57
 # @LastEditors: Please set LastEditors
###

# 升级包
UPDATE_PACK_NAME="update.tar.gz"
# 升级包MD5
UPDATE_PACK_MD5_FILE_NAME="update.md5"

# 备份文件名称
BACKUP_NAME="backup.tar"

# 程序目录
TARGET_PATH="../../"
# 升级包解压后的名字
UNPACK_PACK_NAME="update"


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


###
 # @description: 数据恢复
 # @param {type} 
 # @return: 
###
function recovery() {
    filePath="${DOWNLOAD_PATH}/${DOWNLOAD_NAME}"
    if [ -f ${filePath} ]; then

        check_md5 ${filePath}
        if [ $? == 0 ]; then

            # 删除程序
            clear_dir ${PROGRAME_PATH}
            # 解压
            tar -xf  ${BACKUP_PATH}/${BACKUP_NAME} -C ${PROGRAME_PATH}
            if [ $? == 0 ]; then
                return 0
            fi
            
        fi
        
    fi

    return 1
}


###
 # @description: 校验md5
 # @param {type} 
 # @return: 
###
function check_md5() {
    if [ -f $1 ]; then
        # 从指定文本中读取md5值，然后检测MD5值对应的文件是否完整
        res=$(md5sum --check $1 | grep "OK")
        if [ ! -z "${res}" ]; then
            return 0
        fi
    fi
    return 1
}


###
 # @description: 校验
 # @param {type} 
 # @return: 
###
function check() {

    update_pack="$1/${UPDATE_PACK_NAME}"
    update_pack_md5_file="$1/${UPDATE_PACK_MD5_FILE_NAME}"
    
    if [ -f ${update_pack} ]; then
        if [ -f ${update_pack_md5_file} ]; then
            check_md5 ${update_pack_md5_file}
            if [ $? == 0 ]; then
                return 0
            fi
        fi
    fi

    return 1
}


###
 # @description: 具体操作
 # @param {type} 
 # @return: 
###
function do_something() {

    # 文件存放目录
    do_path="$1/UNPACK_PACK_NAME"

    cp -a ${do_path}/1.txt ${TARGET_PATH}/
}


###
 # @description: 数据更新
 # @param {type} 
 # @return: 
###
function update() {
    # 校验MD5
    check $1
    if [ $? == 0 ]; then
        # 解压
        tar -zxf "$1/${UPDATE_PACK_NAME}"
        if [ $? == 0 ]; then
            do_something
        fi
    fi
}


###################### run ######################

# 脚本当前路径
current_dir=$(cd $(dirname $0); pwd -P)

case $1 in 
update) 
    update ${current_dir}
    ;; 
recovery) 
    recovery ${current_dir}
    ;; 
*)
    ;;
esac

# 删除
clear_dir ${current_dir}
# 重启
#shutdown -r now

exit 0
#!/bin/bash

###
 # @Description: 数据恢复
 # @Author: your name
 # @Date: 2019-07-25 12:01:23
 # @LastEditTime: 2019-07-30 16:32:21
 # @LastEditors: Please set LastEditors
###


# 备份文件目录
BACKUP_DIR="backup"
# 备份文件名称
BACKUP_NAME="backup.tar.gz"


###
 # @description: 删除目录
 # @param {type} 
 # @return: 
###
function delete_dir() {
    if [ -d $1 ]; then
        rm -rf $1
    fi
}

###
 # @description: 数据恢复
 # @param {type} 
 # @return: 
###
function recovery() {
    # 脚本当前路径
    current_dir=$(cd $(dirname $0); pwd -P)
    # 备份
    mv "${current_dir}/../ud" "${current_dir}/../ud.back"

    # 解压
    if [ -f "${current_dir}/${BACKUP_NAME}" ]; then
        tar -zxf "${current_dir}/${BACKUP_NAME}" -C "${current_dir}/../"
        if [ $? == 0 ]; then
            # 删除
            delete_dir "${current_dir}/../ud.back"
            return;
        fi
    fi
    # 恢复
    mv "${current_dir}/../ud.back" "${current_dir}/../ud"
}


###################### run ######################

recovery

# 重启
shutdown -r now

exit 0
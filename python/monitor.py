#-*- coding:utf-8 -*-
#########################################################################
# File Name: monitor.py
# Author: Shen Bo
# mail: Bo.A.Shen@nokia-sbell.com.cn
# Created Time: Tue 23 Apr 2019 02:45:02 PM CST
#########################################################################
#!usr/bin/env python3

import os
import commands
import time
import db_op

ENDLINE="Any question, please contact Bo.A.Shen@nokia-sbell.com\n\
==========================Warning==========================\n"
WARNING="\n==========================Warning==========================\n\
==== To many storage space you have requested\n\
==== Please reduce storage occupation to %dGB or blow\n"

def return_time():
    time_tup = time.localtime(time.time())
    format_time = '%Y-%m-%d_%a_%H-%M-%S'
    return time.strftime(format_time, time_tup)

class DirInfo:
    def __init__(self, dirname, result_file, limit):
        self.dirname = dirname
        self.result = result_file
        self.limit = limit

class UserDirInfo:
    def __init__(self, uname, used_space, directory, above_limited = None):
        self.uname = uname
        self.used_space = used_space
        self.directory = directory
        self.above_limited = above_limited

    def show_info(self):
        return "==== USER:<%s>, DIR:<%s/%s>, Used Space:%.2fGB\n%s" %(self.uname,
            self.directory, self.uname, self.used_space, ENDLINE)

    def show_warning(self):
        return WARNING

def get_storage_info(dirInfo):
    cmd = "cd %s && ls ./ | xargs du -sh > %s" %(dirInfo.dirname, dirInfo.result)
    #print("cmmand is: %s" %(cmd))
    status, result = commands.getstatusoutput(cmd)

def get_pts_by_username(uname):
    cmd = "w | grep %s | awk '{print $2}'" %uname
    #print("cmmand is: %s" %(cmd))
    status, result = commands.getstatusoutput(cmd)
    pts_list = result.split('\n')
    return pts_list

def analysis_storage(dirInfo):
    result_file = dirInfo.result
    file = open(result_file)
    userDirInfo_list = []
    for line in file:
        item_tmp = UserDirInfo(0, "Null", "Null")
        no_br = line.replace('\n', '')
        str_arry = no_br.split('\t')
        if "G" not in str_arry[0]:
            continue
        else:
            item_tmp.uname = str_arry[1]
            item_tmp.used_space = float(str_arry[0].replace('G', ''))
            item_tmp.directory = dirInfo.dirname
            userDirInfo_list.append(item_tmp)
    return userDirInfo_list

def info_user(user_list, limit):
    for user in user_list:
        if user.used_space >= limit:
            message = user.show_warning() %limit + user.show_info()
            user_pts_list = get_pts_by_username(user.uname)
            for pts in user_pts_list:
                if pts == '':
                    continue
                cmd = "echo \"%s\" | write %s %s" %(message, user.uname, pts)
                #print("cmd: [", cmd, "]")
                os.system(cmd)
        else:
            continue

def generate_update_db_data(user_dirinfo_list, limit):
    db_list = []
    for user in user_dirinfo_list:
        db_data = db_op.dbData('', '', 0, False, False)
        db_data.uname = user.uname
        db_data.dirname = '%s/%s' %(user.directory, user.uname)
        db_data.used_space = user.used_space
        if user.used_space > limit:
            db_data.above_limited  = True
        else:
            db_data.above_limited  = False
        db_data.force_removed = False
        db_list.append(db_data)
    db_op.check_db_table()
    db_op.insert_data_to_db(db_list)


def dir_space_check(dir_list, times):
    for dirInfo in dir_list:
        get_storage_info(dirInfo)
        userDirInfo_list = analysis_storage(dirInfo)
        generate_update_db_data(userDirInfo_list, dirInfo.limit)
        for i in  range(times):
            info_user(userDirInfo_list, dirInfo.limit)

def start_main():
    fpwork_dirInfo = DirInfo("/var/fpwork",
        "/root/storage_monitor/generated/fpwork_result.txt", 20)
    workspace_dirInfo = DirInfo("/ephemeral/workspace",
        "/root/storage_monitor/generated/workspace_result.txt", 50)
    dir_list = [fpwork_dirInfo, workspace_dirInfo]
    dir_space_check(dir_list, 5)

def log_store():
    file_log = "/root/storage_monitor/generated/mail"
    root_mail = "/var/spool/mail/root"
    split_str = '==================='
    cmd = 'cat %s >> %s && echo %s >> %s && echo '' > %s' %(root_mail,
            file_log, split_str, file_log, root_mail)
    status, result = commands.getstatusoutput(cmd)
    cmd = "ls -l %s | awk '{print $5}'" %file_log
    max_size = 1024*1024*10
    status, file_size = commands.getstatusoutput(cmd)
    if int(file_size) > max_size:
        time_str = return_time()
        cmd = 'mv %s %s_mail.log' %(file_log, time_str)
        os.system(cmd)

def test_func():
    pass

start_main()
log_store()

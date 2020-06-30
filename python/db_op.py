#-*- coding:utf-8 -*-
#########################################################################
# File Name: db_op.py
# Author: Shen Bo
# mail: Bo.A.Shen@nokia-sbell.com.cn
# Created Time: Tue 30 Apr 2019 03:29:46 PM CST
#########################################################################
#!usr/bin/env python3
import commands
import json
import MySQLdb

DBNAME = "eecloud_monitor"
CREATE_TABLE_SQL = 'CREATE TABLE IF NOT EXISTS `%s`(`id` INT NOT NULL \
AUTO_INCREMENT, `uname` VARCHAR(32), `dirname` VARCHAR(64), \
`used_space` DOUBLE(10, 2), `above_limited` BOOLEAN, \
`force_removed` BOOLEAN, `time_date` TIMESTAMP DEFAULT \
CURRENT_TIMESTAMP, PRIMARY KEY (id));'
INSERT_TABLE_SQL = 'INSERT INTO `%s` (uname, \
dirname, used_space, above_limited, force_removed) \
VALUES '

class dbData:
    def __init__(self, uname, dirname, used_space,
            above_limited = False, force_removed = False,
            time = None):
        self.uname = uname
        self.dirname = dirname
        self.used_space = used_space
        self.above_limited = above_limited
        self.force_removed = force_removed
        self.time = time

def get_instance_host_info():
    with open("/root/storage_monitor/config/ee_instances.json", 'r') as load_f:
        instances_dict = json.load(load_f)
        status, hostname = commands.getstatusoutput("echo $HOSTNAME")

    return hostname.replace('.', '_').replace('-', '_'), instances_dict[hostname]



class ExecuteSQL(object):
    def __init__(self, sql, host_ip, data = None):
        self.dbname = DBNAME
        self.sql = sql
        self.server_ip = host_ip
        self.data = data

    def format_data(self):
        if not self.data:
            print("Data is NULL")
            return

        if len(self.data) == 1:
            return (self.data[0].uname, self.data[0].dirname,
                    self.data[0].used_space, self.data[0].above_limited,
                    self.data[0].force_removed)
        else :
            squence_list = []
            for item in self.data:
                item_tuple = (item.uname, item.dirname, item.used_space,
                        item.above_limited, item.force_removed)
                squence_list.append(item_tuple)
            return squence_list

    def execute_sql(self):
        results = ''
        db_connect = MySQLdb.connect(host = self.server_ip,
                                     port = 3306,
                                     user = "monitor",
                                     passwd = "passwd",
                                     db = self.dbname)
        cursor = db_connect.cursor()

        try:
            if self.data:
                tuple_list = self.format_data()
                for item in tuple_list:
                    results = cursor.execute(self.sql, item)
            else:
                cursor.execute(self.sql)
            db_connect.commit()
            results = cursor.fetchall()
        except Exception as error:
            print('Error: execute failed, %s' %error)

        db_connect.close()
        return results

def check_db_table():
    table, ip = get_instance_host_info()
    #print ('table_nmae: ', table, ' ip: ', ip)
    if ip == '10.183.68.25':
        server_ip = 'localhost'
    else:
        server_ip = "10.183.68.25"
    sql = CREATE_TABLE_SQL %(table)
    #print("sql: ", sql)
    connect = ExecuteSQL(sql, server_ip)
    connect.execute_sql()

def insert_data_to_db(data):
    table, ip = get_instance_host_info()
    #print ('table_nmae: ', table, ' ip: ', ip)
    if ip == '10.183.68.25':
        server_ip = 'localhost'
    else:
        server_ip = "10.183.68.25"
    sql = INSERT_TABLE_SQL %table + "(%s, %s, %s, %s, %s);"
    #print('sql insert:', sql)
    connect = ExecuteSQL(sql, server_ip, data)
    connect.execute_sql()

def read_from_db():
    pass

if __name__ == '__main__':
    test_data = []
    check_db_table()
    data1 = dbData('test1', 'testdir/test1', 20.2, True, False)
    test_data.append(data1)
    data2 = dbData('test2', 'testdir/test2', 49.2, True, False)
    test_data.append(data2)
    insert_data_to_db(test_data)


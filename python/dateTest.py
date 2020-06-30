import time
import calendar

def timeprintf():
    times = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
    print(times)
    #times = time.strptime("%Y-%m-%d %H:%M:%S", time.localtime())
    #print(times)
    calendar1 = calendar.month(2020,1)
    print(calendar1)
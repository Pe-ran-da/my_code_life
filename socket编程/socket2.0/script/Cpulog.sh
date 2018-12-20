#                           hello! world!                               
########################################################################
#--------> File Name:Cpulog.sh
#--------> Version: 1.0
#--------> Author: Peranda
#--------> Mail: 
#--------> Created Time:2018-08-28 15:04:14
########################################################################
#!/bin/bash

echo -n "`date +%Y%m%d_%H:%M:%S` " #时间
echo -n "`cat /proc/loadavg | cut -d " " -f 1-3` " #cpu平均负载

###  cpu占用率(间隔0.5s)
time1=`cat /proc/stat | head -n 1 | awk '{print $5; print $2 + $3 + $4 + $5 + $6 + $7 + $8 + $9 + $10 + $11 }' `
sleep 0.5s
time2=`cat /proc/stat | head -n 1 | awk '{print $5; print $2 + $3 + $4 + $5 + $6 + $7 + $8 + $9 + $10 + $11 }' `
key1=$[`echo $time2 | cut -d " " -f 1` - `echo $time1 | cut -d " " -f 1`]
key2=$[`echo $time2 | cut -d " " -f 2` - `echo $time1 | cut -d " " -f 2`]
echo -n `echo "scale=2; (1 - ${key1}/${key2}) * 100" | bc `
echo -n "% "
###

### cpu温度
cpu_key=`cat /sys/devices/virtual/thermal/thermal_zone0/temp`
cpu_size=`echo "ibase=10;($cpu_key/1000)" | bc`
echo -n "${cpu_size}°C "
###判断cpu温度级别
echo ${cpu_size} | awk '{if($1 > 70) {print "warning";} else if ($i > 50) {print "note";}  else {print "normal";}}'



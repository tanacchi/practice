#!/bin/sh

set -eu

bag_filename=${1}
bag_duration=`rosbag info ${bag_filename} | sed -n 3p | awk '{print substr($3, 2, 4) }'`
echo ${bag_duration}

rosbag play ${bag_filename} > /dev/null

process_id=`ps -aux | grep [r]osbag/play | awk '{print $2 }'`
echo "process ID : ${process_id}"

start_time=`date +%s`

current_time=`date +%s`
processing_time=$((${current_time} - ${start_time}))
# while [ $(( ${bag_duration} - ${processing_time} )) -lt 0 ]:
while [ ${processing_time} -lt 10 ]:
do
    echo "${processing_time} seconds has past."
    sleep 0.5
    current_time=`date +%s`
    processing_time=$((${current_time} - ${start_time}))
done

kill -SIGINT ${process_id}

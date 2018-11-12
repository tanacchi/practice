#!/bin/sh
set -eu

integrated_points_num=0

output_filename=`date +%Y%m%d%H%M`.pcd
echo ${output_filename}

for pcd_file in "${@}"; do
    pcd_data=`tail -n +12 ${pcd_file}`
    points_num=`echo "${pcd_data}" | wc -l`
    integrated_points_num=`expr ${integrated_points_num} + ${points_num}`
    echo "${pcd_data}" >> ${output_filename}
done

file_header="# .PCD v0.7 - Point Cloud Data file format\n\
VERSION 0.7\n\
FIELDS x y z\n\
SIZE 4 4 4\n\
TYPE F F F\n\
COUNT 1 1 1\n\
WIDTH ${integrated_points_num}\n\
HEIGHT 1\n\
VIEWPOINT 0 0 0 1 0 0 0\n\
POINTS ${integrated_points_num}\n\
DATA ascii\n"

sed -i "1s/^/${file_header}/" ${output_filename}

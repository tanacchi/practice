#!/bin/sh

for file in *.jpg
do
    num=`expr ${file%.*} + 1`
    echo "${num}"
done

#!/bin/sh

if ["$#" -ne "2" ]
then
    echo "Invaild argument"
    exit 1
fi

index=`expr $2 \* 1000000`

for file in "$1"/*.jpg
do
    echo "Converting ${file%/}\t=>\t${index%.*}.jpg"
    mv ${file%.*}.jpg $1/${index%.*}.jpg
    index=`expr ${index} + 1`
done

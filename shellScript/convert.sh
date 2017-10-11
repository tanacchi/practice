#!/bin/sh

index=`expr $2 \* 10000`

for file_raw in $1/*.JPG
do
    echo "Converting ${file_raw%/}\t=>\t${index%.*}.jpg"
    mogrify -format jpg ${file_raw}
    index=`expr ${index} + 1`
    mv ${file_raw%.*}.jpg $1/${index%.*}.jpg
done

rm $1/*.JPG

for renamed_file in $1/*.jpg
do
    mogrify -resize 640x \
            -unsharp 0x0.75+0.75+0.008 \
            -colors 255 -quality 100 \
            -blur 0.5x0.5 \
            -verbose ${renamed_file}
done

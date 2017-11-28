#!/bin/sh

if [$# -ne 1]
then
    echo "Invaild argument"
    exit 1
fi

for file in "$1"/*.jpg
do
    mogrify -format jpg \
            -resize 640x \
            -unsharp 0x0.75+0.75+0.008 \
            -colors 255 -quality 100 \
            -blur 0.5x0.5 \
            -verbose \
            "${renamed_file}"
done


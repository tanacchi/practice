#!/bin/sh

GOMOKU_IMAGE_DIR="${HEROKU_APP_URL}/images/gomoku"
BOARD_SIZE=2

if [ ${#} -ne $((BOARD_SIZE * BOARD_SIZE)) ]; then
  echo "Argument num \"${#}\" is invalid."
  return 1
fi

args=(${@})
for col in `seq 0 $((${BOARD_SIZE} - 1))`; do
  row_images=()
  for row in `seq 0 $((${BOARD_SIZE} - 1))`; do
    index=$((col*BOARD_SIZE + row))
    row_images+=("${GOMOKU_IMAGE_DIR}/${args[${index}]}.png")
  done
  convert +append ${row_images[@]} "${GOMOKU_IMAGE_DIR}/row${col}.png"
done
row_images=("${GOMOKU_IMAGE_DIR}/row*.png")
convert -append ${row_images[@]} "${GOMOKU_IMAGE_DIR}/result.png"

sizes=("1040" "700" "460" "300" "200")
for size in ${sizes[@]}; do
  convert -resize ${size} "${GOMOKU_IMAGE_DIR}/result.png" "${GOMOKU_IMAGE_DIR}/${size}"
done

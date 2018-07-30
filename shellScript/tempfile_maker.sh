file_names=`cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 10 | head -n 20 | uniq`
for file_name in ${file_names[@]}; do
    echo ${file_name}
    touch ./test/${file_name}'.tmp'
done

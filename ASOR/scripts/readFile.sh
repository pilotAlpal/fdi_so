#! /bin/bash
echo -e "Enter absolute path of the file"
read file
exec <$file 
while read line
do
echo $line
done

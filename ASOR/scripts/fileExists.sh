#!/bin/bash
file=$1
if [ -f $file ]
then
 echo -e "The $file exist"
else
 echo -e "The $file does not exist"
fi

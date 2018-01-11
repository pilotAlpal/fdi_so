#!/bin/bash
echo Give me a string
read str1
echo and give an other one
read str2
len1=${#str1}
len2=${#str2}
echo "Length of the first string ($str1) is: $len1"
echo "Length of the second string ($str2) is: $len2"

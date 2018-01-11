#!/bin/bash
echo Give me two string to compare:
read str1 str2
if [ "$str1" == "$str2" ] ; then
	echo Both strings are "$str1"
else
	echo They are diferent
fi

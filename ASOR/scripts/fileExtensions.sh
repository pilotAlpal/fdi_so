#!/bin/bash
for filename in $(ls)
do
	ext=${filename##*\.}
	case "$ext" in
	c) echo "$filename : C source file"
		;;
	o) echo "$filename :Object file"
		;;
	sh) echo "$filename : Shell script"
		;;
	txt) echo "$filename : Text file"
		;;
	*) echo "$filename : Unknown file type"
		;;
esac
done

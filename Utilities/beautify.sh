#!/bin/bash
# Author : Loïc Messal

usage="Program to recursively beautify each file from a directory.

Usage : $(basename "$0") [-h] -p path

where:
    -h  show this help text
    -p  set a specific path"


if [[ $# -eq 0 ]] ; then
	echo "$usage"
	exit 0
fi


while getopts ':hp:' option; do
	case "$option" in
		h) 	echo "$usage"
			;;
		p) 	path=$OPTARG
			;;
		:) 	printf "missing argument for -%s\n" "$OPTARG" >&2
			echo "$usage" >&2
			exit 1
			;;
		\?)	printf "illegal option: -%s\n" "$OPTARG" >&2
			echo "$usage" >&2
			exit 1
			;;
	esac
done

for file in $(find $path -name '*.cpp' -or -name '*.h')
do
	echo "$file"
	clang-format-3.8 -style=WebKit $file > "$file_save.cpp"
	mv "$file_save.cpp" $file 
done
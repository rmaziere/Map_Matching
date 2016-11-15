#! /bin/sh

usage="Be sure to have commit before launch this program.

Usage : $(basename "$0") [-h] -r

where:
    -h  show this help text
    -r  Okay, I am ready ! "

if [[ $# -eq 0 ]] ; then
	echo "$usage"
	exit 0
fi


while getopts ':hr:' option; do
	case "$option" in
		h) 	echo "$usage"
			;;
		r) 	;;
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

cd ../MMModule
doxygen
rm -r /tmp/map_matching/html
mkdir -p /tmp/map_matching/html
mv ./html /tmp/map_matching/html
cd ..
git checkout gh-pages
rm -r doc/
mkdir -p doc
cp -r /tmp/map_matching/html/html/html/* doc/
git add doc/
git commit -m "update documentation"
git push
git checkout sandbox
rm -r MMModule/html
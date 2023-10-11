#!/bin/bash

for i in "$@"
do 
	du -sH $i

	if [ -f $i ]
	then
		echo To jest plik
	elif [ -d $i ]
	then
		if [ $(ls -A $i) ]
		then
			echo To jest katalog
		else
			echo To jest pusty katalog
		fi
	fi
done

#!/bin/bash

if [ $# != 4 ]
then
	echo Bledna liczba argumentow
	exit 1
fi

tar -cv $(find $1 -name "*.${2}" -ctime -$3) --file $4 2>/dev/null

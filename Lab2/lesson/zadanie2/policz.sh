#!/bin/bash


if [ $# == 1 ]
then
	if [ $1 == '-a' ]
	then 
	echo $(ls -A1 | wc -l)
	fi
else
	echo $(ls -1 | wc -l)
fi

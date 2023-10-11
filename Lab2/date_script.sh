#!/bin/bash

WEEK_DAY=$(date +%u)


if [ ${LC_TIME} == "pl_PL.UTF-8" ]
then
	if [ ${WEEK_DAY} -lt 6 ] 
	then
		echo "Have a nice workday!!!"
	else
		echo "Have a nice weekend!!!"
	fi
fi


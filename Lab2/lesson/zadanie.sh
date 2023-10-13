#!/bin/bash

LC_ALL=C

if [ $(date +%u) -lt 6 ]
then 
		echo Dzien dobry, dzien roboczy
else
		echo Dzien dobry, weekend
fi

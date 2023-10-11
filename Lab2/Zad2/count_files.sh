#!/bin/bash

if [ $# == 1 ] && [ $1 == '-a' ]
then
	ls -1aA | wc -l
else
	ls -1 | wc -l
fi

#!/bin/bash

if [ $# != 1 ]
then
	echo "Wrong number of input parameters!!!"
	exit 1
fi

while true
do
echo "What would like to do?"
echo "1- be ignored by projector (SIGFPE)"
echo "2- redraw (SIGWINCH)"
echo "3- shut down (SIGUSR1)"
echo "4- shut down pilot"

read -a COMMAND

echo $COMMAND

if [ $COMMAND == 1 ]
then
	kill -$(kill -l SIGFPE) $1
elif [ $COMMAND == 2 ]
then
	kill -$(kill -l SIGWINCH) $1
elif [ $COMMAND == 3 ]
then
	kill -$(kill -l SIGUSR1) $1
elif [ $COMMAND == 4 ]
then
	exit 3
fi
done

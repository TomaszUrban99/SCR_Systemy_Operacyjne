#!/bin/bash

signal_count=0
time

function signal_controller()
{
	let signal_count++
	if [[ ${signal_count} == 1 ]]
	then
		echo "Do you really want to delete?"
		sleep 1
		echo 5
		sleep 1
		echo 4
		sleep 1
		echo 3
		sleep 1
		echo 2
		sleep 1
		echo 1
		sleep 1
		echo 0
		echo RESET...
		signal_count=0
	elif [[ ${signal_count} == 2 ]]
	then
		echo "Closing..."
		exit 0
	fi
}

trap "echo WINDOWS CHANGE - redraw" SIGWINCH
trap signal_controller SIGUSR1

while true
do
	sleep 1
done

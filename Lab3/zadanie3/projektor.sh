#!/bin/bash

signal_count=0

function signal_controller()
{
	let signal_count++
	if [[ ${signal_count} == 1 ]]
	then
		time_counter=5
		echo "Do you really want to delete?"
		while [ ${time_counter} -gt 0 ]
		do 
			sleep 1
			echo ${time_counter}
			let time_counter--
		done
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

# Nie udalo sie przechwycic sygnalu SIGKILL
trap "echo Kernel wants to kill me :-(" SIGKILL

# Udalo sie zatrzymac i pononwnie wystartowac proces

while true
do
	sleep 1
done

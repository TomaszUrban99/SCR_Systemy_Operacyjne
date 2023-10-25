#!/bin/bash

iterator=0

while [ $iterator -lt $1 ]
do
	echo $iterator
	nice -$(( iterator * 2 )) ./$2 &
	let iterator++
done



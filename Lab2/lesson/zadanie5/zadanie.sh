#!/bin/bash

while read x y z
do
	echo Adresat $x
	echo Temat $y
	echo Plik z wiadomoscia $z

	echo $z | mail -s $y $x
done < $1

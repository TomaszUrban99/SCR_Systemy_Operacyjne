
#!/bin/bash

for i in $@
do
	if [ -f $i ]
	then
		echo Plik istnieje $i
	elif  [ -d $i ]
	then
		if [ $(ls -aA $i) ]
		then
			echo To jest katalog $i
		else
			echo To jest pusty katalog $i
		fi
	else
		echo Plik nie istnieje $i
	fi
done

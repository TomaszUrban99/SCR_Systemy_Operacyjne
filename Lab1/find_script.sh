#!/bin/bash

ls -lsca $( find /etc -type f -a \( \( -ctime -3 -size -1k \) -o \( -ctime +30 -ctime -90 -size -250k \) \) )

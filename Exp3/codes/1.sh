#!/bin/bash

re='^[0-9]+$'
if ! [ $# -eq 2 ] # check if the number of arguments is not correct
then
	echo "Invalid input! This script needs 2 arguments."
elif ! [[ $1 =~ $re ]] || ! [[ $2 =~ $re ]] # check if arguments are not numbers
then
	echo "Invalid input! Arguments should be numbers."
else
	# print sum of 2 args
	echo "Sum of given arguments is $(($1+$2))."
	# print the greater number
	if [ $1 -gt $2 ]
	then
		echo "The greater number is $1."
	else
		echo "The greater number is $2."
	fi
fi



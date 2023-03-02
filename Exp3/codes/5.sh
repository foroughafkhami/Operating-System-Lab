#!/bin/bash
# functions for printing shapes
###############################
# print diamond
###############################
print_diamond () { # parameters: size
	size=$1
	space=$(( size - 1 ))
	i=0
	# print upper part of diamond
	while [ $i -lt $size ]
	do
		j=0
		while [ $j -lt $space ]
		do
			echo -n " "
			j=$(( j + 1 ))
		done
		j=0
		while ! [ $i -lt $j ]
		do
			echo -n ". "
			j=$(( j + 1 ))
		done
		echo
		space=$(( space - 1 ))
		i=$(( i + 1 ))
	done
	# print downer part of diamond
	space=0
	i=$size
	while [ $i -gt 0 ]
	do
		j=0
		while [ $j -lt $space ]
		do
			echo -n " "
			j=$(( j + 1 ))
		done
		j=0
		while [ $j -lt $i ]
		do
			echo -n ". "
			j=$(( j + 1 ))
		done
		echo
		space=$(( space + 1 ))
		i=$(( i - 1 ))
	done
}
###############################
# print number triangle
###############################
print_num_triangle () { # parameters: size
	size=$1
	i=1
	while ! [ $i -gt $size ]
	do
		j=$i
		while [ $j -gt 0 ]
		do
			echo -n $i
			j=$(( j - 1 ))
		done
		echo
		i=$(( i + 1 ))
	done
}
###############################
# print liner triangle
###############################
print_line_triangle () { # parameters: size
	size=$1
	i=1
	while ! [ $i -gt $size ]
	do
		j=$i
		while [ $j -gt 0 ]
		do
			echo -n "|"
			if [ $j -eq 1 ]
			then
				echo -n "_"
			else
				echo -n " "
			fi
			j=$(( j - 1 ))
		done
		echo
		i=$(( i + 1 ))
	done
}
read -p "Enter 1 or 2 or 3 to choose shape: " num
re='^[0-9]+$'
if ! [[ $num =~ $re ]] || [ $num -gt 3 ] || [ $num -lt 1 ]
then
	echo "ERR: Invalid input"
	exit
fi
read -p "Enter size of shape: " size
if ! [[ $size =~ $re ]] ||  [ $size -lt 1 ]
then
	echo "ERR: Invalid size!"
	exit
fi
################
# Print shapes
################
# Shape number 1
if [ $num -eq 1 ]
then
	print_num_triangle "$size"
################
# Shape number 2
elif [ $num -eq 2 ]
then
	print_diamond "$size"
################
# Shape number 3
elif [ $num -eq 3 ]
then
	print_line_triangle "$size"
fi

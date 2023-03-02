#!/bin/bash
read -p 'Enter first number:' num1
echo -e "Choose operation:\n1.add\n2.subtract\n3.multiply\n4.divide"
read op
read -p 'Enter second number:' num2
re='^[0-9]+$'
if ! [[ $num1 =~ $re ]] || ! [[ $num2 =~ $re ]]
then
	echo "ERR: Operands should be numbers!"
	exit
fi
if ! [[ $op =~ $re ]] ||  [ $op -gt 4 ] || [ $op -lt 1 ]
then
	echo "ERR: Chosen operator in not valid!"
	exit
fi
case $op in
	1)result=$(( num1 + num2 ))
	;;
	2)result=$(( num1 - num2 ))
	;;
	3)result=$(( num1 \* num2 ))
	;;
	4)
		if [ $num2 -eq 0 ]
		then
			echo "ERROR: Divide by zero."
			exit
		else
			result=$(( num1 / num2 ))
		fi
	;;
esac
echo "The result is $result."


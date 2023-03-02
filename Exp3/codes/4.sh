#! /usr/bin/bash
echo "Enter start line:"
read x
echo "Enter end line:"
read y
echo "Enter file name:"
read file_name

i=1
while read line
do
   if [ $i -ge $x ]&&[ $i -le $y ]
   then
       echo $line
   fi
   ((i=$i+1))
done < $file_name

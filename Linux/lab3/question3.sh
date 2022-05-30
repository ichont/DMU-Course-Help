#!/bin/sh
echo "Input a integer:"
read tag
for num in $(seq 1 $tag | grep -v "3")
do
	((var=$num%3))
	if test $var -ne 0 ;then
		
		echo $num
	fi
done
exit 0

#!/bin/bash

# Factorial Calculation - Displays the factorial of given integer
# JJ McCauley

num=$1
sum=1

while [ $num -ne 0 ]; do
	sum=$( expr $sum \* $num)
	num=$( expr $num - 1)
done

echo $sum 

exit 0;

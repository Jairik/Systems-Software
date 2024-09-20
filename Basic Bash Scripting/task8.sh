#!/bin/bash

# Digit Adder - Add all the digits of a given number
# JJ McCauley

full_num=$1
sum=0

while [ $full_num -gt 0 ]; do
	digit=$(expr $full_num % 10)
	sum=$(expr $sum + $digit)
	full_num=$(expr $full_num / 10)
done

echo "Sum: $sum"

exit 0;

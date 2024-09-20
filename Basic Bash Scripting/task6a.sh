#!/bin/bash


# Lab 2 Task #6a - Display a diamond given a base value by the user
# JJ McCauley

# Retreiving user input
echo "What's up $USER!"
echo "Please enter diamond size to print: "
read baseNum
while [ $baseNum -le 2 ]  || [ $(expr $baseNum % 2) -eq 0 ]; do
	echo "Number must be odd and greater than 3. Please try again"
	read baseNum
done

# Declaring a function to print a triangle, given a start and end
print_triangle () {
	start_param=$1
	step=$2
	end_param=$3
	for i in $(seq $start_param $step $end_param); do
		num_stars=$(expr $i \* 2 + 1) 
		num_spaces=$(expr $baseNum - $num_stars / 2)
		for j in $(seq 0 $num_spaces); do
			echo -n " "
		done 
		for l in $(seq 0 $num_stars); do
			echo -n "*"
		done
		for s in $(seq 0 $num_spaces); do
			echo -n " "
		done 
		echo "" #Will print a newline
	done
} 

#Running the print_triangle functions for the top and bottom half of the diamond
print_triangle 0 1 $baseNum  # Echo top half and middle
print_triangle $(expr $baseNum - 1) -1 0



exit 0;

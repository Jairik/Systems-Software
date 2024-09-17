#!/bin/bash


# Lab 2 Task #6b - Display an arrow, given a base and tail value by the user
# JJ McCauley

# Retreiving user input
echo "What's up $USER!"
echo "Please enter head and tail (seperated by a space) for the size of the arrow to print: "
read headNum tailNum
while [ $(expr $headNum % 2) -eq 0 ]; do
        echo "Head must be odd. Please try again"
        read headNum
done

# Declaring a function to half of an arrow, given a start, step, and end
print_arrow () {
        start_param=$1
        step=$2
        end_param=$3
        for i in $(seq $start_param $step $end_param); do
		num_stars=$(expr $i + 1)
                num_spaces=$(expr $headNum - $num_stars)
                for j in $(seq 0 $num_spaces); do
                        echo -n " "
                done 
                for l in $(seq 0 $i); do
                        echo -n "*"
                done
                echo "" #Will print a newline
        done
} 

#Printing the top half of the arrow
print_arrow 0 2 $(expr $headNum - 3)  # Echo top half and middle
#Printing the middle part of array (head and tail)
echo -n " "
for s in $(seq 0 $(expr $headNum + $tailNum - 1)); do
	echo -n "*"
done
echo ""  # Print a newline
#Printing the bottom half of the arrow
print_arrow $(expr $headNum - 3) -2 0


exit 0;


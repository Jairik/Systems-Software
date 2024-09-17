#!/bin/bash

# JJ McCauley

echo "Welcome! Please enter directory to find the file:"
read directory_name

if [ ! -d $directory_name ]; then
	echo "Directory was not found"
	exit 1
fi
#Now, retreive a file to search for within this directory
echo "Enter File Name: "
read file_name

if [ ! -e $directory_name/$file_name ]; then  # If file is not in the directory
	i=2
	while [$(expr $i -ne 0) ] && [ ! -e $file_name ]; do
		echo "Please try again, File was not found."
		read file_name
	done
	if [ $(expr $i -eq 0) ]; then
		echo "Unable to find file name, exiting program"
		exit 2
	fi
fi

#Check if the file is readable
if [ ! -r $directory_name/$file_name ]; then
	echo "File is not readable"
	exit 3
fi

#File is now in directory, search for a given word
echo "Please enter word to look for in the file: "
read word_to_find

if grep -q $word_to_find $directory_name/$file_name; then
	echo "$word_to_find FOUND!"
else
	echo "$word_to_find NOT FOUND"
	exit 4
fi

exit 0;

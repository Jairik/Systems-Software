# Practice for upcoming Midterm, mainly refreshing up on syntax
# JJ McCauley

# Bash Basics:
#	-> Low level scripting language (plain-text file (Ascii code) that contains Shell commands)
#	-> Takes in parameters $1, $2, $3, ect.
#	-> Syntax is like a weird subproduct of python and C
#		-> There are NO spaces between assignments (var=$1)
#		-> if -> fi, do: (loop here) done, case -> esac

#!~/bin/bash

guestName=$1
ogn=-1

# --- While loop ---

while [ $ogn -ne -1 ]; do  # Must be space around brackets
	read ogn
done

# --- Echo Statement (EZ) ---

echo "You have $ogn number of guests!"

# --- For Loop ---
for i in $(seq 0 $ogn); do
	echo "Hello Guest #$i"
done

# --- Function with local variable ---
func () {
	local loopNum
	echo "Enter loop num or something"
	read loopNum
	if [ "$1" != "Carl" ]; then  # -ne flags used for ints, == used for strings
		echo 'Since Carl isnt here... (sorry if your name is Carl, random name)'
	else
		exit 1
	fi 

	echo 'Enter Filename to Compile'
	read fileName

# --- Case statement + compiling stuff
	case fileName in 
		*.c ) gcc -o $filename;; #Dont forget two semicolons for some reason
		*.cpp ) g++ -o $filename;;
		*.sh ) chmod a+x;;
		* ) echo "$fileName is unrecognized in simple program. Exiting (get better)"
			exit 1 ;;
	esac

}
func

# --- Using chmod to make program executable
chmod a+x "$0"
echo "Now everybody can execute this"

chmod a-rwx "$0"
echo "Now nobody can do anything to this"

chmod a+r "$0"
chmod u+wx "$0"
echo "Now everyone can read, and user can write + execute"

# Shell Parameters
echo "Program name: $0"
echo "Program parameter count: $#"
echo "The following parameters represent all positional parameters in: "
echo "A single word $*"
echo "Seperate words (might break) $@"

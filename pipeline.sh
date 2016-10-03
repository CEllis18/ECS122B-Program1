#!/bin/bash
#Author:		Chris Ellis
#ID#:			991868704
#ECS122B 		Program#1
#FileName		pipeline.sh
#!/bin/bash
#Argument List
#1) executable to run
#2) number of samples (number of files to sort)
#3) number of integers in each sample
#sample input: bash pipeline.sh quicksort 3 50
if [ "$1" != "" ] && [ "$2" != "" ] && [ "$3" != "" ]; then
	echo "Correct Number of Arguments"	
	RANDOM=$$
	numTest="$2"
	numElmsPerTest="$3"
	#QUICKSORT CASE
	if [ "$1" == "quicksort" ]; then
		echo "Quicksort_timed.out selected"
		echo "Compiling quicksort"
		g++ -std=c++11 quicksort_timed.cpp -o quicksort_timed.out
		g++ -std=c++11 quicksort_stats.cpp -o quicksort_stats.out	
		echo "Sample Number, Language, Time, Number of Partitioning Stages, Number of Exchanges, Number of Compares" > quicksort.csv
		for((start=1; $start<=$numTest;start++));do
			#a) gen a file with number of integers to sort
			echo "Running Test $start"
			echo "$numElmsPerTest" > input.txt
			for((innerStart=1;$innerStart<=$numElmsPerTest;innerStart++));do
				temp=$RANDOM;
				echo "$temp" >> input.txt
			done
			#b)run and time the timed program using Unix command time
			(time quicksort_timed.out input.txt 10) 2> timed.txt
			while read -r line
			do
				grepLine=$(grep 'real' $line)
				filteredTime=${grepLine/real	/}
				filter2=${filteredTime/[0-9]*m/} #remove "numbers"m prefix
				capturedTime=${filter2/s/} #remove suffix 's'
			done < timed.txt
			#$filteredTime has the Timed value!
			#b.1) RUN STATS VERSION FOR STATS!
			(quicksort_stats.out input.txt 10) > stats.txt
			vs=1
			while read -r line
			do
				if [ "$vs" == 1 ]; then
					orig="$line"
					search1="Partitioning_Stages "
					part1=${orig/$search1/}
					((vs++))
				elif [ "$vs" == 2 ]; then
					orig="$line"
					search2="Exchanges "
					part2=${orig/$search2/}
					((vs++))
				else
					orig="$line"
					search3="Compares "
					part3=${orig/$search3/}
					((vs++))
				fi
			done < stats.txt
			#c) print the relevant statistics for sample i to a .csv
			nextLine="$start,c++,$capturedTime,$part1,$part2,$part3"
			echo "$nextLine" >> quicksort.csv
		done
		rm input.txt
		rm timed.txt
		rm stats.txt
		rm quicksort_timed.out
		rm quicksort_stats.out
	#MERGESORT CASE
	elif [ "$1" == "mergesort" ]; then
		echo "mergesort_timed.out selected"
		echo "Compiling mergesort"
		g++ -std=c++11 mergesort_timed.cpp -o mergesort_timed.out
		g++ -std=c++11 mergesort_stats.cpp -o mergesort_stats.out		
		echo "Sample Number, Language, Time, Number of Recursive Calls, Number of Transitions, Number of Compares" > mergesort.csv
		for((start=1; $start<=$numTest;start++)); do
			#a) gen a file with number of integers to sort
			echo "Running Test $start"
			echo "$numElmsPerTest" > input.txt
			for((innerStart=1;$innerStart<=$numElmsPerTest;innerStart++));do
				temp=$RANDOM;
				echo "$temp" >> input.txt
			done
			#b)run and time the timed program using Unix command time
			(time mergesort_timed.out input.txt) 2> timed.txt
			while read -r line
			do
				grepLine=$(grep 'real' $line)
				filteredTime=${grepLine/real	/}
				filter2=${filteredTime/[0-9]*m/} #remove "numbers"m prefix
				capturedTime=${filter2/s/} #remove suffix 's'
			done < timed.txt
			#$filteredTime has the Timed value!
			#b.1) RUN STATS VERSION FOR STATS!
			(mergesort_stats.out input.txt) > stats.txt
			vs=1
			while read -r line
			do
				if [ "$vs" == 1 ]; then
					orig="$line"
					search1="Recursive_Calls "
					part1=${orig/$search1/}
					((vs++))
				elif [ "$vs" == 2 ]; then
					orig="$line"
					search2="Transitions "
					part2=${orig/$search2/}
					((vs++))
				else
					orig="$line"
					search3="Compares "
					part3=${orig/$search3/}
					((vs++))
				fi
			done < stats.txt
			#c) print the relevant statistics for sample i to a .csv
			nextLine="$start,c++,$capturedTime,$part1,$part2,$part3"
			echo "$nextLine" >> mergesort.csv
		done
		rm input.txt
		rm timed.txt
		rm stats.txt
		rm mergesort_timed.out
		rm mergesort_stats.out
	#INVALID CASE
	else
		echo "Invalid executable: please use quicksort_timed.out or mergesort_timed.out"
	fi
else
	echo "Incorrect input: invalid # of command line arguments"
	echo "Argument format is: executableName numFilesToSort numberOfIntsInTest"
fi
#end
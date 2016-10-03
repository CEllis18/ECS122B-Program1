#!/bin/bash
#Author:		Chris Ellis
#ID#:			991868704
#ECS122B 		Program#1
#FileName		Sanity_check.sh
#This script takes in two command line arguments: 
#1)Number of tests (number of test files to gen and sort)
#2) Number of integers in each sample
if [ "$1" != "" ] && [ "$2" != "" ]; then
	echo "Compiling quicksort and mergesort"
	g++ -std=c++11 quicksort_verbose.cpp -o quicksort.out
	g++ -std=c++11 mergesort_verbose.cpp -o mergesort.out
	RANDOM=$$
	numTest="$1"
	numElmsPerTest="$2"
	numFailed=0;
	for((start=1; $start<=$numTest;start++)); do
		echo "$numElmsPerTest" > input.txt
		#generate random values for file
		echo "Creating random file for test $start"
		for((innerStart=1;$innerStart<=$numElmsPerTest;innerStart++)); do
			temp=$RANDOM;
			echo "$temp" >> input.txt
		done
		echo "Running quicksort"
		quicksort.out input.txt 10 > quicksort_failed_test_$start.txt
		echo "Running mergesort"
		mergesort.out input.txt > mergesort_failed_test_$start.txt
		#compare results
		diff quicksort_failed_test_$start.txt mergesort_failed_test_$start.txt
		#note: $? is special character where result of diff is store
		#$? = 0, means no diff found $? = 1 means diffs found
		if [ $? = "0" ]; then
			echo "Test $start: No Difference"
			rm quicksort_failed_test_$start.txt
			rm mergesort_failed_test_$start.txt
		else
			echo "Test $start: Differences Found"
			((numFailed++))
		fi
	done
	if [ $numFailed = "0" ]; then
		echo "All tests passed."
	else
		echo "$numFailed tests failed."
	fi
	#remove generated files
	rm quicksort.out
	rm mergesort.out
	rm input.txt	
else
	echo "Incorrect input: invalid # of command line arguments"
	echo "Argument format is: numberOfTests numberOfIntsInTest"
fi
#NEED TO REMOVE ALL GEN'd FILES!
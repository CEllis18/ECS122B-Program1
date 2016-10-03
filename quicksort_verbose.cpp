//Author:		Chris Ellis
//ID#:			991868704
//ECS122B 		Program#1
//FileName		quicksort_verbose.cpp
#include <string>
#include <utility>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
using namespace std;

//COMPLETED AND FIXED!
//COMMAND LINE ARGUMENT FORMAT
//quicksort.out inputFile K-Value
 
 
int iSort;


void insertionSort(int *a, int lo, int hi){
	int temp;
	int prev;
	int index = lo+1;
	while(index != hi+1){
		temp = a[index];
		prev = index -1;
		while(prev >= lo and a[prev] > temp){
			a[prev+1] = a[prev];
			prev = prev - 1;		
		}
		a[prev+1] = temp;
		index++;
	}
	return;
}


void quicksort(int* a, int lo, int hi) {
    if (hi <= lo) return;
	
	if((hi - lo + 1) <= iSort){
		return insertionSort(a, lo, hi);	
	}
	else{
		//move random entry to "end"
		int rnd = rand() % (hi - lo + 1) + lo;
		rnd = rand() % (hi - lo + 1) + lo;
		
		
		std::swap(a[rnd], a[hi]);
		
		// v is the partitioning element
		int v = a[hi];
		int i = lo - 1, j = hi;
		
		while (true) {
			// Scan left->R as much as possible
			while(a[++i] < v) ;
			// Scan right->L as much as possible
			while(v < a[--j])
				if (j == lo) break;
			if (j <= i) break;
			std::swap(a[i], a[j]);
		}
		// a[i] > v, place pivot element
		std::swap(a[i], a[hi]);
		quicksort(a, lo, i - 1);
		quicksort(a, i + 1, hi);
		return;
	}
}





int main(int argc, char** argv) {
	//seed rng
	srand(time(NULL));
	//set K-value to CMD specified value
	iSort = std::stoi(argv[2]);
	
	//open given input file and read first line (number of elements in file)
	ifstream myFile(argv[1]);
	string in;
	getline(myFile, in, '\n');
	int numElm = std::stoi(in);
	
	//Initialize array of matching size
	int* a = new int[numElm];
	
	// Get ints to sort by reading in from input file
	for(int i = 0; i < numElm; i++){
		getline(myFile, in, '\n');
		a[i] = std::stoi(in);
	}
	
	//sort input
	quicksort(a,0,numElm-1);
	
	//prevent code being optimized away
    int min = a[0];
	
	for(int x =0; x < numElm; x++)
		std::cout << a[x] << std::endl;
	
    delete[] a;
    return min;
}

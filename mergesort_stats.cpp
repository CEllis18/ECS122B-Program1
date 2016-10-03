//Author:		Chris Ellis
//ID#:			991868704
//ECS122B 		Program#1
//FileName		mergesort_stats.cpp
#include <limits>
#include <string>
#include <utility>
#include <cstdio>
#include <iostream>
#include <fstream>
using namespace std;

//complete

#define INFTY std::numeric_limits<int>::max()
#define SUB_B 1
#define SUB_C 2
#define SUB_D 3

bool debug = false;
int recurseCalls = 0; 
int transitions = 0;
int compares = 0;


void printArray(int* a, int lo, int hi){
	cout << "Printing Array"<< endl;
	for(int x = lo; x <= hi; x++){
		cout << "a[" << x << "] = " << a[x] << endl;
	}
	cout << endl;
}




void mergesort(int* a, int lo, int hi) {
    //if less then 3 values, cannot split into tri results, so handle as special base cases
	
	
	if(((hi-lo)+1) <3){
		//if single value, no sorting needed, return
		if(hi-lo == 0){
			return;
		}
		//must be two values, sort
		else{
			//if already in correct order, no sorting needed, return
			//if(lo < hi){
			if(a[lo] < a[hi]){
				compares++;
				return;
			}
			//else swap to become "sorted"
			else{
				int temp = a[lo];
				a[lo] = a[hi];
				a[hi] = temp;
				compares++;
				return;
			}			
		}
	}
	
    // Split array into two (roughly) equal sized subarrays 	
	int bLo;
	int bHi;
	int cLo;
	int cHi;
	int dLo;
	int dHi;
	int numElm = hi-lo+1;
	int numDiv = numElm/3;
	
	//determine boundaries
	//if divisible by 3 perfectly
	if (((hi-lo)+1)%3 == 0){
		bLo = lo;
		bHi = bLo + numDiv - 1;
		cLo = bHi+1;
		cHi = cLo + numDiv - 1;
		dLo = cHi+1;
		dHi = dLo + numDiv - 1;

		// Sort recursively
		recurseCalls +=3;
		mergesort(a, bLo, bHi);
		mergesort(a, cLo, cHi);
		mergesort(a, dLo, dHi);
		
			
		// Copy sorted subarrays to buffers [UPDATE THIS]
		int* b = new int[numDiv + 1];
		int* c = new int[numDiv + 1];
		int* d = new int[numDiv + 1];
		
		int k;
		
		for (k = bLo; k <= bHi; k++){ //copy into b
			b[k-bLo] = a[k];
		}
		b[k-bLo] = INFTY;
		for (k = cLo; k <= cHi; k++){ //copy into c
			c[k-cLo] = a[k];
		}
		c[k-cLo] = INFTY;	
		for (k = dLo; k <= dHi; k++){ //copy into d
			d[k-dLo] = a[k];
		}
		d[k-dLo] = INFTY;	
		
		// Sentinel values for ease of merge implementation
		b[numDiv] = INFTY; c[numDiv] = INFTY; d[numDiv] = INFTY;
		
		
		int x = 0, y = 0, z = 0;
		
		// Merge Step
		int prior = 0;
		
		for(k = lo; k <= hi; k++){
			if(b[x] < c[y]){
				if(b[x] < d[z]){
					if(prior == 0){//if prior hasnt been set
						prior = SUB_B;
					}
					if(prior != SUB_B){
						prior = SUB_B;
						transitions++;
					}
					a[k] = b[x];
					x++;
					compares += 2;
				}
				else{
					if(prior == 0){//if prior hasnt been set
						prior = SUB_D;
					}
					if(prior != SUB_D){
						prior = SUB_D;
						transitions++;
					}
					a[k] = d[z];
					z++;
					compares += 2;
				}
			}
			else if(c[y] < d[z]){
					if(prior == 0){//if prior hasnt been set
						prior = SUB_C;
					}
					if(prior != SUB_C){
						prior = SUB_C;
						transitions++;
					}
				a[k] = c[y];
				y++;
				compares += 2;
			}
			else{
				if(prior == 0){//if prior hasnt been set
					prior = SUB_D;
				}
				if(prior != SUB_D){
					prior = SUB_D;
					transitions++;
				}
				a[k] = d[z];
				z++;
				compares += 2;
			}
		}
		
		
		delete[] b;
		delete[] c;
		delete[] d;
		
		return;
	}
	//if % 1 case
	if(((hi-lo)+1)%3 == 1){
		bLo = lo;
		bHi = bLo + numDiv - 1;
		cLo = bHi+1;
		cHi = cLo + numDiv - 1;
		dLo = cHi+1;
		dHi = dLo + numDiv;		

		// Sort recursively
		recurseCalls +=3;
		mergesort(a, bLo, bHi);
		mergesort(a, cLo, cHi);
		mergesort(a, dLo, dHi);
		
			
		// Copy sorted subarrays to buffers [UPDATE THIS]
		int* b = new int[numDiv + 1];
		int* c = new int[numDiv + 1];
		int* d = new int[numDiv + 2];
		
		
		
		int k;
				
		
		for (k = bLo; k <= bHi; k++) //copy into b
			b[k-bLo] = a[k];
		b[k-bLo] = INFTY;	
		
		for (k = cLo; k <= cHi; k++) //copy into c
			c[k-cLo] = a[k];
		c[k-cLo] = INFTY;	
		
		for (k = dLo; k <= dHi; k++) //copy into d
			d[k-dLo] = a[k];
		d[k-dLo] = INFTY;
		
		
		// Sentinel values for ease of merge implementation
		b[numDiv] = INFTY; c[numDiv] = INFTY; d[numDiv+1] = INFTY;
				
		int x = 0, y = 0, z = 0;
		
		// Merge Step
		int prior = 0;
		
		for(k = lo; k <= hi; k++){
			if(b[x] < c[y]){
				if(b[x] < d[z]){
					if(prior == 0){//if prior hasnt been set
						prior = SUB_B;
					}
					if(prior != SUB_B){
						prior = SUB_B;
						transitions++;
					}
					a[k] = b[x];
					x++;
					compares += 2;
				}
				else{
					if(prior == 0){//if prior hasnt been set
						prior = SUB_D;
					}
					if(prior != SUB_D){
						prior = SUB_D;
						transitions++;
					}
					a[k] = d[z];
					z++;
					compares += 2;
				}
			}
			else if(c[y] < d[z]){
					if(prior == 0){//if prior hasnt been set
						prior = SUB_C;
					}
					if(prior != SUB_C){
						prior = SUB_C;
						transitions++;
					}
				a[k] = c[y];
				y++;
				compares += 2;
			}
			else{
				if(prior == 0){//if prior hasnt been set
					prior = SUB_D;
				}
				if(prior != SUB_D){
					prior = SUB_D;
					transitions++;
				}
				a[k] = d[z];
				z++;
				compares += 2;
			}
		}
		
		
		delete[] b;
		delete[] c;
		delete[] d;
		
		return;
	}
	//if % 2 case
	else{
		bLo = lo;
		bHi = bLo + numDiv;
		cLo = bHi+1;
		cHi = cLo + numDiv;
		dLo = cHi+1;
		dHi = dLo + numDiv -1;		

		// Sort recursively
		recurseCalls +=3;
		mergesort(a, bLo, bHi);
		mergesort(a, cLo, cHi);
		mergesort(a, dLo, dHi);
				
		
		// Copy sorted subarrays to buffers [UPDATE THIS]
		int* b = new int[numDiv + 2];
		int* c = new int[numDiv + 2];
		int* d = new int[numDiv + 1];
		
		int k;
				
		
		for (k = bLo; k <= bHi; k++){ //copy into b
			b[k-bLo] = a[k];
		}
		b[k-bLo] = INFTY;
			
		for (k = cLo; k <= cHi; k++){ //copy into c
			c[k-cLo] = a[k];
		}
		c[k-cLo] = INFTY;
		
		for (k = dLo; k <= dHi; k++){ //copy into d
			d[k-dLo] = a[k];
		}
		d[k-dLo] = INFTY;
		
			
		// Sentinel values for ease of merge implementation
		b[numDiv+1] = INFTY; c[numDiv+1] = INFTY; d[numDiv] = INFTY;
		
		int x = 0, y = 0, z = 0;
		
		// Merge Step
		int prior = 0;
		
		for(k = lo; k <= hi; k++){
			if(b[x] < c[y]){
				if(b[x] < d[z]){
					if(prior == 0){//if prior hasnt been set
						prior = SUB_B;
					}
					if(prior != SUB_B){
						prior = SUB_B;
						transitions++;
					}
					a[k] = b[x];
					x++;
					compares += 2;
				}
				else{
					if(prior == 0){//if prior hasnt been set
						prior = SUB_D;
					}
					if(prior != SUB_D){
						prior = SUB_D;
						transitions++;
					}
					a[k] = d[z];
					z++;
					compares += 2;
				}
			}
			else if(c[y] < d[z]){
					if(prior == 0){//if prior hasnt been set
						prior = SUB_C;
					}
					if(prior != SUB_C){
						prior = SUB_C;
						transitions++;
					}
				a[k] = c[y];
				y++;
				compares += 2;
			}
			else{
				if(prior == 0){//if prior hasnt been set
					prior = SUB_D;
				}
				if(prior != SUB_D){
					prior = SUB_D;
					transitions++;
				}
				a[k] = d[z];
				z++;
				compares += 2;
			}
		}
		
		delete[] b;
		delete[] c;
		delete[] d;
		
		return;
	}	
}

int main(int argc, char** argv) {
    //int size;
    // Get number of ints to sort
    //scanf("%d", &size);
	
	//expected input will be of form:
	//merge.out sourceFileName
	
	//cout << "argc = " << argc << endl;
	//cout << "argv[1] = " << argv[1] << endl;
	
	//open given input file and read first line (number of elements in file)
	ifstream myFile(argv[1]);
	string in;
	getline(myFile, in, '\n');
	int numElm = std::stoi(in);
	
	//int* a = new int[argc-1];
	//Initialize array of matching size
	int* a = new int[numElm];
	
    // Get ints to sort by reading in from input file
    /*for (int i = 1; i < argc; ++i)
        a[i - 1] = std::stoi(argv[i]);*/	
	for(int i = 0; i < numElm; i++){
		getline(myFile, in, '\n');
		a[i] = std::stoi(in);
	}
		
    //mergesort(a, 0, argc-2);
	//Sort input
	mergesort(a,0,numElm-1);
    // For safety: make sure code is not optimized away
    int min = a[0];
	
	/*for(int x = 0; x < numElm ; x++){
			std::cout << "a[" << x << "] = " << a[x] << std::endl;
		}*/
	/*for(int x =0; x < numElm; x++)
		std::cout << a[x] << std::endl;*/
	
	//cout << "Complete" << endl;
	
	cout << "Recursive_Calls " << recurseCalls << endl;
	cout << "Transitions " << transitions << endl;
	cout << "Compares " << compares << endl;
	
    delete[] a;
    return min;
}
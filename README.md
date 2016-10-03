# ECS122B-Program1
Tri-merge mergesort vs randomized pivot quicksort for my algorithms class at UC Davis. Utilizes bash scripts to automate running tests.

Purpose: Compare the runtime of a merge sort that breaks data into three groups (instead of traditional two) to the run time of a quicksort using a randomized pivot. 

The "randomized" pivot was done by modifying an end-based pivot algorithm to swap the "end" position with a random element from within the valid sorting range.

Results: The merge sort had a consistent run time compared to the randomized quicksort. This was most likely due to the set number of recursive calls that had to be made for data sets of the same length. 

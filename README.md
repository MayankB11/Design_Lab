# Design_Lab
Autumn Semester 2019-2020
Under [Professor Abhijit Das](http://cse.iitkgp.ac.in/~abhij/)

## Holy Grail of Logology

main.cpp   
  * Brute force implementation, Time complexity O(nCs*s!) where n is the total no of words in dictionary of length s
  * Trie approach (non-parallel), Time complexity O(n*(s-1)^26), will be even less as pruning is applied
         
p_main.cpp 
  * Trie approach (parallel), Time complexity O((n*(s-1)^26)/t), where t is the number of threads

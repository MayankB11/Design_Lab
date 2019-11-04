# Design_Lab 
Autumn Semester 2019-2020  <br />
Under the supervision of [Professor Abhijit Das](http://cse.iitkgp.ac.in/~abhij/) 

## Holy Grail of Logology [[Link](https://en.wikipedia.org/wiki/Word_square#Order_10_squares)]

main.cpp   
  * Brute force implementation, Time complexity O(nCs*s!) where n is the total no of words in dictionary of length s
  * Trie approach (non-parallel), Time complexity O(n*(s-1)^26)
         
p_main.cpp 
  * Trie approach (parallel), Time complexity O((n*(s-1)^26)/t), where t is the number of threads

Both the trie approaches also have pruning

To compile:<br /> 
  * g++ main.cpp main.h -lpthread
  
To run:  (input.txt contains no of words first and then words as input)<br />
  * ./a.out 
  
All constants are defined in main.h

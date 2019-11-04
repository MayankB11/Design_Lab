#include <bits/stdc++.h>
#include <algorithm>	
#include <unordered_map>
#include <stdio.h>

using namespace std;

#define FILE_NAME "input.txt"       // contains words of length SQUARE_SIZE
#define SQUARE_SIZE 3
#define NO_OF_APLHABETS 26
#define LOWEST_ASCII_ALPHABET 'a'

struct  Trie
{
	struct Trie* children[NO_OF_APLHABETS];
	bool isEnd;
};
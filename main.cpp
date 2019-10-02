#include<bits/stdc++.h>
#include<stdio.h>

using namespace std;

#define FILE_NAME "input.txt"       // contains words of length SQUARE_SIZE
#define SQUARE_SIZE 4
#define NO_OF_APLHABETS 26
#define LOWEST_ASCII 'a'

struct  Trie
{
	struct Trie children[NO_OF_APLHABETS]*;
	bool isEnd;
};



int main(){

	freopen("input.txt","r",stdin);

	string str;
	vector<string> v;

	Trie* root = new Trie;

	for(int i=0;i<NO_OF_APLHABETS;i++){
		root->children[i]=NULL;
	}

	root->isEnd = false;

	return 0;
}
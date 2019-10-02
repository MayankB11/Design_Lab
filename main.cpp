#include<bits/stdc++.h>
#include <algorithm>	
#include<stdio.h>

using namespace std;

#define FILE_NAME "input.txt"       // contains words of length SQUARE_SIZE
#define SQUARE_SIZE 4
#define NO_OF_APLHABETS 26
#define LOWEST_ASCII_ALPHABET 'a'

struct  Trie
{
	struct Trie* children[NO_OF_APLHABETS];
	bool isEnd;
};

void Trie_init(Trie* t){
	for(int i=0;i<NO_OF_APLHABETS;i++){
		t->children[i]=NULL;
	}

	t->isEnd = false;
}

void Trie_add(Trie* t,string str){
	for(int i=0;i<str.length();i++){
		if(t->children[str[i]-LOWEST_ASCII_ALPHABET]==NULL){
			t->children[str[i]-LOWEST_ASCII_ALPHABET]=new Trie;
			t=t->children[str[i]-LOWEST_ASCII_ALPHABET];
			Trie_init(t);
		}else{
			t=t->children[str[i]-LOWEST_ASCII_ALPHABET];
		}
	}
	t->isEnd=true;
}

bool Trie_search(Trie* t,string str){
	transform(str.begin(),str.end(),str.begin(),::tolower);
	for(int i=0;i<str.length();i++){
		t=t->children[str[i]-LOWEST_ASCII_ALPHABET];
		if(t==NULL){
			return false;
		}
	}
	return t->isEnd;
}

void Trie_build_check(Trie* t){
	cout<<Trie_search(t,"bit")<<endl;
	cout<<Trie_search(t,"top")<<endl;
	cout<<Trie_search(t,"pen")<<endl;
	cout<<Trie_search(t,"cat")<<endl;
	cout<<Trie_search(t,"hat")<<endl;
	cout<<Trie_search(t,"rat")<<endl;
}

int main(){

	freopen("input.txt","r",stdin);

	string str;
	vector<string> v;

	Trie* root = new Trie;

	Trie_init(root);

	int no_of_words;
	cin>>no_of_words;

	for(int i=0;i<no_of_words;i++){
		cin>>str;
		transform(str.begin(),str.end(),str.begin(),::tolower);
		v.push_back(str);
		Trie_add(root,str);
	}

	// Trie_build_check(root);
	
	return 0;
}
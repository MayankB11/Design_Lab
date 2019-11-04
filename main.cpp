#include <bits/stdc++.h>
#include <algorithm>	
// #include <unordered_map>
#include<stdio.h>

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
	// checks for three letter words 
	// Initial checker
	cout<<Trie_search(t,"bit")<<endl;
	cout<<Trie_search(t,"top")<<endl;
	cout<<Trie_search(t,"pen")<<endl;
	cout<<Trie_search(t,"cat")<<endl;
	cout<<Trie_search(t,"hat")<<endl;
	cout<<Trie_search(t,"rat")<<endl;
}


bool checkIsSol(vector<string> &v){
	for(int i=0;i<v.size();i++){
		for(int j=i;j<v.size();j++){
			if(v[i][j]!=v[j][i]){
				return false;
			}
		}
	}
	return true;
}

void getSolutionsBruteForceHelper(vector<string> &v,vector<string> &possible_solution,unordered_map<int,int> &m){
	
	if(possible_solution.size()==SQUARE_SIZE){
		bool isSol = checkIsSol(possible_solution);
		// isSol=true;
		if(isSol){
			// print here
			for(int i=0;i<possible_solution.size();i++){
				cout<<possible_solution[i]<<endl;
			}
			cout<<endl;
		}
		return;
	}

	for(int k=0;k<v.size();k++){
		if(m[k]!=1){
			m[k]=1;
			possible_solution.push_back(v[k]);
			getSolutionsBruteForceHelper(v,possible_solution,m);
			possible_solution.pop_back();
			m[k]=0;
		}
	}
}

void getSolutionsBruteForce(vector<string> &v){
	unordered_map<int,int> m;
	vector<string> possible_solution;
	for(int k=0;k<v.size();k++){
		m[k]=1;
		possible_solution.push_back(v[k]);
		getSolutionsBruteForceHelper(v,possible_solution,m);
		possible_solution.pop_back();
		m[k]=0;
	}
}

// Using k pointers in trie approach approach

void kPointersTrie(vector<string> &v){

	if(v.size()==0){
		cout<<"No strings given"<<endl;
	}

	int k = v[0].length();
	Trie* pointers = new Trie[k];
	string str;

	for(int i=0;i<v.size();i++){
		str = v[i];
		for(int i=0;i<str.length();i++){
			
		}
	}
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
		assert(str.length()==SQUARE_SIZE);
		transform(str.begin(),str.end(),str.begin(),::tolower);
		v.push_back(str);
		Trie_add(root,str);
	}

	sort(v.begin(),v.end());

	// Trie_build_check(root);

	getSolutionsBruteForce(v);

	return 0;
}
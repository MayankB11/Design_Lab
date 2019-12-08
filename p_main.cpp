#include <thread>
#include "main.h"

int word_index; // INDEX position in the vector array to be shared by the threads
mutex mtx;
Trie* trie_root;
vector<string> v;


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

// word_no for the ith word
// letter in the word_no

void checkSolution(Trie *t, Trie** pointers, int word_no, int depth, vector<string> &sol){   
 
	// cout<<"Word_no: "<<word_no<<"\tDepth: "<<depth<<endl;

	if(depth==SQUARE_SIZE){
		depth = word_no+1;
		word_no++;
	}


	if(word_no==SQUARE_SIZE){
		mtx.lock();

		// cout<<"---------------------------- Solution found ----------------------------"<<endl; 
		for(int i=0;i<sol.size();i++){
			cout<<sol[i]<<endl;
		}
		cout<<endl;
		// cout<<"------------------------------------------------------------------------"<<endl;
		mtx.unlock();
		return;
	}


	for(int i=0;i<NO_OF_APLHABETS;i++){
		if(pointers[word_no]->children[i]==NULL){  // solution doesn't exist with the current word
			continue;
		}else{

			if(pointers[depth]->children[i]==NULL){  // solution doesn't exist with the depth index word
				continue;
			}

			Trie* cur_word_pointer = pointers[word_no];
			Trie* depth_word_pointer = pointers[depth];

			pointers[word_no] = pointers[word_no]->children[i];
			if(word_no!=depth){
				pointers[depth] = pointers[depth]->children[i];
			}

			sol[word_no][depth] = 'a'+i;
			sol[depth][word_no] = 'a'+i;
			// recursive call for the next letter
			checkSolution(t,pointers,word_no,depth+1,sol);

			pointers[word_no] = cur_word_pointer;

			if(word_no!=depth){
				pointers[depth] = depth_word_pointer;
			}
		}
	}
}

void threadHelper(int thread_id){
	
	Trie *t = trie_root;

	int k = SQUARE_SIZE;
	int flag;
	Trie** pointers = new Trie*[k];
	string str;
	vector<string> sol(k);

	for(int i=0;i<sol.size();i++){
		sol[i] = v[0];
	}


	while(1){

		mtx.lock();

		if(word_index==v.size()){
			return;
		}
		str = v[word_index];
		word_index++;
  		
  		// cout << "thread #" << thread_id << " checking for solutions beginning with : "<<str<<endl;
  		// cout<< "thread #" << thread_id << " word_index "<<word_index-1<<endl;
  		
  		mtx.unlock();


		sol[0]=str;
		// inefficient memory access, column wise TO DO
		for(int j=0;j<str.length();j++){
			sol[j][0] = str[j];
		}

		flag = 1;

		for(int i=0;i<str.length();i++){
			if(t->children[str[i]-LOWEST_ASCII_ALPHABET]==NULL){   // No solution exists with the current string
				flag = 0;
				break;
			}
			pointers[i] = t->children[str[i]-LOWEST_ASCII_ALPHABET];
		}

		if(flag){
			// There might be a possible solution with the current string, need to check
			// cout<<"Checking for solution for words beginning with : "<<str<<endl;
			checkSolution(t,pointers,1,1,sol);
		}else{
			// cout<<"No solution for words beginning with : "<<str<<endl;
		}
	}
}

// Using k pointers in trie approach approach

void kPointersTrie(Trie* t){

	// cout<<Trie_search(t,"ace")<<endl;

	int flag;

	if(v.size()<SQUARE_SIZE){
		// cout<<"Not enough strings given"<<endl;
	}
	
	thread threads[NO_OF_THREADS];

	for(int i=0;i<NO_OF_THREADS;i++){
		threads[i] = thread(threadHelper,i);
	}

	for(int i=0;i<NO_OF_THREADS;i++){
		threads[i].join();
	}
}

int main(){

	freopen(FILE_NAME,"r",stdin);

	string str;

	Trie* root = new Trie;
	trie_root = root;

	Trie_init(root);
	word_index = 0;

	int no_of_words;
	cin>>no_of_words;

	assert(SQUARE_SIZE>0);
	assert(no_of_words>=SQUARE_SIZE);

	for(int i=0;i<no_of_words;i++){
		cin>>str;
		assert(str.length()==SQUARE_SIZE);
		transform(str.begin(),str.end(),str.begin(),::tolower);
		v.push_back(str);
		Trie_add(root,str);
	}

	sort(v.begin(),v.end());

	kPointersTrie(root);

	return 0;
}

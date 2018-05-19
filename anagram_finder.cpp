#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include "time.h"
using namespace std;

struct word_key{
	int count[26];
	bool isValid;
	word_key(){
		for(size_t i=0; i<26; ++i)
			count[i] = 0;
		isValid = false;
	}
	word_key(string word){
		for(size_t i=0; i<26; ++i)
			count[i] = 0;
		int letter_count = 0;
		for(size_t i=0; i<word.length(); ++i){
			if( (word[i]<='z')&&(word[i]>='a') ){
				count[word[i]-'a']++;
				letter_count++;
			}
			else if( (word[i]<='Z')&&(word[i]>='A') ){
				count[word[i]-'A']++;
				letter_count++;
			}
		}
		isValid = (letter_count) ? true : false;
	}
	string getStr(){
		string output;
		for(size_t i=0; i<26; ++i)
			output.push_back((char)count[i]);
		return output;
	}
};

inline bool operator <(const word_key &a, const word_key &b){
	for(size_t i=0; i<26; ++i){
		if(a.count[i] < b.count[i]) return true;
		else if(a.count[i] > b.count[i]) return false;
	}
	return false;//a==b
}

int main(int argc, char** argv){
	if(argc<2) return -1;
#ifdef _WIN32
    clock_t start, finish;
    float elapsed_secs;
#else
	struct timespec start, finish;
	double elapsed_secs;
#endif // _WIN32
	//iterate through text files
	//create sets of anagram
#ifdef _WIN32
	start = clock();
#else
	clock_gettime(CLOCK_MONOTONIC, &start);
#endif
	ifstream file_in;
	string new_word;
	int total_lines = 0;
	unordered_map< string, vector<string> > anagram_map;
	file_in.open(argv[1]);
	if(!file_in.is_open()) return -1;
	while(!file_in.eof()){
		//get new word
		getline(file_in, new_word);
		total_lines++;
		//create a map key to new_word
		word_key key = word_key(new_word);
		//insert into anagram map
		if(key.isValid){
			unordered_map< string, vector<string> >::iterator iter;
			string hash_str = key.getStr();
			iter = anagram_map.find(hash_str);
			if(iter==anagram_map.end()){
				vector<string> new_set(1, new_word);
				anagram_map[hash_str] = new_set;
			}
			else iter->second.push_back(new_word);
		}
	}
	file_in.close();
#ifdef _WIN32
	finish = clock();
	elapsed_secs = (float)(finish-start)/CLOCKS_PER_SEC;
#else
	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed_secs = (finish.tv_sec - start.tv_sec);
	elapsed_secs += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
#endif // _WIN32
	cout << "time elapsed for anagram sets generation: " << \
		elapsed_secs << ", with " << total_lines << \
		" lines processed" << endl;
	//print/output the info of anagram sets(>=3)
#ifdef _WIN32
	start = clock();
#else
	clock_gettime(CLOCK_MONOTONIC, &start);
#endif
	ofstream file_out;
	file_out.open("output.txt");
	int anagram_set_count = 0;
	for(unordered_map< string, vector<string> >::iterator iter = \
			anagram_map.begin(); iter != anagram_map.end(); \
			++iter){
		//check if set is valid
		//if valid, output anagram strings in this set
		if(iter->second.size()>=3){
			anagram_set_count++;
			for(size_t i=0; i<iter->second.size(); ++i){
				if(0==i) file_out << iter->second[i];
				else file_out << ',' << iter->second[i];
			}
			file_out << endl;
		}
	}
	file_out.close();
#ifdef _WIN32
	finish = clock();
	elapsed_secs = (float)(finish-start)/CLOCKS_PER_SEC;
#else
	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed_secs = (finish.tv_sec - start.tv_sec);
	elapsed_secs += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
#endif // _WIN32
	cout << "time elapsed for anagram sets output: " << \
		elapsed_secs << ", with " << anagram_set_count << \
		" total number of anagram sets" << endl;
	//return
	return 0;
}

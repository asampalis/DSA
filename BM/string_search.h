#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <cctype>
#define NO_OF_CHARS 256


class string_key{
public:
	//a vector of pairs that store the answers:
	//1- the number assigned to the question
	//2- the answer to the question
	std::vector<std::vector<std::string>> answers_key{};

	//a vector of the answers to be checked
	//this is the work to be graded
	std::vector<std::vector<std::string>> answers_given{};


	//stores whether the answer is correct or not
	//0 false
	//1 true
	std::vector<bool> score;

	//default constructor 
	string_key();

	//takes in file name and puts data into answer_key and answers_given
	string_key(std::string fname1, std::string fname2);

	//boyer moore
	int caseConvert_bm(std::string data, std::string pat, std::vector<std::vector<std::string>> data_vec);

	int BMSearch(std::string data, std::string pat, std::vector<std::vector<std::string>> data_vec);

	void badCharHeuristic(std::string pat, int size, int badChar[NO_OF_CHARS]);

	//kmp
	
	//int caseConvert_kmp(std::string ans_data, std::string data, int num);

	//int KMPSearch(std::string ans_data, std::string data, int num);
	
	//void computeLPSArray(std::string pat, int M, std::vector<int> lps);
	

	void printkey();

};

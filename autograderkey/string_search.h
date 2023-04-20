#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
#include <algorithm>

class string_key {
private:
	//a vector of pairs that store the short answers:
	//1- the number assigned to the question
	//2- the answer to the question
	std::vector<std::pair<int, std::string>> short_answers{};

	//a vector of pairs that store the long answers:
	//1- the number assigned to the question
	//2- a vector of strings that stores the key phrases we are looking for in the long answers
	std::vector<std::pair<int, std::vector<std::string>>> long_answers;
	

public:	
	//default constructor 
	string_key();

	//takes in file name and puts data into short answers and long answers 
	string_key(std::string fname);

	//print all short and long answers
	void print_key();
};


//What were grading
class answer_sheet {

};

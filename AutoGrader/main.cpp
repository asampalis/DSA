#include "string_search.h"


bool check_files(std::string fname) {
	std::ifstream file;
	// opening the file
	file.open(fname);

	if (file)
	{
		// printing the success message
		return true;
	}
	else
	{
		// printing the error message
		return false;
	}
}


int main() {

	//Code that drives user choice between normal string search or using the autograder.
	//normal string search just compares two strings
	//auto grade searches multiple lines- tells you whether the question on that line is 
	std::cout << '\n' << '\n' << '\n';
	std::cout << "Input a for string search" << "\n";
	std::cout << "Input b for autograder";
	std::cout << '\n' << '\n' << '\n';
	std::string choice;
	std::string choice2;
	bool chosen = true;
	while (chosen) {
		std::cout << "--->";
		std::cin >> choice;
		std::cout << "\n";
		if (choice == "a") {
			std::cout << "Normal string search chosen";
			chosen = false;
		}
		else if (choice == "b") {
			std::cout << "Autograder chosen";
			chosen = false;
		}
		else {
			std::cout << "Try Again!";
		}
		std::cout << "\n";
	}
	std::cout << "\n" << "\n";
	
	//code that drives the choice of whether the program is case sensetive or not 
	std::cout << "Input a for case sensetive." << "\n";
	std::cout << "Input b for non-case sensetive" << "\n";
	bool chosen2 = true;
	while (chosen2) {
		std::cout << "\n" << "\n";
		std::cout << "--->";
		std::cin >> choice2;
		std::cout << "\n";
		if (choice2 == "a") {
			std::cout << "Case sensetive chosen";
			chosen2 = false;
		}
		else if (choice2 == "b") {
			std::cout << "Non-case sensetive chosen";
			chosen2 = false;
		}
		else {
			std::cout << "Try Again!";
		}
		std::cout << "\n";
	}
	std::cout << "\n";


	//what we should do based off the users given input 

	//a is normal string search
	if (choice == "a") {
		
		//get input files 
		bool a = true;
		std::string fname1;
		std::string fname2;
		while (a) {
			std::cout << "What is the name of the key file" << "\n";
			std::cout << "--->";
			std::cin >> fname1;
			std::cout << "What is the name of the search file" << "\n";
			std::cout << "--->";
			std::cin >> fname2;
			
			if (check_files(fname1) == true && check_files(fname2) == true) {
				a = false;
				std::cout << "Success" << "\n";
			}
			else {
				std::cout << "files failed try again" << "\n";
				std::cout << "\n" << "\n";
			}
		}

		
		string_key key(fname1, fname2);
		

		
		int bm_time;
		int kmp_time;

		//case sensetive
		if (choice2 == "a") 
		{	
			bm_time = key.BMSearch(key.answers_given[0][0], key.answers_key[0][0], key.answers_given);
			//kmp_time = key.KMPSearch(key.answers_key[0][0], key.answers_given[0][0], -1);
		}
		//non case sensetive
		else {
			bm_time = key.caseConvert_bm(key.answers_key[0][0], key.answers_given[0][0], key.answers_given);
			//kmp_time = key.caseConvert_kmp(key.answers_key[0][0], key.answers_given[0][0], -1);
		}
		

		//find the times
		std::cout << bm_time << " " ;
		


	}
	else if (choice == "b") {
		//get input files 
				//get input files 
		bool a = true;
		std::string fname1;
		std::string fname2;
		while (a) {
			std::cout << "What is the name of the Answer key file" << "\n";
			std::cout << "--->";
			std::cin >> fname1;
			std::cout << "What is the name of the Given Answers file" << "\n";
			std::cout << "--->";
			std::cin >> fname2;

			if (check_files(fname1) == true && check_files(fname2) == true) {
				a = false;
				std::cout << "Success" << "\n";
			}
			else {
				std::cout << "files failed try again" << "\n";
				std::cout << "\n" << "\n";
			}
		}


		string_key key(fname1, fname2);
		


		int bm_time;
		int kmp_time;

		//case sensetive
		if (choice2 == "a") {
			
			int kmp_time = 0;
			int bm_time = 0;
			for (int i = 0; i < key.answers_key.size(); i++)
			{
				for (int j = 0; j < key.answers_key[i].size(); j++) {
					//kmp_time += key.KMPSearch(key.answers_key[i][0], key.answers_given[i][j], -1);
					bm_time += key.BMSearch(key.answers_given[i][0], key.answers_key[i][j], key.answers_given);
				}
			}
			std::cout << bm_time << "\n";
			
		}
		//non case sensetive
		else{
			int kmp_time = 0;
			int bm_time = 0;
			for (int i = 0; i < key.answers_key.size(); i++)
			{
				for (int j = 0; j < key.answers_key[i].size(); j++) {
					//kmp_time += key.caseConvert_kmp(key.answers_key[i][0], key.answers_given[i][j], -1);
					bm_time += key.caseConvert_bm(key.answers_given[i][0], key.answers_key[i][j], key.answers_given);
				}
			}
			std::cout << bm_time << "\n";
		}
	}
}

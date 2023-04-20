#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>
#define NO_OF_CHARS 256

void caseConvert(std::string data, std::string pat, std::vector<std::vector<std::string>> data_vec);
void badCharHeuristic(std::string pat, int size, int badChar[NO_OF_CHARS]);
void BMSearch(std::string data, std::string pat, std::vector<std::vector<std::string>> data_vec);

int main(int argc, char*argv[]){
    //file to read from
    std::string input_file(argv[1]);
    //pattern to find
    std::string pat(argv[2]);

    //asks user if they want to the pattern to be case-sensitive
    std::string case_sense;
    std::cout << "Case Sensitive? yes or no" << std::endl;
    std::cin >> case_sense;
    std::cout << std::endl;

    //reads the file
    std::ifstream file(input_file);
    std::string line;

    //pushes the strings to data and data_vec
    std::string data;
    std::vector<std::vector<std::string>> data_vec;
    std::string s;
    while (std::getline(file, line)){
        std::istringstream ss(line);
        data_vec.push_back({});
        while (ss >> s) {
            data.append(s);
            data.append(" ");
            data_vec.back().push_back(s);
        }
    }

    //if user chooses not to care about lower/upper case
    if (case_sense == "no"){
        caseConvert(data, pat, data_vec);
    }
    else if (case_sense == "yes"){
        //std::cout << pat << std::endl;
        BMSearch(data, pat, data_vec);
    }
    else{
        std::cout << "check spelling" << std::endl;
    }

    return 0;
}

void caseConvert(std::string data, std::string pat, std::vector<std::vector<std::string>> data_vec){
    int length = pat.length();
    char c;

    //goes through pat and changes the characters to lower case if they are upper case
    for (int i = 0; i < length; i++) {
        c = pat[i];
        if (isupper(c)) {
            pat[i] = tolower(c);
        }
    }

    //turns all characters in data to be lower case
    std::transform(data.begin(), data.end(), data.begin(), ::tolower);

    BMSearch(data, pat, data_vec);
}

void BMSearch(std::string data, std::string pat, std::vector<std::vector<std::string>> data_vec){
    //starts the clock to time the time it takes to go through function
    auto start = std::chrono::high_resolution_clock::now();

    //Length of the pattern
    int M = pat.size();
    //Length of the data
    int N = data.size();

    //whether the pattern is present or not
    bool pattern = false;

    //the row of the 2D data vector
    int line;

    int badChar[NO_OF_CHARS];

    badCharHeuristic(pat, M, badChar);

    //index of data_vec
    int idx;

    //shift of pattern with respect to data
    int s = 0;

    //while statement determines the length of data it needs to shift through
    while(s <= (N - M)){

        //for statement used to verify where the word is in the data vector
        //allows the program to output the precise location in the data that the word matched
        line = 0;
        idx = 0;
        for(int i = 0; i <= s; i++){
            if(data[i] == ' '){
                idx++;
            }
            if(idx >= data_vec[line].size()){
                line++;
                idx = 0;
            }
        }

        int j = M - 1;
        //std::cout << "s: " << s << std::endl;
        //std::cout << "data: " << data[s] << std::endl;

        //iterates through the characters being compared starting from the back
        //ends if either all are iterated through, or a character does not match
        while(j >= 0 && pat[j] == data[s + j]){
            j--;
            //std::cout << "j: " << j << std::endl;
        }
        if(j < 0){
            std::cout << "Found pattern on line " << line << " and at index " << idx << " within " << "\"" << data_vec[line][idx] << "\"" << std::endl;
            pattern = true;

            s += (s + M < N)? M-badChar[data[s + j]] : 1;
        }else{
            s += std::max(1, j - badChar[data[s + j]]);
        }
    }
    if(pattern == false){
        std::cout << "Pattern not found in database" << std::endl;
    }

    //stops clock and outputs time in microseconds taken to go through function
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "\n" << "Time taken by KMP function: " << duration.count() << " microseconds" << std::endl;
}

//The preprocessing function for boyer-moore's bad character heuristic
void badCharHeuristic(std::string pat, int size, int badChar[NO_OF_CHARS]){
    for(int i = 0; i < NO_OF_CHARS; i++){
        badChar[i] = -1;
    }

    for(int i = 0; i < size; i++){
        badChar[(int) pat[i]] = i;
    }
}
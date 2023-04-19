#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <chrono>

void caseConvert(std::string pat, std::string data, std::vector<std::vector<std::string>> data_vec);
void KMPSearch(std::string pat, std::string txt, std::vector<std::vector<std::string>> data_vec);
void computeLPSArray(std::string pat, int M, int* lps);

int main(int argc, char*argv[]){

    //file to read from
    std::string input_file(argv[1]);
    //pattern to find
    std::string pat(argv[2]);

    //asks user if they want to the pattern to be case sensitive
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
        caseConvert(pat, data, data_vec);
    }
    else if (case_sense == "yes"){
        //std::cout << pat << std::endl;
        KMPSearch(pat, data, data_vec);
    }
    else{
        std::cout << "check spelling" << std::endl;
    }

    return 0;
}

//converts all character in pat and data to be lowercase, so they always match regardless of lower/upper case
void caseConvert(std::string pat, std::string data, std::vector<std::vector<std::string>> data_vec){
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

    KMPSearch(pat, data, data_vec);
}

//Prints occurrences of data in pat
void KMPSearch(std::string pat, std::string data, std::vector<std::vector<std::string>> data_vec){
    //starts the clock to time the time it takes to go through function
    auto start = std::chrono::high_resolution_clock::now();


    int M = pat.length();
    int N = data.length();

    //whether the pattern is present or not
    bool pattern = false;

    //the row of the 2d data_test vector
    int line = 0;

    //values for pattern
    int lps[M];

    //Preprocess the pattern
    computeLPSArray(pat, M, lps);

    //index for txt
    int i = 0;

    //index for pat
    int j = 0;

    //index for data_vec
    int idx = 0;

    while ((N - i) >= (M - j)){
        if (pat[j] == data[i]){
            j++;
            i++;
            //std::cout << "i: " << i << std::endl;
            //std::cout << "j: " << j << std::endl;
        }

        if (j == M){
            //std::cout << i << std::endl;
            //std::cout << j << std::endl;
            std::cout << "Found pattern on line " << line << " and at index " << idx << " within " << "\"" << data_vec[line][idx] << "\"" << std::endl;
            j = lps[j - 1];
            pattern = true;
        }

        //mismatch after j matches
        else if (i < N && pat[j] != data[i]){

            if (j != 0) {
                j = lps[j - 1];
            }
            else {
                i = i + 1;
            }
        }

        //if there is a space in the data, then idx is increased to go to the next element in data_vec
        if (data[i-1] == ' ') {
            idx++;
            //std::cout << data[i] << std::endl;
            //std::cout << idx << std::endl;
        }

        //used to keep track of new line in file
        if (idx >= data_vec[line].size()){
            //std::cout << idx << std::endl;
            line++;
            idx = 0;
        }

    }

    if (pattern == false) {
        std::cout << "Pattern not found in database" << std::endl;
    }

    //stops clock and outputs time in microseconds taken to go through function
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "\n" << "Time taken by KMP function: " << duration.count() << " microseconds" << std::endl;
}

//Fills lps for given pattern pat
void computeLPSArray(std::string pat, int M, int* lps){
    //length of the previous longest prefix suffix
    int len = 0;

    lps[0] = 0;

    //the loop calculates lps for i = 1 to M-1
    int i = 1;
    while (i < M){
        if (pat[i] == pat[len]){
            len++;
            lps[i] = len;
            i++;
        }
        else{
            if (len != 0){
                len = lps[len - 1];

            }
            else{
                lps[i] = 0;
                i++;
            }
        }
    }
}
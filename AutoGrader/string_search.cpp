#include "string_search.h"
#define NO_OF_CHARS 256

string_key::string_key() {

}

//puts data into 2d vectors
string_key::string_key(std::string fname1, std::string fname2) {
    //answer key
    //reads the data file
    std::ifstream file(fname1);
    std::string line;

    //pushes the strings to data_vec
    std::string data;
    std::string s;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string question_num;
        std::string question_answer;
        answers_key.push_back({});

        std::getline(ss, question_num, '-');
        while (std::getline(ss, question_answer, ',')) {
            answers_key.back().push_back(question_answer);
        }

    }

    //reads the answer file
    std::ifstream file2(fname2);
    std::string line2;

    //pushes the strings to ans_data_vec
    std::string ans_data;
    std::string s2;
    while (std::getline(file2, line2)) {
        std::istringstream ss2(line2);



        std::string question_num2;
        std::string question_answer2;
        answers_given.push_back({});

        std::getline(ss2, question_num2, '-');
        std::getline(ss2, question_answer2);
        answers_given.back().push_back(question_answer2);
    }

}

//-----------------bm


int string_key::caseConvert_bm(std::string data, std::string pat, std::vector<std::vector<std::string>> data_vec) {
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

    int count = BMSearch(data, pat, data_vec);
    return count;
}



int string_key::BMSearch(std::string data, std::string pat, std::vector<std::vector<std::string>> data_vec) {
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
    while (s <= (N - M)) {

        //for statement used to verify where the word is in the data vector
        //allows the program to output the precise location in the data that the word matched
        line = 0;
        idx = 0;

        int j = M - 1;
    

        //iterates through the characters being compared starting from the back
        //ends if either all are iterated through, or a character does not match
        while (j >= 0 && pat[j] == data[s + j]) {
            j--;
            
        }
        if (j < 0) {
            std::cout << pat << " found. " << "\n";
            
            pattern = true;

            s += (s + M < N) ? M - badChar[data[s + j]] : 1;
        }
        else {
            s += std::max(1, j - badChar[data[s + j]]);
        }
    }
    if (pattern == false) {
        std::cout << pat << " not found. " << '\n';
        
    }

    //stops clock and outputs time in microseconds taken to go through function
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Time taken by BM function: " << duration.count() << " microseconds" << "\n" << "\n";

    return duration.count();
}

//The preprocessing function for boyer-moore's bad character heuristic
void string_key::badCharHeuristic(std::string pat, int size, int badChar[NO_OF_CHARS]) {
    int i;
    for (int i = 0; i < NO_OF_CHARS; i++) {
        badChar[i] = -1;
    }

    for (int i = 0; i < size; i++) {
        badChar[(int)pat[i]] = i;
    }
}

//-----------------kmp


//converts all character in pat and data to be lowercase, so they always match regardless of lower/upper case

int string_key::caseConvert_kmp(std::string ans_data, std::string data, int num) {
    //count used for the time it takes to go through the KMPSearch function
    int count;

    int length = ans_data.length();
    char c;

    //goes through pat and changes the characters to lower case if they are upper case
    for (int i = 0; i < length; i++) {
        c = ans_data[i];
        if (isupper(c)) {
            ans_data[i] = tolower(c);
        }
    }

    //turns all characters in data to be lower case
    std::transform(data.begin(), data.end(), data.begin(), ::tolower);

    //returned value of the time
    count = KMPSearch(ans_data, data, num);

    return count;
}


//Prints occurrences of data in pat
int string_key::KMPSearch(std::string ans_data, std::string data, int num) {
    //starts the clock to time the time it takes to go through function
    auto start = std::chrono::high_resolution_clock::now();

    int M = ans_data.length();
    int N = data.length();

    //std::cout << M << std::endl;
    //whether the pattern is present or not
    bool pattern = false;

    //the row of the 2d data_test vector
    int line = 1;

    //values for pattern
    int lps[M];

    //Preprocess the pattern
    computeLPSArray(ans_data, M, lps);

    //index for txt
    int i = 0;

    //index for pat
    int j = 0;

    //index for data_vec
    int idx = 1;

    while ((N - i) >= (M - j)) {

        //if a specified number is chosen, then have that number + 1 equal to the line
        if (num != -1) {
            line = num + 1;
        }

        if (ans_data[j] == data[i]) {
            j++;
            i++;
            //std::cout << "i: " << i << std::endl;
            //std::cout << "j: " << j << std::endl;
        }

        if (j == M) {
            //std::cout << i << std::endl;
            //std::cout << j << std::endl;
            //std::cout << "Found pattern on line " << line << " and at index " << idx << " within " << "\"" << data_vec[line][idx] << "\"" << std::endl;
            std::cout << "Found " << "\"" << ans_data << "\"" << " on line " << line << " and at index " << idx << std::endl;// << " within " << "\"" << data << "\"" << std::endl;
            //ans_data = "";
            j = lps[j - 1];
            pattern = true;
        }

        //mismatch after j matches
        else if (i < N && ans_data[j] != data[i]) {

            if (j != 0) {
                j = lps[j - 1];
            }
            else {
                i = i + 1;
            }
        }

        //if there is a space in the data, then idx is increased to go to the next element in data_vec
        if (data[i - 1] == ' ') {
            idx++;
            //std::cout << data[i] << std::endl;
            //std::cout << idx << std::endl;
        }
    }

    if (pattern == false) {
        std::cout << "\"" << ans_data << "\"" << " not found in database" << std::endl;
    }

    //stops clock and outputs time in microseconds taken to go through function
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Time taken by KMP function: " << duration.count() << " microseconds" << std::endl;
    std::cout << std::endl;

    //returns the time taken to go through the KMPSearch function
    return duration.count();
}

void string_key::computeLPSArray(std::string pat, int M, int* lps) {
    //length of the previous longest prefix suffix
    int len = 0;

    lps[0] = 0;

    //the loop calculates lps for i = 1 to M-1
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = lps[len - 1];

            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void string_key::printkey() {
    for (int i = 0; i < answers_key.size(); i++) {
        for (int j = 0; j < answers_key[i].size(); j++) {
            std::cout << answers_key[i][j] << "\n";
        }
    }
    for (int i = 0; i < answers_given.size(); i++) {
        for (int j = 0; j < answers_given[i].size(); j++) {
            std::cout << answers_given[i][j] << "\n";
        }
    }
}




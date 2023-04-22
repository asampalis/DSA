#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <chrono>

int caseConvert(std::string ans_data, std::string data, int num);
int KMPSearch(std::string ans_data, std::string txt, int num);
void computeLPSArray(std::string pat, int M, int* lps);

int main(int argc, char*argv[]){

    //file to read from
    std::string input_file(argv[1]);
    std::string answer_file(argv[2]);

    //line number to compare (0 is for every line)
    std::string number(argv[3]);
    int num = std::stoi(number) - 1;

    //used for finding amount of time it takes to find the patterns
    int time_count = 0;


    //asks user if they want to the pattern to be case sensitive
    std::string case_sense;
    std::cout << "Case Sensitive? yes or no" << std::endl;
    std::cin >> case_sense;
    std::cout << std::endl;


    //reads the data file
    std::ifstream file(input_file);
    std::string line;

    //pushes the strings to data_vec
    std::string data;
    std::vector<std::vector<std::string>> data_vec;
    std::string s;
    while (std::getline(file, line)){
        std::istringstream ss(line);
        data_vec.push_back({});
        while (ss >> s) {
            data_vec.back().push_back(s);
        }
    }

    //reads the answer file
    std::ifstream file2(answer_file);
    std::string line2;

    //pushes the strings to ans_data_vec
    std::string ans_data;
    std::vector<std::vector<std::string>> ans_data_vec;
    std::string s2;
    while (std::getline(file2, line2)){
        std::istringstream ss2(line2);
        ans_data_vec.push_back({});
        while (ss2 >> s2) {
            ans_data_vec.back().push_back(s2);
        }
    }

    /*for(int i = 0; i < data_vec.size(); i++) {
        for (int j = 0; j < data_vec[i].size(); j++) {
            std::cout << data_vec[i][j] << " ";
        }
        std::cout << std::endl;
    }*/

    //if user input is 0 compares every line of files, else campare the specified line
    if (num == -1) {
        //set line, so line count matches in KMPSearch
        //line is only used as an output and not used in calculations
        int lines = -1;

        //used for when there is more than one string that needs to be searched on a line
        std::string temp;

        //puts all values in ans_data_vec into a single string
        for (int i = 0; i < ans_data_vec.size(); i++) {
            for (int j = 1; j < ans_data_vec[i].size(); j++) {
                ans_data.append(ans_data_vec[i][j]);
                ans_data.append(" ");
            }

            //puts all values on the current line in data_vec into the data string
            for(int k = 1; k < data_vec[i].size(); k++) {
                data.append(data_vec[i][k]);
                data.append(" ");
            }


            //removes the single quote from the answer key string
            ans_data.erase(remove(ans_data.begin(), ans_data.end(), '\''), ans_data.end());

            //line is added each time to keep track of the current line
            lines++;

            //this is so the current line number can be sent as a parameter in the KMPSearch function without adding another parameter
            num = lines;

            //goes into this if statement if there is only 1 string needed to be found, otherwise go to else
            if(ans_data_vec[i].size() == 2) {
                //whether user wants it to be case_sensitive
                if (case_sense == "no") {
                    //adds the time taken each time
                    time_count += caseConvert(ans_data, data, num);

                    //resets both strings for next search
                    ans_data = "";
                    data = "";
                } else if (case_sense == "yes") {
                    time_count += KMPSearch(ans_data, data, num);
                    ans_data = "";
                    data = "";
                } else {
                    std::cout << "check spelling" << std::endl;
                    break;
                }
            }
            else{
                //initial position/length of first space
                int pos = ans_data.find_first_of(' ');

                for(int k = 0; k < ans_data_vec[i].size() - 1; k++) {
                    //temp is used to take one substring at a time in ans_data
                    temp = ans_data.substr(0, pos);

                    //erases the first substring
                    ans_data.erase(0, pos + 1);

                    //finds position/length of new substring
                    pos = ans_data.find_first_of(' ');

                    //std::cout << "temp: " << temp << std::endl;
                    //std::cout << "ans_data: " << ans_data << std::endl;
                    //std::cout << "pos: " << pos << std::endl;

                    //whether user wants it to be case_sensitive
                    if (case_sense == "no") {
                        //adds the time taken each time
                        time_count += caseConvert(temp, data, num);
                    } else if (case_sense == "yes") {
                        time_count += KMPSearch(temp, data, num);
                    } else {
                        std::cout << "check spelling" << std::endl;
                        break;
                    }
                }
                //resets both strings for next search
                ans_data = "";
                data = "";
            }
        }
    }
    else{
        //goes into this if statement if there is only 1 string needed to be found, otherwise go to else
        if(ans_data_vec[num].size() == 2) {
            //loops through the single chosen line and adds the values into the string
            for (int j = 1; j < ans_data_vec[num].size(); j++) {
                ans_data.append(ans_data_vec[num][j]);
                ans_data.append(" ");
            }

            for (int j = 1; j < data_vec[num].size(); j++) {
                data.append(data_vec[num][j]);
                data.append(" ");
            }

            //removes the single quote from the answer key string
            ans_data.erase(remove(ans_data.begin(), ans_data.end(), '\''), ans_data.end());

            if (case_sense == "no") {
                time_count += caseConvert(ans_data, data, num);
            } else if (case_sense == "yes") {
                time_count += KMPSearch(ans_data, data, num);
            } else {
                std::cout << "check spelling" << std::endl;
            }
        }
        else{
            for (int j = 1; j < data_vec[num].size(); j++) {
                data.append(data_vec[num][j]);
                data.append(" ");
            }

            for (int j = 1; j < ans_data_vec[num].size(); j++) {
                ans_data.append(ans_data_vec[num][j]);
                ans_data.append(" ");

                //removes the single quote from the answer key string
                ans_data.erase(remove(ans_data.begin(), ans_data.end(), '\''), ans_data.end());

                if (case_sense == "no") {
                    time_count += caseConvert(ans_data, data, num);
                    ans_data = "";
                } else if (case_sense == "yes") {
                    time_count += KMPSearch(ans_data, data, num);
                    ans_data = "";
                } else {
                    std::cout << "check spelling" << std::endl;
                    break;
                }
            }

        }
    }

    std::cout << "Total time taken by KMP function: " << time_count << " microseconds" << std::endl;

    return 0;
}

//converts all character in pat and data to be lowercase, so they always match regardless of lower/upper case
int caseConvert(std::string ans_data, std::string data, int num){
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
int KMPSearch(std::string ans_data, std::string data, int num){
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

    while ((N - i) >= (M - j)){

        //if a specified number is chosen, then have that number + 1 equal to the line
        if(num != -1){
            line = num + 1;
        }

        if (ans_data[j] == data[i]){
            j++;
            i++;
            //std::cout << "i: " << i << std::endl;
            //std::cout << "j: " << j << std::endl;
        }

        if (j == M){
            //std::cout << i << std::endl;
            //std::cout << j << std::endl;
            //std::cout << "Found pattern on line " << line << " and at index " << idx << " within " << "\"" << data_vec[line][idx] << "\"" << std::endl;
            std::cout << "Found " << "\"" << ans_data << "\"" << " on line " << line << " and at index " << idx << std::endl;// << " within " << "\"" << data << "\"" << std::endl;
            //ans_data = "";
            j = lps[j - 1];
            pattern = true;
        }

        //mismatch after j matches
        else if (i < N && ans_data[j] != data[i]){

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
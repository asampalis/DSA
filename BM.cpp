#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>
#define NO_OF_CHARS 256

int caseConvert(std::string ans_data, std::string data, std::vector<std::vector<std::string>> data_vec, int num);
void badCharHeuristic(std::string pat, int size, int badChar[NO_OF_CHARS]);
int BMSearch(std::string ans_data, std::string data, std::vector<std::vector<std::string>> data_vec, int num);

int main(int argc, char*argv[]){
    //file to read from
    std::string input_file(argv[1]);
    std::string answer_file(argv[2]);

    //line number to compare (0 is for every line)
    std::string number(argv[3]);
    int num = std::stoi(number) - 1;

    //used for finding amount of time it takes to find the patterns
    int time_count = 0;

    //asks user if they want to the pattern to be case-sensitive
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
    /*
    for(int i = 0; i < data_vec.size(); i++) {
        for (int j = 0; j < data_vec[i].size(); j++) {
            std::cout << data_vec[i][j] << " ";
        }
        std::cout << std::endl;
    }*/

    //if user input is 0 compares every line of files, else compare the specified line
    if (num == -1) {
        //set line, so line count matches in BMSearch
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

            //this is so the current line number can be sent as a parameter in the BMSearch function without adding another parameter
            num = lines;

            //goes into this if statement if there is only 1 string needed to be found, otherwise go to else
            if(ans_data_vec[i].size() == 2) {
                //whether user wants it to be case_sensitive
                if (case_sense == "no") {
                    //adds the time taken each time
                    time_count += caseConvert(ans_data, data, data_vec, num);

                    //resets both strings for next search
                    ans_data = "";
                    data = "";
                } else if (case_sense == "yes") {
                    time_count += BMSearch(ans_data, data, data_vec, num);
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
                        time_count += caseConvert(ans_data, data, data_vec, num);
                    } else if (case_sense == "yes") {
                        time_count += BMSearch(ans_data, data, data_vec, num);
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
                time_count += caseConvert(ans_data, data, data_vec, num);
            } else if (case_sense == "yes") {
                time_count += BMSearch(ans_data, data, data_vec, num);
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
                    time_count += caseConvert(ans_data, data, data_vec, num);
                    ans_data = "";
                } else if (case_sense == "yes") {
                    time_count += BMSearch(ans_data, data, data_vec, num);
                    ans_data = "";
                } else {
                    std::cout << "check spelling" << std::endl;
                    break;
                }
            }

        }
    }

    std::cout << "Total time taken by BM function: " << time_count << " microseconds" << std::endl;

    return 0;
}

//converts all character in pat and data to be lowercase, so they always match regardless of lower/upper case
int caseConvert(std::string ans_data, std::string data, std::vector<std::vector<std::string>> data_vec, int num){
    //count used for the time it takes to go through the BMSearch function
    int count;

    int length = ans_data.length();
    char c;

    //goes through ans_data and changes the characters to lower case if they are upper case
    for (int i = 0; i < length; i++) {
        c = ans_data[i];
        if (isupper(c)) {
            ans_data[i] = tolower(c);
        }
    }

    //turns all characters in data to be lower case
    std::transform(data.begin(), data.end(), data.begin(), ::tolower);

    //returned value of the time
    count = BMSearch(ans_data, data, data_vec, num);

    return count;
}

int BMSearch(std::string ans_data, std::string data, std::vector<std::vector<std::string>> data_vec, int num){
    //starts the clock to time the time it takes to go through function
    auto start = std::chrono::high_resolution_clock::now();

    //Length of the pattern
    int M = ans_data.size();
    //Length of the data
    int N = data.size();

    //whether the pattern is present or not
    bool pattern = false;

    //the row of the 2D data vector
    int line;

    int badChar[NO_OF_CHARS];

    badCharHeuristic(ans_data, M, badChar);

    //index of data_vec
    int idx;

    //shift of pattern with respect to data
    int s = 0;

    //while statement determines the length of data it needs to shift through
    while(s <= (N - M)){

        //if a specified number is chosen, then have that number + 1 equal to the line
        if(num != -1){
            line = num + 1;
            idx = 0;
            for(int i = 0; i <= s; i++) {
                if (data[i] == ' ') {
                    idx++;
                }
            }
        }else{
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
        }

        int j = M - 1;
        //std::cout << "s: " << s << std::endl;
        //std::cout << "data: " << data[s] << std::endl;

        //iterates through the characters being compared starting from the back
        //ends if either all are iterated through, or a character does not match
        while(j >= 0 && ans_data[j] == data[s + j]){
            j--;
            //std::cout << "j: " << j << std::endl;
        }
        if(j < 0){
            if(ans_data != ""){
                std::cout << "Found " << "\"" << ans_data << "\"" << " on line " << line << " and at index " << idx << std::endl;
                pattern = true;

                s += (s + M < N)? M-badChar[data[s + j]] : 1;
            }else{
                break;
            }

        }else{
            s += std::max(1, j - badChar[data[s + j]]);
        }
    }
    if(pattern == false){
        if(ans_data != ""){
            std::cout << "\"" << ans_data << "\"" << " not found in database" << std::endl;
        }
    }
    pattern = false;
    //stops clock and outputs time in microseconds taken to go through function
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "\n" << "Time taken by BM function: " << duration.count() << " microseconds" << std::endl;
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

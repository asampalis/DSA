#include "string_search.h"

string_key::string_key() {

}


string_key::string_key(std::string fname) {
    std::ifstream file;
    std::string line;
    std::string entry;
    file.open(fname);
    if (file.fail()) {
        std::cout << "Can't open file\n";
    }
    while (std::getline(file, line)) {          
        std::stringstream streamline(line);
        int x = 0;

        //gets each part of the line and stores as string
        std::string question_type;
        std::string question_num;
        std::string question_answer;

        std::getline(streamline, question_type,'-');
        std::getline(streamline, question_num, '-');
        std::getline(streamline, question_answer, ' ');
        
        //logic on whether to store it as large or small answer
        if (question_type == "s") {
            short_answers.push_back(std::make_pair(stoi(question_num), question_answer));
        }
        else if (question_type == "l") {
            std::string entry;
            std::vector<std::string> temp;
            std::stringstream streamline2(question_answer);
            while (std::getline(streamline2, entry, ',')) {
                std::cout << entry << "\n";
                temp.push_back(entry);
            }
            long_answers.push_back(std::make_pair(stoi(question_num), temp));
        }
    }
    file.close();                                
}

void string_key::print_key() {
    std::cout << "short answer" << "\n";
    for (int i = 0; i < short_answers.size(); i++) {
        std::cout << short_answers[i].first << " " << short_answers[i].second << '\n';
    }
    std::cout << "long answers" << "\n";
    for (int i = 0; i < long_answers.size(); i++) {
        std::cout << long_answers[i].first << " ";
        for (int j = 0; j < long_answers[i].second.size(); j++) {
            std::cout << long_answers[i].second[j] << " ";
        }
        std::cout << '\n';
    }
}

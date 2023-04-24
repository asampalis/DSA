# DSA Project - String Search II
### Implementing the Knuth-Morris-Pratt & Boyer Moore Algorithms
## Project Description:
## Project Structure:
## Compilation Instructions: 
### KMP: 
The IDE used is CLion and the following is an example compile:

&emsp;&emsp;&emsp;&emsp; g++ KMP.cpp -o KMP

## Runtime Instructions:
### KMP:
**CLA Format:** &emsp; grading_file &emsp; answer_key_file &emsp; where_to_search

&emsp;&emsp;&emsp;&emsp; grading_file = the file to read from and search

&emsp;&emsp;&emsp;&emsp; answer_key_file = the file that has the pattern, which will be searched for in the grading_file

&emsp;&emsp;&emsp;&emsp; where_to_search = the line where the program will search for the pattern
</br></br>

**Whole file example:** &emsp; database.txt answer_key.txt 0
</br>
&emsp;&emsp;&emsp;&emsp; -This will go through every line of the two files and search for the pattern that is on each line

**Specific line example:** &emsp; database.txt answer_key.txt 1
</br>
&emsp;&emsp;&emsp;&emsp; -This will go through the first line of the two files and search for the pattern on that line
</br></br>

Once the program is run, it will prompt the user to choose whether they want the pattern to be case-sensitive

## Planning: 
## Sample Inputs and Outputs:

# DSA Project - String Search II
### Implementing the Knuth-Morris-Pratt & Boyer Moore Algorithms
## Project Description:
To be able to showcase the abilities and efficiency of both the Knuth-Morris-Pratt & Boyer-Moore algorithms, we chose to create an auto grader that compares two files, one answer key and one test document and search for matches throughout the two. It also outputs 
## Project Structure:
  we took made an auto grader using string search algorithms Boyer-Moore and Knuth-Morris-Pratt and compared the run times of both the algorithms
## Compilation Instructions: 
### KMP: 
The IDE used is CLion and the following is an example compile:

&emsp;&emsp;&emsp;&emsp; g++ KMP.cpp -o KMP

### BOYER-MOORE:

### COMBINED AUTO-GRADER:
The IDE used is CLion and following is an example compile:

&emsp;&emsp;&emsp;&emsp; g++ main.cpp string_search.cpp -o KMP

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

### BOYER-MOORE:

### COMBINED AUTO-GRADER:
No CLAs.
Options are presented when running. 
First set of options:
-simple string search 
or 
-auto grader

## Input file specifications
Simple string search key text file must only have num and a string seperated by a singular "-".
Example: 
  Input key: 
  1-Hello
  
  Text file to be searched:
  1-Hello everyone today we are learning about the clouds.
  
  

## Planning: 
## Sample Inputs and Outputs:

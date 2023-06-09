# DSA Project - String Search II
### Implementing the Knuth-Morris-Pratt & Boyer Moore Algorithms
## Project Description:
To be able to showcase the abilities and efficiency of both the Knuth-Morris-Pratt & Boyer-Moore algorithms, we chose to create an auto grader that compares two files, one answer key and one test document and search for matches throughout the two. It allows you to chose if you want to grade the entire document vs. just a single question, and it allows you to grade in a case sensative manner or not. You can grade multiple choice questions, true or false questions, math equations, and short short or long answer responses.
## Project Structure:
  we took made an auto grader using string search algorithms Boyer-Moore and Knuth-Morris-Pratt and compared the run times of both the algorithms. To really compare the two algorithms, we created an autograder tailored to each specific algorithm and then one combined autograder.
## Compilation Instructions: 
### KMP: 
The IDE used is CLion and c++ 11. The following is an example compile:

&emsp;&emsp;&emsp;&emsp; g++ KMP.cpp -o KMP

### BOYER-MOORE:
The IDE used is CLion and c++ 11. The following is an example compile:

&emsp;&emsp;&emsp;&emsp; g++ BM.cpp -o BM

### COMBINED AUTO-GRADER:
The IDE used is CLion and c++ 11. The following is an example compile:

&emsp;&emsp;&emsp;&emsp; g++ main.cpp string_search.cpp -o KMP
<br></br>


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
</br>

**Answer key file format:**
</br>
1 a
</br>
2 test
</br>
3 'code' 'language' 'useful'
</br>

**Text file to be searched:**
</br>
1 A
</br>
2 test
</br>
3 This code is a language that is very useful to use.
</br>

### BOYER-MOORE:
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
</br>

**Answer key file format:**
</br>
1 a
</br>
2 test
</br>
3 'code' 'language' 'useful'
</br>

**Text file to be searched:**
</br>
1 A
</br>
2 test
</br>
3 This code is a language that is very useful to use.
</br>

### COMBINED AUTO-GRADER:
No CLAs.
Options are presented when running. 
<br></br>
First set of options:
<br></br>
-simple string search 
<br></br>
or 
<br></br>
-auto grader
<br></br>
You will also have the choice between the string being Case sensetive or not.
 

## Sample Inputs and Outputs:

### COMBINED AUTO-GRADER
**Input Files Specifications**
<br></br>
Simple string search key text file must only have num and a string seperated by a singular "-". Only one line.
<br></br>
**Input key:** 
<br></br>
1-Hello
  
**Text file to be searched:**
<br></br>
1-Hello everyone today we are learning about the clouds.
<br></br>

AutoGrader key text file must only have num and a string seperated by a singular "-". There can be multiple comma sperated string values in a line. Can be multiple lines.
<br></br>
**Input key:** 
<br></br>
1-T
<br>
2-T
<br>
3-9.40
<br>
4-Hello,today,clouds
<br>
  
**Text file to be searched:**
<br></br>
1-T
<br>
2-T
<br>
3-9.30
<br>
4-Hello everyone today we are learning about the clouds.
<br>  
<br></br>
look in output folder for screenshots of output

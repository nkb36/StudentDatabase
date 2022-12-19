# StudentDatabase
Student database project for COSC 051
## Description
The project goal is to develop a database system for student records, which will contain 1) the name of the student, 2) grades of their 5 projects and 2 exams, 3) computed weighted score, 4) and their final letter grade. The program needs to read in from a text file, P4Test.txt is an example input file. And the output is to print out the students' records in the original order, alphabetically descending, and alphabetically ascending orders. Because there is no maximum number of students enrolled, the program will use dynamic memory. To earn extra credits, I have decided to use linked lists rather than vectors and recursions rather than iteration in the program.

In this program, I used a class definition to hold all the associated information of each student's record, with member functions to set the weighted average grade, letter grade, and get all the students' info. I then created a linked list that reads in the input data. To sort the students by names alphabetically, I used selection sort to swap the nodes in the linked list without swapping the data. Details of the selection sort method can be found here: https://www.geeksforgeeks.org/swap-nodes-in-a-linked-list-without-swapping-data/amp/

## Run Instruction
To run the program, do simple command line to compile the source file: g++ -o exe projects4_nambui.cpp
Followed by: ./exe
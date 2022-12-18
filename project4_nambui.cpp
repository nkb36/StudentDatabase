#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

//Each student has a total of 7 grades
const int NumGrade = 7;

//Create class of Student;
class Student
{
    public:
    string name;
    int grade[NumGrade];
    double weighted_grade;
    char letter_grade;
    Student *next; //Declare a pointer of type Student that would hold the address of the next node

    //Function prototypes
    double setWeightedAverage(int grade[]);
    char setLetterGrade (double weighted_grade);
    void getStudentInfo (string name, int gradep[], double weighted_grade, char letter_grade, ofstream &outputFile);

    //Constructor
    Student(Student *p = nullptr) //Initilize a default pointer to NULL
    {next = p;} //Assigning default pointer
};

//List of weights for each grade
const double grade_weights[] = {0.02, 0.10, 0.10, 0.14, 0.14, 0.20, 0.30};

//Prototypes for functions outside of class
int linkedListLength(Student *head);
void sortName (Student ** head, bool sorttype);

int main()
{
    //Opening input and output files
    ifstream inputFile;
    inputFile.open("input.txt");
    ofstream outputFile;
    outputFile.open("output.txt");

    //Temporary variable names to pass in data for objects in linked list
    string name, dummy;
    int project1, project2, project3, project4, project5, exam1, exam2;

    //Pointers to loop through linked list, initially set to null
    Student * head = nullptr;
    Student * lastnode = nullptr;

    while (inputFile >> name >> project1 >> project2 >> project3 >> project4 >> project5 >> exam1 >> exam2 && getline(inputFile, dummy, '\n'))
    {
        Student * newNode = new Student(); //Allocate new memory
        
        //Pass in the data
        newNode->name = name;
        newNode->grade[0] = project1;
        newNode->grade[1] = project2;
        newNode->grade[2] = project3;
        newNode-> grade[3] = project4;
        newNode->grade[4] = project5;
        newNode->grade[5] = exam1;
        newNode->grade[6] = exam2;
        newNode->weighted_grade = newNode->setWeightedAverage(newNode->grade);
        newNode->letter_grade = newNode->setLetterGrade(newNode->weighted_grade);

        //Move pointers one node over
        if (lastnode == nullptr) {head = newNode;
        } else lastnode->next = newNode;
        lastnode = newNode;
    }

    inputFile.close();

    //Using recursive function to count number of nodes in the linked list
    int num_student = linkedListLength(head);
    cout << "The number of students in the class is: ";
    cout << num_student << endl;

    //Create a new pointer to traverse the linked list
    Student *traverse1 = nullptr;
    traverse1 = head;

    //Listing in order of entry
    outputFile << "Listing 1: Order of entry" << endl;
    while (traverse1 != NULL)
    {
        traverse1->getStudentInfo(traverse1->name, traverse1->grade, traverse1->weighted_grade, traverse1->letter_grade, outputFile);
        traverse1 = traverse1->next;
    }

    //Sort students name alphabetical ascending
    sortName(&head, true);
    Student *traverse2 = nullptr;
    traverse2 = head;

    outputFile << "Listing 2: Alphabetical Ascending" << endl;
    while (traverse2 != NULL)
    {
        traverse2->getStudentInfo(traverse2->name, traverse2->grade, traverse2->weighted_grade, traverse2->letter_grade, outputFile);
        traverse2 = traverse2->next;
    }

    //Sort students name alphabetical descending
    sortName(&head, false);
    Student *traverse3 = nullptr;
    traverse3 = head;

    outputFile << "Listing 3: Alphabetical Descending" << endl;
    while (traverse3 != NULL)
    {
        traverse3->getStudentInfo(traverse3->name, traverse3->grade, traverse3->weighted_grade, traverse3->letter_grade, outputFile);
        traverse3 = traverse3->next;
    }

    outputFile.close();
    return 0;
}

//Function to calculate weighted average grade
double Student::setWeightedAverage(int grade[])
{
    double total_weighted_grade = 0;
    for (int i = 0; i < 7; i++)
    {
        total_weighted_grade = total_weighted_grade + grade[i] * grade_weights[i];
    }
    return total_weighted_grade;
}

//Function to get the letter grade based on weighted average grade
char Student::setLetterGrade(double weighted_grade)
{
    char letter_grade = 0;
    if (weighted_grade >= 90) letter_grade = 'A';
    else if (weighted_grade >= 80 & weighted_grade <90) letter_grade = 'B';
    else if (weighted_grade >= 70 & weighted_grade < 80) letter_grade = 'C';
    else if (weighted_grade >= 60 & weighted_grade < 70) letter_grade = 'D';
    else letter_grade = 'F';
    return letter_grade;
}

//Function to print with a for loop accroding to the format
void Student::getStudentInfo (string name, int grade[], double weighted_grade, char letter_grade, ofstream &outputFile)
{
    outputFile << name << endl;
    outputFile << "Projects 0-4: ";
    for (int c = 0; c < 5; c++)
    {
        outputFile << grade[c] << " ";
    }
    outputFile << endl;
    outputFile << "Exams: ";
    for (int c = 5; c < 7; c++)
    {
        outputFile << grade[c] << " ";
    }
    outputFile << endl;
    outputFile << "Weighted Score: " << weighted_grade << endl;
    outputFile << "Grade: " << letter_grade << endl;
    outputFile << endl;
}

//Recursive function to count number of nodes in linked list
int linkedListLength(Student *head)
{
    if (head == NULL)
        return 0;
    else
        return 1 + linkedListLength(head->next);
}

//SelectionSort to sort names of students
void sortName (Student ** head, bool sorttype) //sort alphabet ascending if sorttype = true, sort alphabet descending if sorttype = false
{
    //Pointers for the outer loop of selection sort
    Student * trailCurrent = nullptr;
    Student * Current = *head;

    while (Current != NULL){ //Looping through the list with head
        string ref_name;
        ref_name = Current->name; //Create a temporary variable that holds the name of the current node that head points to

        //Pointers for the inner loop of selection sort
        Student *swap;
        Student *trailswap;

        //Pointers to check for and assign the highest/lowest name to ref_name
        Student *trailChecker = Current;
        Student *Checker = Current->next;

        while (Checker != NULL){ // Looping through the inner list
            int name_diff = (Checker->name).compare(ref_name);
            if (sorttype ? name_diff < 0 : name_diff > 0)
            {
                ref_name = Checker->name; //Assigning ref_name variable to the name of the node pointed to by Checker
                swap = Checker;
                trailswap = trailChecker;
            }
            trailChecker = trailChecker->next;
            Checker = Checker->next;
        }

        //Swapping if ref_name holds a different value than original
        if (ref_name != Current->name){

            //For the case in the beginning where trailCurrent is still at NULL
            if (trailCurrent == NULL) {
                *head = swap;
                trailswap->next = Current;
                Student *temp2 = swap->next;
                swap->next = Current->next;
                Current->next = temp2;

                trailCurrent = swap;
                Current = swap->next;
            }

            //For subsequent cases
            else {
                trailCurrent->next = swap;
                trailswap->next = Current;
                Student * temp1 = swap->next;
                swap->next = Current->next;
                Current->next = temp1;

                trailCurrent = swap;
                Current = swap->next;
            }
        }
        else {
            trailCurrent = Current;
            Current = Current->next;
        }
    }
}


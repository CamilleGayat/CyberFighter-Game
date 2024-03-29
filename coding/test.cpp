#include <iostream> // includes the library about input/output management
#include <stdio.h> // includes libraries from C
#include <string.h>
using namespace std; // we use the namespace "std" from the iostream library to be able to use functions from it

class Person{ // I initialize a class
    const char* gender; // I put some attributes in the class
    int age;

    public: // I set the following code block as "public": it can be used by functions outside the class
    void attribute(const char* gender, int age){ // function to change the attribute of the class, depending on the object's attributes
        Person::gender = gender; // I change the gender from the class to the gender of the object
        Person::age = age; // I change the age from the class to the age of the object
    }
    void displayInfo(){ // function to display the information about the object
        cout << "This person is a " << gender << "." << endl; // "cout" is like "printf" in C. We basically surround the displayed text by "<<", and put cout and endl to begin the display and end the line (this last one works as an \n in C. You can use \n and \t in C++ btw)
        if (age <= 0){ 
            cout << "This person is not even born." << endl;
        }
        else{
            cout << "This person is " << age << " years old." << endl;
        }
    }
}; // do not forget the semicolon after a class :)

void inputGender(char gender[10], int &age){ // function to ask the gender and the age to the user
    cout << "What is your gender, or whatever you are? ";
    cin >> gender; // "cin" is like "getchar" in C. We basically ask o the user a input, and we store the input into a variable (here, the variable gender) with the symbol ">>"
    cout << "What is your age? ";
    cin >> age;
}


int main(){ // the main function, like in C
    Person MyPerson; // we initialize a class named "MyPerson", following the structure of the class "Person"
    char gender[10];
    int age;
    inputGender(gender, age); // we call the function to obtain the input information
    MyPerson.attribute(gender, age); // we call the function which is within the class "Person", but with the name we gave it (here, the class "MyPerson")
    MyPerson.displayInfo();
    return 0;
}
#pragma once
#include <cstring>      //for string manipulation functions
#include <iostream>     //for input-output operations
using namespace std;    //use standard namespace definitions


class MyUnit {
private:
    unsigned short value; //stores the value
    char description[100]; //stores the description

public:
    //constructor
    //pre: none
    //post: initializes value to 0 and description to "unknown"
    MyUnit() {
        value = 0; //initialize value to 0
        strncpy_s(description, "unknown", 99); //initialize description to "unknown"
    }

    //sets the value of the unit
    //pre: n is a non-negative integer
    //post: value is updated to n
    void setValue(int n) {
        value = n; //set value to n
    }

    //gets the current value of the unit
    //pre: none
    //post: returns the current value
    int getValue() const {
        return value; //return value
    }

    //sets the description of the unit
    //pre: d is a valid string
    //post: description is updated to d (truncated if necessary)
    void setDescription(const string& d) {
        strncpy_s(description, d.c_str(), 99); //set description to d
    }

    //gets the current description of the unit
    //pre: none
    //post: returns the current description as a c-string
    const char* getDescription() const {
        return description; //return description
    }

    //overloaded << operator for outputting MyUnit details
    //pre: none
    //post: outputs the value and description to the ostream
    friend ostream& operator<<(ostream&, const MyUnit&);
};

//overloaded << operator for MyUnit class
//pre: obj is a valid MyUnit object
//post: outputs the value and description of the object
ostream& operator<<(ostream& out, const MyUnit& obj) {
    out << "\nvalue: " << obj.getValue(); //output value
    out << "\ndescription: " << obj.getDescription(); //output description
    return out; //return output stream
}

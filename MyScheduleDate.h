#pragma once            //ensure header is included once
#include "MyUnit.h"     //include base class definition
#include <iostream>     //for input-output operations

//class definition for MyScheduleDate
class MyScheduleDate : public MyUnit {
private:
    char type; //type of schedule entry

public:
    //constructor--initializes with default type 'U' for "unscheduled"
    //precondition:none
    //postcondition:creates object with type 'U'
    MyScheduleDate() : type('U') {}

    //setter for type
    //precondition:valid character input
    //postcondition:updates the type attribute
    void setType(char t) {
        type = t;
    }

    //getter for type
    //precondition:none
    //postcondition:returns current type
    char getType() const {
        return type;
    }

    //overloaded << operator for outputting object state
    //precondition:valid ostream object
    //postcondition:outputs formatted type attribute
    friend std::ostream& operator<<(std::ostream& out, const MyScheduleDate& obj) {
        out << "\nType: " << obj.getType(); //output type value
        return out; //return modified stream
    }
};

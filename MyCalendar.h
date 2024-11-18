#pragma once                    //ensure header is included once
#include "MyScheduleDate.h"     //include MyScheduleDate class definition
#include <iostream>             //for input-output operations
#include <ctime>                //for date and time functions
#include <cstring>              //for string manipulation

using namespace std; //simplify code syntax

//class definition for MyCalendar
class MyCalendar {
private:
    unsigned short currentYear; //stores the current year
    unsigned short currentMonth; //stores the current month
    unsigned short currentDay; //stores the current day
    MyScheduleDate scheduleDays[12][31]; //array to hold schedule entries

    //helper function to determine days in a month
    //precondition:valid month and year
    //postcondition:returns number of days in the month
    int getDaysInMonth(int month, int year) const {
        if (month == 2) { //check for February
            return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28;
        }
        if (month == 4 || month == 6 || month == 9 || month == 11) { //check for 30-day months
            return 30;
        }
        return 31; //default for 31-day months
    }

public:
    //constructor initializes calendar to the current system date
    //precondition:none
    //postcondition:calendar set to current date
    MyCalendar() {
        time_t now = time(0); //get current time
        tm localtm = {};
        localtime_s(&localtm, &now); //populate localtm with current date
        currentYear = localtm.tm_year + 1900; //set year
        currentMonth = localtm.tm_mon + 1; //set month
        currentDay = localtm.tm_mday; //set day
    }

    //setter for year
    //precondition:valid year
    //postcondition:updates currentYear
    void setCurrentYear(int year) {
        currentYear = year;
    }

    //getter for year
    //precondition:none
    //postcondition:returns currentYear
    int getCurrentYear() const {
        return currentYear;
    }

    //setter for month
    //precondition:valid month
    //postcondition:updates currentMonth and adjusts currentDay
    void setCurrentMonth(int month) {
        currentMonth = month;
        int maxDays = getDaysInMonth(currentMonth, currentYear);
        if (currentDay > maxDays) {
            currentDay = maxDays; //adjust day if it exceeds max days
        }
    }

    //getter for month
    //precondition:none
    //postcondition:returns currentMonth
    int getCurrentMonth() const {
        return currentMonth;
    }

    //setter for day
    //precondition:valid day
    //postcondition:updates currentDay within month's max days
    void setCurrentDay(int day) {
        int maxDays = getDaysInMonth(currentMonth, currentYear);
        currentDay = (day > maxDays) ? maxDays : day;
    }

    //getter for day
    //precondition:none
    //postcondition:returns currentDay
    int getCurrentDay() const {
        return currentDay;
    }

    //method to calculate the day of the week
    //precondition:valid currentDay, currentMonth, and currentYear
    //postcondition:returns day of the week as a string
    string getDayOfWeek() const {
        const char* days[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
        int d = currentDay;
        int m = currentMonth;
        int y = currentYear;

        if (m < 3) { //adjust for Zeller's algorithm
            m += 12;
            y -= 1;
        }
        int c = y / 100;
        y = y % 100;
        int h = (c / 4 - 2 * c + y + y / 4 + 13 * (m + 1) / 5 + d - 1) % 7;
        return days[(h + 7) % 7];
    }

    //method to get the name of the current month
    //precondition:valid current month
    //postcondition:returns month name as a string
    string getMonthName() const {
        const string months[] = { "January", "February", "March", "April", "May", "June",
                                  "July", "August", "September", "October", "November", "December" };
        return months[currentMonth - 1];
    }

    //method to check if the current year is a leap year
    //precondition:valid currentYear
    //postcondition:returns true if leap year, false otherwise
    bool isLeapYear() const {
        return (currentYear % 4 == 0 && (currentYear % 100 != 0 || currentYear % 400 == 0));
    }

    //method to get awareness description for the current month
    string getMonthAwareness() const {
        const string awareness[] = {
            "Cervical Cancer Awareness Month",
            "American Heart Month",
            "National Kidney Month",
            "Autism Awareness Month",
            "Mental Health Awareness Month",
            "Alzheimer's & Brain Awareness Month",
            "UV Safety Awareness Month",
            "Immunization Awareness Month",
            "Childhood Cancer Awareness Month",
            "Breast Cancer Awareness Month",
            "Lung Cancer Awareness Month",
            "HIV/AIDS Awareness Month"
        };
        return awareness[currentMonth - 1];
    }

    //overloaded prefix increment operator
    //precondition:none
    //postcondition:increments day, adjusts month/year if needed
    MyCalendar& operator++();

    //overloaded postfix increment operator
    //precondition:none
    //postcondition:increments day, adjusts month/year if needed
    MyCalendar operator++(int);

    //overloaded prefix decrement operator
    //precondition:none
    //postcondition:decrements day, adjusts month/year if needed
    MyCalendar& operator--();

    //overloaded postfix decrement operator
    //precondition:none
    //postcondition:decrements day, adjusts month/year if needed
    MyCalendar operator--(int);

    //jump forward a certain number of days
    //precondition:positive number of days
    //postcondition:updates calendar by specified days
    MyCalendar jumpForward(int days);

    //jump backward a certain number of days
    //precondition:positive number of days
    //postcondition:updates calendar by specified days
    MyCalendar jumpBackward(int days);

    //stream output operator
    //precondition:none
    //postcondition:outputs formatted calendar state
    friend ostream& operator<<(ostream& out, const MyCalendar& obj);
};

//implementations for overloaded operators and methods
//prefix increment operator implementation
MyCalendar& MyCalendar::operator++() {
    currentDay++;
    int maxDays = getDaysInMonth(currentMonth, currentYear);
    if (currentDay > maxDays) {
        currentDay = 1;
        currentMonth++;
        if (currentMonth > 12) {
            currentMonth = 1;
            currentYear++;
        }
    }
    return *this;
}

//postfix increment operator implementation
MyCalendar MyCalendar::operator++(int) {
    MyCalendar temp = *this;
    ++(*this);
    return temp;
}

//prefix decrement operator implementation
MyCalendar& MyCalendar::operator--() {
    currentDay--;
    if (currentDay < 1) {
        currentMonth--;
        if (currentMonth < 1) {
            currentMonth = 12;
            currentYear--;
        }
        currentDay = getDaysInMonth(currentMonth, currentYear);
    }
    return *this;
}

//postfix decrement operator implementation
MyCalendar MyCalendar::operator--(int) {
    MyCalendar temp = *this;
    --(*this);
    return temp;
}

//jump forward implementation
MyCalendar MyCalendar::jumpForward(int days) {
    for (int i = 0; i < days; ++i) {
        ++(*this);
    }
    return *this;
}

//jump backward implementation
MyCalendar MyCalendar::jumpBackward(int days) {
    for (int i = 0; i < days; ++i) {
        --(*this);
    }
    return *this;
}

//stream output operator implementation
ostream& operator<<(ostream& out, const MyCalendar& obj) {
    out << "Year: " << obj.getCurrentYear() << ", Month: " << obj.getCurrentMonth() << ", Day: " << obj.getCurrentDay();
    return out;
}

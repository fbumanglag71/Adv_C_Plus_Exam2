#include <iostream>         //for input-output operations
#include <ctime>            //for date and time functions
#include <cctype>           //for character handling
#include <string>           //for string handling
#include <fstream>          //for file operations
#include <iomanip>          //for formatted input/output
#include <limits>           //for numeric limits
#include <vector>           //for dynamic array handling
#include <map>              //for key-value pairs
#include <stdexcept>        //for invalid_argument


#include "MyUnit.h"         //include MyUnit class
#include "MyScheduleDate.h" //include MyScheduleDate class
#include "MyCalendar.h"     //include MyCalendar class

#include "input.h"          //from professor 

using namespace std;        //simplifies code syntax

//function prototypes
int menuOption();
void displayCalendar(MyCalendar& calendar);     //displays current calendar state
void SetCurrentYear(MyCalendar& calendar);      //modifies the current year
void SetCurrentMonth(MyCalendar& calendar);     //modifies the current month
void SetCurrentDay(MyCalendar& calendar);       //modifies the current day
void SetCurrentCalendar(MyCalendar& calendar);  //adjusts the calendar
void SetSystemDate(MyCalendar& calendar);       //syncs calendar with system date
void SetSaveFile(const MyCalendar& calendar);   //saves calendar to file
void SetRestoreFile(MyCalendar& calendar);      //restores calendar from file
void SetScheduleReport(MyCalendar& calendar);   //manages schedule reporting

//function to display the menu options to the user
int menuOption() {
    cout << "\n\tCMPR121 Exam2: MyCalendar - OOP implementations by Francisco Bumanglag\n";
    cout << "\t" << string(80, char(205)); 
    cout << "\n\t A. Setting Current Year "; 
    cout << "\n\t B. Setting Current Month ";
    cout << "\n\t C. Setting Current Day "; 
    cout << "\n\t D. Setting Current Calendar"; 
    cout << "\n\t E. Schedule and Report Dates"; 
    cout << "\n\t" << string(80, char(196)); 
    cout << "\n\t F. Sync to system's date"; 
    cout << "\n\t G. Save calendar to file"; 
    cout << "\n\t H. Restore calendar from file"; 
    cout << "\n\t" << string(80, char(196)); 
    cout << "\n\t X. Exit"; 
    cout << "\n\t" << string(80, char(205)); 
    cout << "\n\tOption: "; //prompt user input

    char choice;
    cin >> choice; //get user choice
    choice = toupper(choice); //convert to uppercase
    return choice; //return choice
}

//main function to control program flow
int main()

{
    MyCalendar calendar; 
    do {
        system("cls"); //clear screen for fresh display
        displayCalendar(calendar); //display current calendar state

        switch (menuOption()) {
        case 'A': //handle setting current year
            SetCurrentYear(calendar);
            break;
        case 'B': //handle setting current month
            SetCurrentMonth(calendar);
            break;
        case 'C': //handle setting current day
            SetCurrentDay(calendar);
            break;
        case 'D': //handle calendar adjustments
            SetCurrentCalendar(calendar);
            break;
        case 'E': //handle schedule reporting
            SetScheduleReport(calendar);
            break;
        case 'F': //sync with system date
            SetSystemDate(calendar);
            break;
        case 'G': //save calendar to file
            SetSaveFile(calendar);
            break;
        case 'H': //restore calendar from file
            SetRestoreFile(calendar);
            break;
        case 'X': //exit program
            exit(1);
            break;
        default: //handle invalid input
            cout << "\t\tError - invalid option. Please re-enter.";
            break;
        }
        cout << "\n";
        system("pause"); //pause for user to view output
    } while (true); //loop until exit

    return EXIT_SUCCESS; //successful program termination
}

//function to set text color to blue
void setColorBlue() {
    cout << "\033[1;34m"; //ANSI code for bright blue text
}

//function to reset text color to default
void resetColor() {
    cout << "\033[0m"; //ANSI code to reset color
}

//function to set text color to gray
void setColorGray() {
    cout << "\033[1;30m"; //ANSI code for gray text
}

//function to get the year description in words (e.g., 2024 -> "Two Thousand Twenty Four")
string getYearInWords(int year) {
    const string thousands[] = { "", "One Thousand", "Two Thousand", "Three Thousand", "Four Thousand",
                                "Five Thousand", "Six Thousand", "Seven Thousand", "Eight Thousand", "Nine Thousand" };
    const string hundreds[] = { "", "One Hundred", "Two Hundred", "Three Hundred", "Four Hundred",
                               "Five Hundred", "Six Hundred", "Seven Hundred", "Eight Hundred", "Nine Hundred" };
    const string tens[] = { "", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };
    const string teens[] = { "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen",
                            "Seventeen", "Eighteen", "Nineteen" };
    const string units[] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine" };

    string result;

    //extract thousands, hundreds, tens, and units
    int thousand = year / 1000;
    int hundred = (year % 1000) / 100;
    int ten = (year % 100) / 10;
    int unit = year % 10;

    //construct the result
    if (thousand > 0) result += thousands[thousand] + " ";
    if (hundred > 0) result += hundreds[hundred] + " ";
    if (ten == 1) { //special case for teens (10-19)
        result += teens[unit];
    }
    else { //standard tens and units
        if (ten > 0) result += tens[ten] + " ";
        if (unit > 0) result += units[unit];
    }

    return result;
}

//alternative function to convert an integer year to string representation
string intToString(int num) {
    string result; //stores resulting string representation
    while (num > 0) { //loop to extract digits from integer
        result = char('0' + (num % 10)) + result; //append current digit as char
        num /= 10; //reduce number by removing last digit
    }
    return result; //return string representation of integer
}

//function to get the month name and awareness description
string getMonthName(int month) {
    const string months[] = { "January", "February", "March", "April", "May", "June",
                             "July", "August", "September", "October", "November", "December" };
    return months[month - 1];
}

string getMonthAwareness(int month) {
    //array of awareness month descriptions
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
    return awareness[month - 1]; //return correct awareness for month
}


//zeller's Congruence function to find the weekday
string Zellercongruence(int day, int month, int year) {
    const char* days[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    //array stores weekday names

    if (month < 3) {
        month += 12; //adjust month for January/February
        year -= 1; //adjust year for earlier months
    }

    int c = year / 100; //calculate century value
    year = year % 100; //isolate year within century
    int h = (c / 4 - 2 * c + year + year / 4 + 13 * (month + 1) / 5 + day - 1) % 7;
    //compute zeller's congruence formula

    return days[(h + 7) % 7]; //return the correct weekday
}


//get the starting day of the month (0 = Sunday, 1 = Monday, etc.)
int getStartDayOfMonth(int month, int year) {
    if (month < 3) {
        month += 12; //adjust month for january/february
        year -= 1; //adjust year for early months
    }

    int c = year / 100; //calculate century value
    year = year % 100; //isolate year within century
    int h = (c / 4 - 2 * c + year + year / 4 + 13 * (month + 1) / 5 + 1 - 1) % 7;
    //compute zeller's congruence formula

    return (h + 7) % 7; //return starting day of month
}


//leap year check function
bool checkYear(int year) {
    if (year % 4 == 0) { //check divisibility by four
        if (year % 100 == 0) { //check divisibility by hundred
            return year % 400 == 0; //return true if divisible by 400
        }
        return true; //return true if leap year
    }
    return false; //return false if not leap year
}

//get number of days in the specified month
int getDaysInMonth(int month, int year) {
    if (month == 2) { //check if month is february
        return checkYear(year) ? 29 : 28; //return 29 if leap year
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) { //check for 30-day months
        return 30; //return 30 days for these months
    }
    return 31; //return 31 days for other months
}

//helper function for center alignment
string centerAlign(const string& text, int width) {
    int padding = (width - static_cast<int>(text.size())) / 2;
    return string(padding, ' ') + text + string(width - static_cast<int>(text.size()) - padding, ' ');
}


//initialize year month day values
//setup calendar grid and headers -- boarders
//update schedule and day display
void displayCalendar(MyCalendar& calendar) {
    int year = calendar.getCurrentYear();
    int month = calendar.getCurrentMonth();
    int day = calendar.getCurrentDay();

    //define the width of the calendar grid
    const int calendarWidth = 7 * 11; //7 days, each 11 characters wide

    //top border
    cout << "\t" << char(218) << string(calendarWidth, char(196)) << char(191) << endl;

    //display year
    cout << "\t" << char(179) << " Current year : ";
    setColorBlue();
    cout << setw(calendarWidth - 16) << left << (to_string(year) + " - " + getYearInWords(year) + (calendar.isLeapYear() ? " (leap)" : " (non-leap)"));
    resetColor();
    cout << char(179) << endl;

    //separator
    cout << "\t" << char(195) << string(calendarWidth, char(196)) << char(180) << endl;

    //display month and awareness
    cout << "\t" << char(179) << " Current month: ";
    setColorBlue();
    cout << setw(calendarWidth - 16) << left << (to_string(month) + " - " + getMonthName(month));
    resetColor();
    cout << char(179) << endl;

    cout << "\t" << char(179) << " Awareness    : ";
    setColorBlue();
    cout << setw(calendarWidth - 16) << left << getMonthAwareness(month);
    resetColor();
    cout << char(179) << endl;

    //separator
    cout << "\t" << char(195) << string(calendarWidth, char(196)) << char(180) << endl;

    //display current day
    cout << "\t" << char(179) << " Current day  : ";
    setColorBlue();
    cout << setw(calendarWidth - 16) << left << (to_string(day) + "th - " + Zellercongruence(day, month, year));
    resetColor();
    cout << char(179) << endl;

    //"unschedule" line
    cout << "\t" << char(179) << "              : unschedule" << setw(calendarWidth - 26) << " " << char(179) << endl;

    //separator
    cout << "\t" << char(195) << string(calendarWidth, char(196)) << char(180) << endl;

    //display days of the week
    const char* daysOfWeek[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    cout << "\t" << char(179);
    for (const auto& dayName : daysOfWeek) {
        cout << setw(11) << centerAlign(dayName, 11);
    }
    cout << char(179) << endl;

    //divider below the days of the week
    cout << "\t" << char(195) << string(calendarWidth, char(196)) << char(180) << endl;

    //calculate starting day and number of days in the month
    int startDayOfWeek = getStartDayOfMonth(month, year);
    int daysInMonth = getDaysInMonth(month, year);

    //print the days of the month with shadow boxes for empty spaces
    int currentDayNum = 1;
    bool hasSixthRow = ((daysInMonth + startDayOfWeek) > 35);
    for (int week = 0; week < 6; ++week) { // 6 rows for days
        cout << "\t" << char(179);
        for (int dayOfWeek = 0; dayOfWeek < 7; ++dayOfWeek) {
            if (week == 0 && dayOfWeek < startDayOfWeek) {
                //shadow boxes for days before the 1st of the month
                cout << setw(11) << centerAlign(string(2, char(176)), 11);
            }
            else if (currentDayNum <= daysInMonth) {
                //print the actual days of the month
                string dayStr = to_string(currentDayNum);
                if (currentDayNum == calendar.getCurrentDay()) {
                    setColorBlue();
                    cout << setw(11) << centerAlign(dayStr, 11);
                    resetColor();
                }
                else {
                    cout << setw(11) << centerAlign(dayStr, 11);
                }
                ++currentDayNum;
            }
            else if ((week == 5 && hasSixthRow) || (week == 4 && !hasSixthRow)) {
                //shadow boxes for days after the last day of the month in the last row
                cout << setw(11) << centerAlign(string(2, char(176)), 11);
            }
            else {
                //leave blank for unused rows
                cout << setw(11) << " ";
            }
        }
        cout << char(179) << endl;

        //stop if all days have been printed and there's no 6th row
        if (!hasSixthRow && currentDayNum > daysInMonth) break;
    }

    //solid bottom border
    cout << "\t" << char(192) << string(calendarWidth, char(196)) << char(217) << endl;
}

//function to set the current year
void SetCurrentYear(MyCalendar& calendar) {
    int year = calendar.getCurrentYear();
    string yearInWords = getYearInWords(year);

    char option;
    do {
        system("cls"); //clear the screen for a fresh display of the submenu

        //display the current year
        cout << "\n\tCurrent Year: " << year << " - " << yearInWords << "\n\n";

        //display the submenu
        cout << "\tCalendar - Current Year Menu\n";
        cout << "\t" << string(80, char(205)) << "\n";
        cout << "\t 1. Set Current Year\n";
        cout << "\t" << string(80, char(196)) << "\n";
        cout << "\t 0. Return\n";
        cout << "\t" << string(80, char(205)) << "\n";
        cout << "\tOption: ";
        cin >> option;

        switch (option) {
        case '1': {
            //prompt user to enter a new year
            int newYear;
            cout << "\n\tEnter a year (1...9999): ";
            while (!(cin >> newYear) || newYear < 1 || newYear > 9999) {
                cin.clear(); //clear invalid input
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard invalid input
                cout << "\tInvalid input. Please enter a year between 1 and 9999: ";
            }

            //update the calendar's year and display confirmation
            calendar.setCurrentYear(newYear);
            cout << "\n\tYear updated successfully to " << newYear << ".\n";
            year = newYear; //update local year variable for next loop iteration
            yearInWords = getYearInWords(newYear); // Update year in words
            system("pause"); //pause to allow user to see the update message
            break;
        }
        case '0':
            return; //return to the main menu
        default:
            cout << "\tInvalid option. Please enter a valid option.\n";
            system("pause");
            break;
        }
    } while (option != '0');
}

//function to set the current month
void SetCurrentMonth(MyCalendar& calendar) {
    int month = calendar.getCurrentMonth();
    string monthName = getMonthName(month);

    char option;
    do {
        system("cls"); //clear the screen for a fresh display of the submenu

        //display the current month
        cout << "\n\tCurrent Month: " << month << " - " << monthName << "\n\n";

        //display the submenu
        cout << "\tCalendar - Current Month Menu\n";
        cout << "\t" << string(80, char(205)) << "\n";
        cout << "\t 1. Set Current Month\n";
        cout << "\t" << string(80, char(196)) << "\n";
        cout << "\t 0. Return\n";
        cout << "\t" << string(80, char(205)) << "\n";
        cout << "\tOption: ";
        cin >> option;

        switch (option) {
        case '1': {
            //prompt user to enter a new month
            int newMonth;
            cout << "\n\tEnter a month (1...12): ";
            while (!(cin >> newMonth) || newMonth < 1 || newMonth > 12) {
                cin.clear(); //clear invalid input
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard invalid input
                cout << "\tInvalid input. Please enter a month between 1 and 12: ";
            }

            //update the calendar's month and display confirmation
            calendar.setCurrentMonth(newMonth);
            cout << "\n\tMonth updated successfully to " << newMonth << " - " << getMonthName(newMonth) << ".\n";
            month = newMonth; //update local month variable for next loop iteration
            monthName = getMonthName(newMonth); // Update month name
            system("pause"); //pause to allow user to see the update message
            break;
        }
        case '0':
            return; //return to the main menu
        default:
            cout << "\tInvalid option. Please enter a valid option.\n";
            system("pause");
            break;
        }
    } while (option != '0');
}

//function to set the current day
void SetCurrentDay(MyCalendar& calendar) {
    int day = calendar.getCurrentDay();

    char option;
    do {
        system("cls"); //clear the screen for a fresh display of the submenu

        //display the current day
        cout << "\n\tCurrent Day: " << day << "th\n\n";

        //display the submenu
        cout << "\tCalendar - Current Day Menu\n";
        cout << "\t" << string(80, char(205)) << "\n";
        cout << "\t 1. Set Current Day\n";
        cout << "\t" << string(80, char(196)) << "\n";
        cout << "\t 0. Return\n";
        cout << "\t" << string(80, char(205)) << "\n";
        cout << "\tOption: ";
        cin >> option;

        switch (option) {
        case '1': {
            //prompt user to enter a new day
            int newDay;
            cout << "\n\tEnter a day (1...31): ";
            while (!(cin >> newDay) || newDay < 1 || newDay > 31) {
                cin.clear(); //clear invalid input
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard invalid input
                cout << "\tInvalid input. Please enter a day between 1 and 31: ";
            }

            //update the calendar's day and display confirmation
            calendar.setCurrentDay(newDay);
            cout << "\n\tDay updated successfully to " << newDay << "th.\n";
            day = newDay; //update local day variable for next loop iteration
            system("pause"); //pause to allow user to see the update message
            break;
        }
        case '0':
            return; //return to the main menu
        default:
            cout << "\tInvalid option. Please enter a valid option.\n";
            system("pause");
            break;
        }
    } while (option != '0');
}


//function to display the SetCurrentCalendar submenu
void SetCurrentCalendar(MyCalendar& calendar) {
    string option; //use a string to handle both positive and negative inputs
    int daysToJump;

    do {
        system("cls"); //clear the screen for a fresh display of the submenu
        //display the current date information
        cout << "\n\t" << calendar.getDayOfWeek() << ", " << calendar.getMonthName() << " " << calendar.getCurrentDay() << "th, " << calendar.getCurrentYear() << "\n";
        cout << "\t" << calendar.getCurrentMonth() << "/" << calendar.getCurrentDay() << "/" << calendar.getCurrentYear() << "\n\n";

        //display the submenu header
        cout << "\tMy Calendar Menu\n";
        cout << "\t" << string(80, char(205)) << "\n";
        cout << "\t 1. ++ (pre-increment)\n";
        cout << "\t 2. ++ (post-increment)\n";
        cout << "\t 3. jump forward (+n)\n";
        cout << "\t" << string(80, char(196)) << "\n";
        cout << "\t-1. -- (pre-decrement)\n";
        cout << "\t-2. -- (post-decrement)\n";
        cout << "\t-3. jump backward (-n)\n";
        cout << "\t" << string(80, char(196)) << "\n";
        cout << "\t 0. return\n";
        cout << "\t" << string(80, char(205)) << "\n";
        cout << "\tOption: ";
        cin >> option;

        //interpret options for both positive and negative inputs
        if (option == "1") {  //pre-increment
            ++calendar;
            cout << "\n\tpre-increment:(++)\n\n";
            cout << "\t" << calendar.getDayOfWeek() << ", " << calendar.getMonthName() << " " << calendar.getCurrentDay() << "th, " << calendar.getCurrentYear() << "\n";
            cout << "\t" << calendar.getCurrentMonth() << "/" << calendar.getCurrentDay() << "/" << calendar.getCurrentYear() << "\n";

        }
        else if (option == "2") {  //post-increment
            calendar++;
            cout << "\n\tpost-increment:(++)\n\n";
            cout << "\t" << calendar.getDayOfWeek() << ", " << calendar.getMonthName() << " " << calendar.getCurrentDay() << "th, " << calendar.getCurrentYear() << "\n";
            cout << "\t" << calendar.getCurrentMonth() << "/" << calendar.getCurrentDay() << "/" << calendar.getCurrentYear() << "\n";

        }
        else if (option == "3") {  //jump forward
            cout << "\n\tEnter an integer (n): ";
            while (!(cin >> daysToJump) || daysToJump < 1) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\tInvalid input. Please enter a positive integer: ";
            }
            calendar.jumpForward(daysToJump);
            cout << "\n\tjump forward(" << daysToJump << ")...\n\n";
            cout << "\t" << calendar.getDayOfWeek() << ", " << calendar.getMonthName() << " " << calendar.getCurrentDay() << "th, " << calendar.getCurrentYear() << "\n";
            cout << "\t" << calendar.getCurrentMonth() << "/" << calendar.getCurrentDay() << "/" << calendar.getCurrentYear() << "\n";

        }
        else if (option == "-1") {  //pre-decrement
            --calendar;
            cout << "\n\tpre-decrement:(--)\n\n";
            cout << "\t" << calendar.getDayOfWeek() << ", " << calendar.getMonthName() << " " << calendar.getCurrentDay() << "th, " << calendar.getCurrentYear() << "\n";
            cout << "\t" << calendar.getCurrentMonth() << "/" << calendar.getCurrentDay() << "/" << calendar.getCurrentYear() << "\n";

        }
        else if (option == "-2") {  //post-decrement
            calendar--;
            cout << "\n\tpost-decrement:(--)\n\n";
            cout << "\t" << calendar.getDayOfWeek() << ", " << calendar.getMonthName() << " " << calendar.getCurrentDay() << "th, " << calendar.getCurrentYear() << "\n";
            cout << "\t" << calendar.getCurrentMonth() << "/" << calendar.getCurrentDay() << "/" << calendar.getCurrentYear() << "\n";

        }
        else if (option == "-3") {  //jump backward
            cout << "\n\tEnter an integer (n): ";
            while (!(cin >> daysToJump) || daysToJump < 1) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\tInvalid input. Please enter a positive integer: ";
            }
            calendar.jumpBackward(daysToJump);
            cout << "\n\tjump backward(" << daysToJump << ")...\n\n";
            cout << "\t" << calendar.getDayOfWeek() << ", " << calendar.getMonthName() << " " << calendar.getCurrentDay() << "th, " << calendar.getCurrentYear() << "\n";
            cout << "\t" << calendar.getCurrentMonth() << "/" << calendar.getCurrentDay() << "/" << calendar.getCurrentYear() << "\n";

        }
        else if (option == "0") {
            return;  //exit the submenu and return to the main menu

        }
        else {
            cout << "\tInvalid option. Please enter a valid option.\n";
        }

        cout << "\n";
        system("pause"); //pause to allow the user to view the result before displaying the menu again
    } while (option != "0");
}




//schedule report structure
struct ScheduleEntry {
    int day;
    string description;
    char type; // 'R', 'A', 'H', or 'P'
};

//map to store schedule entries for each month
map<int, vector<ScheduleEntry>> schedule;


void SetScheduleReport(MyCalendar& calendar) {
    int month = calendar.getCurrentMonth(); //get current calendar month
    int day = calendar.getCurrentDay(); //get current calendar day
    string description = "unschedule"; //initialize description to unschedule
    char type = 'U'; //initialize type to unscheduled


    //function to display the top of the scheduling form with current data
    auto displayScheduleForm = [&]() {
        cout << "\n\tMonth       : " << getMonthName(month) << endl;
        cout << "\tDay         : " << day << endl;
        cout << "\tType        : " << type << endl;
        cout << "\tDescription : " << description << endl;
        cout << "\n\tScheduling Date\n";
        cout << "\t" << string(83, char(205)) << endl;
        cout << "\t1. Schedule a date\n";
        cout << "\t2. Unschedule a date\n";
        cout << "\t" << string(83, char(196)) << endl;
        cout << "\t3. Display year schedules\n";
        cout << "\t4. Display month schedules\n";
        cout << "\t5. Display day schedule\n";
        cout << "\t0. Return\n";
        cout << "\t" << string(83, char(205)) << endl;
        };

    //function to display text with specific colors based on the type
    auto displayColoredText = [](const string& fullText, char type) {
        if (type == 'P') {
            cout << "\033[41;30m" << fullText << "\033[0m"; //red background, black font for personal
        }
        else if (type == 'H') {
            cout << "\033[42;30m" << fullText << "\033[0m"; //green background, black font for holiday
        }
        else if (type == 'A') {
            cout << "\033[37m" << fullText << "\033[0m"; //default white font for awareness
        }
        else {
            cout << "\033[37m" << fullText << "\033[0m"; //default white font for unscheduled or other types
        }
        };

    //function to determine the correct suffix for a given day
    auto getDayWithSuffix = [](int day) {
        if (day % 10 == 1 && day % 100 != 11) return to_string(day) + "st";
        if (day % 10 == 2 && day % 100 != 12) return to_string(day) + "nd";
        if (day % 10 == 3 && day % 100 != 13) return to_string(day) + "rd";
        return to_string(day) + "th";
        };

    bool stayInForm = true; //controls loop continuation for scheduling menu
    while (stayInForm) { //main menu loop for scheduling form display
        system("cls"); //clears the screen for each iteration
        displayScheduleForm(); //displays options for scheduling choices

        int choice;
        cout << "\tOption: ";
        cin >> choice; //user input for scheduling menu option
        if (cin.fail() || choice < 0 || choice > 5) { //validates input within range
            cin.clear(); //clears invalid input state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discards excess invalid input
            cout << "\tError: Please enter a number between 0 and 5.\n";
            continue; //restores loop continuation on invalid input
        }

        switch (choice) { //handles user menu selection input
        case 1: {
            //schedule a date (same as before)
            int newMonth, newDay; //variables to hold user inputs
            string newDescription; //description for schedule entry
            char newType; //type character for entry

            cout << "\n\tSpecify a month (1...12): ";
            while (!(cin >> newMonth) || newMonth < 1 || newMonth > 12) { //validates month input range
                cin.clear(); //clears input error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discards invalid input characters
                cout << "\tInvalid month. Please enter a number between 1 and 12: ";
            }

            cout << "\tSpecify a day (1...30): ";
            while (!(cin >> newDay) || newDay < 1 || newDay > 30) { //validates day input range
                cin.clear(); //clears input error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discards invalid input characters
                cout << "\tInvalid day. Please enter a number between 1 and 30: ";
            }

            cout << "\tEnter a description: ";
            cin.ignore(); //clears input buffer for description
            getline(cin, newDescription); //retrieves multi-word user description

            cout << "\tSpecify a type (R-return, A-awareness, H-holiday, or P-personal): ";
            while (true) { //continuously checks valid type input
                cin >> newType; //gets schedule type character
                newType = toupper(newType); //converts input type to uppercase
                if (newType == 'R' || newType == 'A' || newType == 'H' || newType == 'P') break; //exits loop on valid input
                cout << "\tInvalid type. Enter R, A, H, or P: ";
            }

            if (newType == 'R') { // handles unscheduled return type
                cout << "\n\tDate has NOT been scheduled or rescheduled.\n";
            }
            else {
                //add new schedule entry and update the current display variables
                schedule[newMonth].push_back({ newDay, newDescription, newType }); //adds new schedule entry
                month = newMonth; //update display month in the form
                day = newDay; //update display day
                description = newDescription; //update display description
                type = newType; //update display type
                cout << "\n\tSUCCESS: Date has been successfully scheduled.\n";
            }
            break; //exits case after scheduling
        }

        case 2: { //unschedule a date
            int unscheduleMonth, unscheduleDay; //variables for unschedule month and day

            cout << "\n\tSpecify a month (1...12): ";
            while (!(cin >> unscheduleMonth) || unscheduleMonth < 1 || unscheduleMonth > 12) { //validate month input range
                cin.clear(); //clear error state for input
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard invalid characters
                cout << "\tInvalid month. Please enter a number between 1 and 12: ";
            }

            cout << "\tSpecify a day (1...30): ";
            while (!(cin >> unscheduleDay) || unscheduleDay < 1 || unscheduleDay > 30) { //validate day input range
                cin.clear(); //clear error state for input
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard invalid characters
                cout << "\tInvalid day. Please enter a number between 1 and 30: ";
            }

            bool removed = false; //flag to track unschedule success
            auto& entries = schedule[unscheduleMonth]; //reference to month schedule entries
            for (auto it = entries.begin(); it != entries.end(); ++it) { //iterate through entries
                if (it->day == unscheduleDay) { //check for matching day
                    entries.erase(it); //remove the entry
                    removed = true; //set removal flag to true
                    break; //exit loop after removal
                }
            }

            if (removed) { //if date successfully unscheduled
                cout << "\n\tSUCCESS: Date has been successfully unscheduled.\n";
                if (month == unscheduleMonth && day == unscheduleDay) { //reset description if it matches current day
                    description = "unschedule"; //set to unscheduled
                    type = 'U'; //set type to unscheduled
                }
            }
            else {
                cout << "\n\tNo schedule found for the specified date.\n";
            }
            break; //exit case 2
        }

        case 3: { //display all year schedules
            for (int m = 1; m <= 12; ++m) { //iterate through all months
                cout << "\t" << getMonthName(m) << " : ";
                if (schedule.find(m) == schedule.end() || schedule[m].empty()) { //check if month has entries
                    displayColoredText("No scheduled dates for the month.", 'U'); //show no dates message
                    cout << endl;
                }
                else {
                    for (const auto& entry : schedule[m]) { //iterate through entries of the month
                        string fullText = getDayWithSuffix(entry.day) + " - " + entry.description + " (" + entry.type + ")";
                        displayColoredText(fullText, entry.type); //display formatted entry text
                        cout << endl;
                    }
                }
            }
            break; //exit case 3
        }

        case 4: { //display schedules for a specific month
            int displayMonth; //variable for specific month input
            cout << "\n\tSpecify a month (1...12): ";
            while (!(cin >> displayMonth) || displayMonth < 1 || displayMonth > 12) { //validate month input
                cin.clear(); //clear error state for input
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard invalid characters
                cout << "\tInvalid month. Please enter a number between 1 and 12: ";
            }

            cout << "\n\n\t" << getMonthName(displayMonth) << " : "; //added new line before month display
            if (schedule.find(displayMonth) == schedule.end() || schedule[displayMonth].empty()) { //check if month has entries
                displayColoredText("No scheduled dates for the month.", 'U'); //show no dates message
                cout << endl;
            }
            else {
                for (const auto& entry : schedule[displayMonth]) { //iterate through month entries
                    string fullText = getDayWithSuffix(entry.day) + " - " + entry.description + " (" + entry.type + ")";
                    displayColoredText(fullText, entry.type); //display formatted entry text
                    cout << endl;
                }
            }
            break; //exit case 4
        }

        case 5: { //display schedule for a specific day
            int specificMonth, specificDay; //variables for month and day input
            cout << "\n\tSpecify a month (1...12): ";
            while (!(cin >> specificMonth) || specificMonth < 1 || specificMonth > 12) { //validate month input
                cin.clear(); //clear error state for input
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard invalid characters
                cout << "\tInvalid month. Please enter a number between 1 and 12: ";
            }

            cout << "\tSpecify a day (1...30): ";
            while (!(cin >> specificDay) || specificDay < 1 || specificDay > 30) { //validate day input
                cin.clear(); //clear error state for input

                cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard invalid characters
                cout << "\tInvalid day. Please enter a number between 1 and 30: ";
            }

            const auto& entries = schedule[specificMonth]; //reference to specific month entries
            bool found = false; //flag to track if entry found
            cout << "\n\n\t" << getMonthName(specificMonth) << " : "; //added new line before specific day display

            for (const auto& entry : entries) { //iterate through specific month entries
                if (entry.day == specificDay) { //check for matching day
                    string fullText = getDayWithSuffix(entry.day) + " - " + entry.description + " (" + entry.type + ")";
                    displayColoredText(fullText, entry.type); //display formatted entry text
                    cout << endl;
                    found = true; //set found flag to true
                    break; //exit loop after finding entry
                }
            }
            if (!found) { //if no entry found
                displayColoredText("No schedule found for the specified date.", 'U'); //show no entry message
                cout << endl;
            }
            break; //exit case 5
        }

        case 0: //handle exit case
            stayInForm = false; //set loop continuation flag to false
            break; //exit case 0
        }

        if (stayInForm) { //check if still in menu
            cout << "\n";
            system("pause"); //pause for user to see output
        }
    }

}

//function to sync the calendar date to the system date
void SetSystemDate(MyCalendar& calendar) {
    //get the current system date and time
    time_t now = time(0);
    tm localtm = {};
    localtime_s(&localtm, &now);

    //update calendar fields with system date values
    calendar.setCurrentYear(localtm.tm_year + 1900);
    calendar.setCurrentMonth(localtm.tm_mon + 1);
    calendar.setCurrentDay(localtm.tm_mday);     
}

//XOR key for basic encryption and decryption
const char XOR_KEY = 0x5A;

//helper function for XOR encryption and decryption
string xorEncryptDecrypt(const string& data) {
    string result = data;
    for (char& c : result) {
        c ^= XOR_KEY;
    }
    return result;
}

//option G - Save calendar to file with encryption
void SetSaveFile(const MyCalendar& calendar) {
    // Construct filename based on the current year
    string filename = to_string(calendar.getCurrentYear()) + ".DAT";
    ofstream outFile(filename, ios::binary);

    if (outFile) {
        //collect data to save
        int year = calendar.getCurrentYear();
        int month = calendar.getCurrentMonth();
        int day = calendar.getCurrentDay();

        //prepare data for saving
        string data(reinterpret_cast<char*>(&year), sizeof(year));
        data.append(reinterpret_cast<char*>(&month), sizeof(month));
        data.append(reinterpret_cast<char*>(&day), sizeof(day));

        //encrypt data
        string encryptedData = xorEncryptDecrypt(data);

        //write encrypted data to file
        outFile.write(encryptedData.c_str(), encryptedData.size());
        outFile.close();
        cout << "\n    SUCCESS: File " << filename << " has been saved.\n";
    }
    else {
        cout << "\n    ERROR: Could not open file for saving.\n";
    }
}

//option H - Restore calendar from file with decryption
void SetRestoreFile(MyCalendar& calendar) {
    string filename;
    cout << "\n\tEnter the full binary (DAT) calendar file name (YYYY.DAT or YYYY.dat): ";
    cin >> filename;

    //convert filename to lowercase for case-insensitive comparison
    string lowerFilename = filename;
    for (char& c : lowerFilename) {
        c = tolower(c);
    }

    //check if the user provided the correct ".dat" file extension
    if (lowerFilename.find(".dat") == string::npos) {
        cout << "\n\tERROR: Incorrect file format. Please include the '.DAT' or '.dat' extension.\n";
        return;
    }

    ifstream inFile(filename, ios::binary); //open the file in binary mode
    if (inFile) {
        //read encrypted data from file
        string encryptedData((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
        inFile.close();

        //decrypt the data
        string decryptedData = xorEncryptDecrypt(encryptedData);

        //validate and load data into calendar object
        if (decryptedData.size() == sizeof(int) * 3) {
            int year, month, day;
            memcpy(&year, decryptedData.data(), sizeof(year));
            memcpy(&month, decryptedData.data() + sizeof(year), sizeof(month));
            memcpy(&day, decryptedData.data() + sizeof(year) + sizeof(month), sizeof(day));

            //validate data ranges before applying to calendar
            if (year >= 1 && year <= 9999 && month >= 1 && month <= 12 && day >= 1 && day <= 31) {
                calendar.setCurrentYear(year);
                calendar.setCurrentMonth(month);
                calendar.setCurrentDay(day);
                cout << "\n\tSUCCESS: Restored calendar from " << filename << ".\n";
            }
            else {
                cout << "\n\tERROR: Invalid calendar data in file.\n";
            }
        }
        else {
            cout << "\n\tERROR: File data corrupted or incompatible.\n";
        }
    }
    else {
        cout << "\n\tERROR: Cannot open file " << filename << ".\n";
    }
}

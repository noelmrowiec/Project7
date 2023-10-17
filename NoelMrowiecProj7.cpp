/*
* Converts 24-hour time to 12-time.
* 
* Author: Noel Mrowiec
* 10April2023
*/
#include <string>
#include <iostream>
#include <iomanip>

// class for expection handling for incorrect time format
class TimeFormatMistake {
public:
    TimeFormatMistake(std::string);
    std::string getErrorMsg();
private:
    std::string errorMsg;
};

//Converts to 12-time 
// returns a string with the 12-hour time (AM/PM)
// Time must be valid 24-hours values
std::string convert12HourTime(int hours, int mins) {
    bool is_AM{ false };
    int new_hours{ 0 };

    new_hours = hours % 12;
    
    if (new_hours == 0) {
        //Midnight or noon case
        new_hours = 12;
        if (hours == 0 || hours == 24)
            //midnight case
            is_AM = true;
        else
            //noon
            is_AM = false;
    }
    else {
        //all other cases
        if (hours > 12)
            is_AM = false;
        else
            is_AM = true;
        
    }

    //add leading zero to mins if less than 10
    std::string new_mins;
    if (mins < 10)
    {
        new_mins.insert(0, "0"); // insert '0' at the beginning of string
        new_mins += std::to_string(mins);
    }
    else
        new_mins = std::to_string(mins);

    std::string time{ std::to_string(new_hours) + ":" + new_mins };
    time += is_AM ? "AM" : "PM";
    return time;
}

// Gets the 24-time from the user and checks if time is valid
// Modifies 'hours' and 'minutes' with user input
//Throws TimeFormatMistake if time is invalid, such as if minutes are 
//greater than 59, hours greater than 24 or less than 0, or if no input
void check24hourTime(int& hours, int& minutes) throw (TimeFormatMistake) {
    //parse out values from time
    //source: https://stackoverflow.com/questions/21870509/how-do-i-read-in-time-input-and-format-the-output

    char colon;
    std::cin >> hours >> colon >> minutes;

    if (std::cin.fail()) {
        //clear out cin
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw TimeFormatMistake("Error: you must enter a valid number for the hours and minutes");
    }

    //clear buffer
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (hours < 0 )
        throw TimeFormatMistake("Hours must be postitive");
    else if (minutes < 0)
        throw TimeFormatMistake("Minutes must be postitive");
    else if (hours > 24 )
        throw TimeFormatMistake("Hours must less than 24");
    else if (minutes > 59)
        throw TimeFormatMistake("Minutes must less than 59");
    else if (hours == 24 && minutes > 0)
        throw TimeFormatMistake("Minutes must be 0 if hours are 24");
}

int main() {

    while (true) {
        int hours, minutes;
        std::cout << "Enter time in 24-hour notation: " << std::endl;
        try {
            check24hourTime(hours, minutes);
        }
        catch (TimeFormatMistake e) {
            std::cout << e.getErrorMsg() << std::endl;
            continue;
        }
        
        std::string time12hours{ convert12HourTime(hours, minutes) };
        std::cout <<  "That is the same as" << std::endl;
        std::cout << time12hours << std::endl;

        //Ask if to repeat
        std::cout << "Again?(y/n)" << std::endl;
        char choice;
        std::cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        else {
            break;
        }
    }
}

// default constructor for error handling class
TimeFormatMistake::TimeFormatMistake(std::string error) : errorMsg{error}
{
}

// gets the error message for error handling class
std::string TimeFormatMistake::getErrorMsg()
{
    return errorMsg;
}

#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) 
{

    long hours = seconds / 3600;
    long minutes = (seconds % 3600) / 60;
    seconds = seconds % 60;

    string time_output = TruncateValues(std::to_string(hours)) + ":" + TruncateValues(std::to_string(minutes)) + ":" + TruncateValues(std::to_string(seconds));
    return time_output; 
}

string Format::TruncateValues(string value)
{
    string return_string{};
    if (value.length() == 0)
    {
        return_string = "00";
    }
    else if (value.length() == 1)
    {
        return_string = "0" + value;
    }
    else
    {
        return_string = value.substr(value.length()-2, 2);
    }
    return return_string;
}
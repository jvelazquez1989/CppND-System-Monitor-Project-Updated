#include <string>

#include "format.h"
#include <math.h>

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
//string Format::ElapsedTime(long seconds[[maybe_unused]]) { 
string Format::ElapsedTime(long seconds) { 
    int hour;
    int minutes;
    int sec;
    string HH = "";
    string MM = "";
    string SS = "";

    hour = seconds/3600.0;
    minutes = (seconds%3600)/60;
    sec = (seconds%3600)%60;
    
    if(hour < 10) {
        HH = "0" + std::to_string(hour);
    }
    else
    {
        HH = std::to_string(hour);
    }

    if(minutes < 10){
        MM = ":0" + std::to_string(minutes);
    }
    else
    {
        MM = ":" + std::to_string(minutes);
    }

    if(sec < 10){
        SS = ":0" + std::to_string(sec);
    }
    else
    {
        SS = ":" + std::to_string(sec);
    }
    
    return HH + MM + SS;
}
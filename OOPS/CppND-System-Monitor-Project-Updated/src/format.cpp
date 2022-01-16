#include <string>

#include "format.h"

using namespace std;

string Format::timeString(int times) {
    string tmp = to_string(times);
    tmp.insert(0, 2 - tmp.length(), '0');
    return tmp;
}

// Done: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) {
    int mins_temp, hours, mins, secs;
    secs = int(seconds%60);
    mins_temp = int(seconds / 60);
    hours = int(mins_temp / 60);
    mins = int(mins_temp % 60);

    string hh_mm_ss = timeString(hours) + ":" +
            timeString(mins) + ":" +
            timeString(secs);
    return hh_mm_ss;
}
#include "Clock.h"

#include <iostream>
#include <stdexcept>

#include "../Utils/FGDN_Tools.h"

Clock::Clock()
{
    //ctor
}

void Clock::setClock(int yr, int mon, int dy, int hr, int mins, int sec) {
    this->seconds = capAmount(sec, 0, 59);
    this->minutes = capAmount(mins, 0, 59);
    this->hours = capAmount(hr, 0, 23);

    this->year = capAmount(yr, 0, 10000);
    this->month = capAmount(mon, 1, 12);
    this->day = capAmount(dy, 1, getNumDays(this->month));

    if (mins < 0) this->minutes = 0;
    else if (mins > 60) this->minutes = mins % 60;
    else this->minutes = mins;
}

void Clock::incrementSec(int deltaSeconds) {
    this->seconds += deltaSeconds;
    this->minutes += this->seconds / 60;
    this->seconds = this->seconds % 60;

    if (this->minutes > 59) {
        this->hours += this->minutes / 60;
        this->minutes = this->minutes % 60;
    }
    else return;

    if (this->hours > 23) {
        this->day += this->hours / 24;
        this->hours = this->hours % 24;
    }
    else return;

    while (this->day > getNumDays(this->month)) {
        this->day -= getNumDays(this->month);
        this->month += 1;

        if (this->month > 12) {
            this->month = 1;
            this->year += 1;
        }
    }
}

std::string Clock::printDateTime() {
    return  std::to_string(this->month) + "/" +
            std::to_string(this->day) + "/" +
            std::to_string(this->year) + " " +
            std::to_string(this->hours) + ":" +
            std::to_string(this->minutes) + ":" +
            std::to_string(this->seconds);
}

int Clock::getNumDays(int monthAmt) {
    switch (monthAmt) {
        // 31 days
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
            break;

        // 30 days
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
            break;

        // 28 or days
        case 2:
            // Leap years
            if ((this->year % 4 == 0 && this->year % 100 != 0) ||
                (this->year % 100 == 0 && this->year % 400 == 0)) return 29;
            else return 28;
            break;

        default:
            std::cerr << "ERROR: getNumDays invalid month number: " << monthAmt << "\n";
            throw std::logic_error("");
    }
}

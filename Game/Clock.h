#ifndef CLOCK_H
#define CLOCK_H

#include <string>

class Clock
{
    public:
        Clock();

        // Note, values out of range will be capped at the min or max value,
        // e.g. setting minutes to 99 will set minutes to 59.
        void setClock(int year, int month, int day, int hour, int minutes, int sec);
        void incrementSec(int deltaSeconds);
        std::string printDateTime();

    protected:

    private:
        int getNumDays(int month);

        int year;
        int month;
        int day;

        int hours;
        int minutes;
        int seconds;
};

#endif // CLOCK_H

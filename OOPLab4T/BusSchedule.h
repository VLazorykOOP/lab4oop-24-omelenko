#ifndef BUS_SCHEDULE_H
#define BUS_SCHEDULE_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct Time {
    int hours;
    int minutes;

    Time(int h = 0, int m = 0) : hours(h), minutes(m) {}
    bool operator==(const Time& other) const 
    {
        return hours == other.hours && minutes == other.minutes;
    }
};

class BusSchedule 
{
private:
    struct Entry 
    {
        string flightNumber;
        Time departureTime;
        Entry(const string& fn, const Time& dt) : flightNumber(fn), departureTime(dt) {}
    };

    vector<Entry> entries;
    int CodeError;              // Код помилки: 0 - OK, 1 - рейс не знайдено

public:
    BusSchedule() : CodeError(0) {}

    void addEntry(const string& flightNumber, const Time& departureTime);

    Time& operator[](const string& flightNumber);

    Time& operator()(const string& flightNumber);

    int getCodeError() const { return CodeError; }

    friend istream& operator>>(istream& is, BusSchedule& schedule);
    friend ostream& operator<<(ostream& os, const BusSchedule& schedule);
};

#endif
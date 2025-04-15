#include "BusSchedule.h"

using namespace std;

void BusSchedule::addEntry(const string& flightNumber, const Time& departureTime) {
    entries.emplace_back(flightNumber, departureTime);
    CodeError = 0; // �������� ������� ���� �������� ���������
}

Time& BusSchedule::operator[](const string& flightNumber) {
    for (auto& entry : entries) {
        if (entry.flightNumber == flightNumber) {
            CodeError = 0;
            return entry.departureTime;
        }
    }
    CodeError = 1; // ���� �� ��������
    static Time defaultTime(-1, -1); // ��������� "�������" ��� ��� �������
    return defaultTime;
}

Time& BusSchedule::operator()(const string& flightNumber) {
    return (*this)[flightNumber]; // ������������� operator[] ��� ���������
}

istream& operator>>(istream& is, BusSchedule& schedule) {
    schedule.entries.clear(); // ������� �������� ���
    int count;
    cout << "Input journey num: ";
    is >> count;
    is.ignore(); // �������� ���������� '\n'

    for (int i = 0; i < count; ++i) {
        string flightNumber;
        int hours, minutes;

        cout << "Journey " << i + 1 << " - Journey num: ";
        getline(is, flightNumber);
        cout << "Departure time (hours minutes): ";
        is >> hours >> minutes;
        is.ignore();

        schedule.addEntry(flightNumber, Time(hours, minutes));
    }
    return is;
}

ostream& operator<<(ostream& os, const BusSchedule& schedule) {
    if (schedule.entries.empty()) {
        os << "Schedule is empty\n";
        return os;
    }
    os << "Bus schedule:\n";
    for (const auto& entry : schedule.entries) {
        os << "Journey: " << entry.flightNumber
            << ", Departure time: " << entry.departureTime.hours << ":"
            << (entry.departureTime.minutes < 10 ? "0" : "") << entry.departureTime.minutes << "\n";
    }
    return os;
}
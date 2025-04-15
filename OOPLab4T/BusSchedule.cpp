#include "BusSchedule.h"

using namespace std;

void BusSchedule::addEntry(const string& flightNumber, const Time& departureTime) {
    entries.emplace_back(flightNumber, departureTime);
    CodeError = 0; // Скидання помилки після успішного додавання
}

Time& BusSchedule::operator[](const string& flightNumber) {
    for (auto& entry : entries) {
        if (entry.flightNumber == flightNumber) {
            CodeError = 0;
            return entry.departureTime;
        }
    }
    CodeError = 1; // Рейс не знайдено
    static Time defaultTime(-1, -1); // Повертаємо "порожній" час для помилки
    return defaultTime;
}

Time& BusSchedule::operator()(const string& flightNumber) {
    return (*this)[flightNumber]; // Використовуємо operator[] для спрощення
}

istream& operator>>(istream& is, BusSchedule& schedule) {
    schedule.entries.clear(); // Очищаємо попередні дані
    int count;
    cout << "Input journey num: ";
    is >> count;
    is.ignore(); // Ігноруємо залишковий '\n'

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
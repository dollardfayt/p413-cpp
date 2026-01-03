#include <iostream>

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date(int day = 1, int month = 1, int year = 2000);

    void incrementDay();

    Date& operator++();
    Date operator++(int);
    Date& operator--();
    Date operator--(int);
    Date& operator+=(int days);
    Date& operator-=(int days);
    bool operator()(int d, int m, int y);

    friend bool operator==(const Date& d1, const Date& d2);
    friend bool operator!=(const Date& d1, const Date& d2);
    friend bool operator>(const Date& d1, const Date& d2);
    friend bool operator<(const Date& d1, const Date& d2);
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
    friend std::istream& operator>>(std::istream& is, Date& date);

    Date& operator=(const Date& other);

    friend Date operator+(const Date& date, int days);
    friend Date operator-(const Date& date, int days);

    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

private:
    bool isLeapYear(int year) const;
    int daysInMonth(int month, int year) const;

};


Date::Date(int day, int month, int year) : day(day), month(month), year(year) {}

void Date::incrementDay() {
    int daysInCurrentMonth = daysInMonth(month, year);
    day++;
    if (day > daysInCurrentMonth) {
        day = 1;
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
}
Date& Date::operator++() {
    incrementDay();
    return *this;
}

Date Date::operator++(int) {
    Date temp = *this;
    incrementDay();
    return temp;
}

Date& Date::operator--() {
    day--;
    if (day < 1) {
        month--;
        if (month < 1) {
            month = 12;
            year--;
        }
        day = daysInMonth(month, year);
    }
    return *this;
}

Date Date::operator--(int) {
    Date temp = *this;
    day--;
    if (day < 1) {
        month--;
        if (month < 1) {
            month = 12;
            year--;
        }
        day = daysInMonth(month, year);
    }
    return temp;
}

Date& Date::operator+=(int days) {
    for (int i = 0; i < days; ++i) {
        incrementDay();
    }
    return *this;
}

Date& Date::operator-=(int days) {
    for (int i = 0; i < days; ++i) {
        --(*this);
    }
    return *this;
}

bool Date::operator()(int d, int m, int y) {
    return (day == d && month == m && year == y);
}

bool operator==(const Date& d1, const Date& d2) {
    return (d1.day == d2.day && d1.month == d2.month && d1.year == d2.year);
}

bool operator!=(const Date& d1, const Date& d2) {
    return !(d1 == d2);
}

bool operator>(const Date& d1, const Date& d2) {
    if (d1.year > d2.year) return true;
    if (d1.year < d2.year) return false;
    if (d1.month > d2.month) return true;
    if (d1.month < d2.month) return false;
    return d1.day > d2.day;
}

bool operator<(const Date& d1, const Date& d2) {
    return !(d1 > d2 || d1 == d2);
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << date.day << "/" << date.month << "/" << date.year;
    return os;
}

std::istream& operator>>(std::istream& is, Date& date) {
    is >> date.day >> date.month >> date.year;
    return is;
}

Date& Date::operator=(const Date& other) {
    if (this != &other) {
        day = other.day;
        month = other.month;
        year = other.year;
    }
    return *this;
}

Date operator+(const Date& date, int days) {
    Date newDate = date;
    newDate += days;
    return newDate;
}

Date operator-(const Date& date, int days) {
    Date newDate = date;
    newDate -= days;
    return newDate;
}

bool Date::isLeapYear(int year) const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int Date::daysInMonth(int month, int year) const {
    switch (month) {
    case 2:
        return isLeapYear(year) ? 29 : 28;
    case 4: case 6: case 9: case 11:
        return 30;
    default:
        return 31;
    }
}

int main() {
    Date today(17, 12, 2025);
    Date tomorrow = today;
    tomorrow++;
    std::cout << "Tomorrow: " << tomorrow << std::endl;

    Date yesterday = today;
    --yesterday;
    std::cout << "Yesterday: " << yesterday << std::endl;

    Date future = today + 10;
    std::cout << "10 days from now: " << future << std::endl;

    if (today > yesterday) {
        std::cout << "Today is after yesterday" << std::endl;
    }

    if (today(17, 12, 2025)) {
        std::cout << "Today is 17/12/2025" << std::endl;
    }

    Date someDate;
    std::cout << "Enter a date (day month year): ";
    std::cin >> someDate;
    std::cout << "You entered: " << someDate << std::endl;

    return 0;
}

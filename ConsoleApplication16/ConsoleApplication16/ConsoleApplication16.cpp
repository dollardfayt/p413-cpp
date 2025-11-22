#include <iostream>

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date() : day(1), month(1), year(2000) {}
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    void incrementDay() {
        day++;
        if (day > 31) {
            day = 1;
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
    }

    Date& operator++() {
        incrementDay();
        return *this;
    }

    Date operator++(int) {
        Date temp = *this;
        incrementDay();
        return temp;
    }

    Date& operator--() {
        day--;
        if (day < 1) {
            day = 31;
            month--;
            if (month < 1) {
                month = 12;
                year--;
            }
        }
        return *this;
    }

    Date operator--(int) {
        Date temp = *this;
        day--;
        return temp;
    }

    bool operator!=(const Date& other) const {
        return (day != other.day || month != other.month || year != other.year);
    }

    bool operator==(const Date& other) const {
        return (day == other.day && month == other.month && year == other.year);
    }

    bool operator>(const Date& other) const {
        if (year > other.year) return true;
        if (year < other.year) return false;
        if (month > other.month) return true;
        if (month < other.month) return false;
        return day > other.day;
    }

    bool operator<(const Date& other) const {
        return !(*this > other || *this == other);
    }

    Date& operator=(const Date& other) {
        day = other.day;
        month = other.month;
        year = other.year;
        return *this;
    }

    Date& operator+=(int days) {
        for (int i = 0; i < days; ++i) {
            incrementDay();
        }
        return *this;
    }

    Date& operator-=(int days) {
        for (int i = 0; i < days; ++i) {
            --(*this);
        }
        return *this;
    }

    int operator()(int target_year) const {
        return year - target_year;
    }

    friend std::ostream& operator<<(std::ostream& os, const Date& date) {
        os << date.day << "/" << date.month << "/" << date.year;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Date& date) {
        is >> date.day >> date.month >> date.year;
        return is;
    }
};

int main() {
    Date date1(10, 11, 2025);
    Date date2 = date1;

    std::cout << "Date1: " << date1 << std::endl;
    std::cout << "Date2: " << date2 << std::endl;

    date1++;
    std::cout << "Date1++: " << date1 << std::endl;

    ++date2;
    std::cout << "++Date2: " << date2 << std::endl;

    if (date1 != date2) {
        std::cout << "Dates are not equal" << std::endl;
    }

    date1 += 5;
    std::cout << "Date1 += 5: " << date1 << std::endl;
    std::cout << "Year diff with  2020: " << date1(2020) << std::endl;
    std::cout << "Enter a new date (day month year): ";
    std::cin >> date1;
    std::cout << "New Date1: " << date1 << std::endl;
    return 0;
}

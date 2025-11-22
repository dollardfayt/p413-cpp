#include <iostream>

class Fraction {
private:
    int numerator;
    int denominator;

    int gcd(int a, int b) {
        while (b) {
            a %= b;
            std::swap(a, b);
        }
        return a;
    }

    void simplify() {
        int common = gcd(std::abs(numerator), std::abs(denominator));
        numerator /= common;
        denominator /= common;

        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    Fraction(int num = 0, int den = 1) : numerator(num), denominator(den) {
        if (denominator == 0) {
            std::cerr << "Ошибка: Знаменатель не может быть равен нулю." << std::endl;
            denominator = 1;
        }
        simplify();
    }

    void print() const {
        std::cout << numerator << "/" << denominator;
    }

    Fraction operator+(const Fraction& other) const {
        int newNum = (numerator * other.denominator) + (other.numerator * denominator);
        int newDen = denominator * other.denominator;
        return Fraction(newNum, newDen);
    }

    Fraction operator-(const Fraction& other) const {
        int newNum = (numerator * other.denominator) - (other.numerator * denominator);
        int newDen = denominator * other.denominator;
        return Fraction(newNum, newDen);
    }

    Fraction operator*(const Fraction& other) const {
        int newNum = numerator * other.numerator;
        int newDen = denominator * other.denominator;
        return Fraction(newNum, newDen);
    }

    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) {
            std::cerr << "Ошибка: Деление на ноль." << std::endl;
            return Fraction(0, 1);
        }
        int newNum = numerator * other.denominator;
        int newDen = denominator * other.numerator;
        return Fraction(newNum, newDen);
    }

    Fraction& operator+=(const Fraction& other) {
        numerator = (numerator * other.denominator) + (other.numerator * denominator);
        denominator = denominator * other.denominator;
        simplify();
        return *this;
    }

    bool operator==(const Fraction& other) const {
        return (numerator == other.numerator) && (denominator == other.denominator);
    }

    bool operator!=(const Fraction& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& os, const Fraction& fraction) {
        os << fraction.numerator << "/" << fraction.denominator;
        return os;
    }

    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }
};

int main() 
{
    setlocale(LC_ALL, "Russian");
    Fraction a(1, 2);
    Fraction b(1, 4);
    Fraction c = a + b;
    Fraction d = a - b;
    Fraction e = a * b;
    Fraction f = a / b;

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "a + b = " << c << std::endl;
    std::cout << "a - b = " << d << std::endl;
    std::cout << "a * b = " << e << std::endl;
    std::cout << "a / b = " << f << std::endl;

    a += b;
    std::cout << "a += b: " << a << std::endl;

    Fraction g(3, 4);
    if (a == g) {
        std::cout << "a == g is true" << std::endl;
    }

    return 0;
}

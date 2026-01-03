#include <iostream>
#include <numeric>

class Fraction {
private:
    int numerator;
    int denominator;

    int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
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
            std::cerr << "Ошибка: Знаменатель не может быть равен нулю. Установлен знаменатель 1." << std::endl;
            denominator = 1;
        }
        simplify();
    }

    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }

    Fraction operator+(const Fraction& other) const {
        int newNumerator = numerator * other.denominator + other.numerator * denominator;
        int newDenominator = denominator * other.denominator;
        return Fraction(newNumerator, newDenominator);
    }

    Fraction operator-(const Fraction& other) const {
        int newNumerator = numerator * other.denominator - other.numerator * denominator;
        int newDenominator = denominator * other.denominator;
        return Fraction(newNumerator, newDenominator);
    }

    Fraction operator*(const Fraction& other) const {
        int newNumerator = numerator * other.numerator;
        int newDenominator = denominator * other.denominator;
        return Fraction(newNumerator, newDenominator);
    }

    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) {
            std::cerr << "Ошибка: Деление на ноль." << std::endl;
            return Fraction(0, 1);
        }
        int newNumerator = numerator * other.denominator;
        int newDenominator = denominator * other.numerator;
        return Fraction(newNumerator, newDenominator);
    }

    friend std::ostream& operator<<(std::ostream& out, const Fraction& fraction) {
        out << fraction.numerator;
        if (fraction.denominator != 1) {
            out << "/" << fraction.denominator;
        }
        return out;
    }

    Fraction operator-() const {
        return Fraction(-numerator, denominator);
    }
};

int main() {
    Fraction a(1, 2);
    Fraction b(1, 4);

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;

    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "a - b = " << a - b << std::endl;
    std::cout << "a * b = " << a * b << std::endl;
    std::cout << "a / b = " << a / b << std::endl;

    Fraction c(3, -6);
    std::cout << "c = " << c << std::endl;
    std::cout << "-c = " << -c << std::endl;


    return 0;
}

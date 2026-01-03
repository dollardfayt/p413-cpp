#include <iostream>
#include <cmath>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return abs(a);
}

class Fraction {
private:
    int numerator;
    int denominator;

    void simplify() {
        if (denominator == 0) throw std::invalid_argument("Denominator cannot be zero");

        int divisor = gcd(numerator, denominator);
        numerator /= divisor;
        denominator /= divisor;

        if (denominator < 0) {
            numerator *= -1;
            denominator *= -1;
        }
    }

public:
    Fraction(int num = 0, int den = 1) : numerator(num), denominator(den) { simplify(); }

    void set(int num, int den) {
        numerator = num;
        denominator = den;
        simplify();
    }

    Fraction operator+(const Fraction& other) const {
        Fraction result(
            numerator * other.denominator + other.numerator * denominator,
            denominator * other.denominator
        );
        result.simplify();
        return result;
    }

    Fraction operator-(const Fraction& other) const {
        Fraction result(
            numerator * other.denominator - other.numerator * denominator,
            denominator * other.denominator
        );
        result.simplify();
        return result;
    }

    Fraction operator*(const Fraction& other) const {
        Fraction result(numerator * other.numerator, denominator * other.denominator);
        result.simplify();
        return result;
    }

    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0)
            throw std::invalid_argument("Division by zero is not allowed.");

        Fraction result(numerator * other.denominator, denominator * other.numerator);
        result.simplify();
        return result;
    }

    void print() const {
        std::cout << numerator << "/" << denominator << std::endl;
    }
};

int main() {
    Fraction f1(1, 2);
    Fraction f2(3, 4);

    Fraction sum = f1 + f2;
    sum.print();

    Fraction diff = f1 - f2;
    diff.print();

    Fraction prod = f1 * f2;
    prod.print();

    Fraction div = f1 / f2;
    div.print();

    return 0;
}
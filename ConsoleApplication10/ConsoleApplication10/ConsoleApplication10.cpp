#include <iostream>

class Complex {
private:
    double real;
    double imaginary;

public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imaginary(i) {}

    void print() const {
        std::cout << real << " + " << imaginary << "i";
    }

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imaginary + other.imaginary);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imaginary - other.imaginary);
    }

    Complex operator*(const Complex& other) const {
        double newReal = (real * other.real) - (imaginary * other.imaginary);
        double newImaginary = (real * other.imaginary) + (imaginary * other.real);
        return Complex(newReal, newImaginary);
    }

    Complex operator/(const Complex& other) const {
        double denominator = (other.real * other.real) + (other.imaginary * other.imaginary);
        if (denominator == 0) {
            std::cerr << "Ошибка: Деление на ноль." << std::endl;
            return Complex(0, 0);
        }
        double newReal = ((real * other.real) + (imaginary * other.imaginary)) / denominator;
        double newImaginary = ((imaginary * other.real) - (real * other.imaginary)) / denominator;
        return Complex(newReal, newImaginary);
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& complex) {
        os << complex.real << " + " << complex.imaginary << "i";
        return os;
    }
};

int main() {
    Complex a(1.0, 2.0);
    Complex b(2.0, 3.0);

    Complex c = a + b;
    Complex d = a - b;
    Complex e = a * b;
    Complex f = a / b;

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "a + b = " << c << std::endl;
    std::cout << "a - b = " << d << std::endl;
    std::cout << "a * b = " << e << std::endl;
    std::cout << "a / b = " << f << std::endl;

    return 0;
}

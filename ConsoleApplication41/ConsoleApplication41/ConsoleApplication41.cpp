#include <iostream>

class Complex {
private:
    double real;
    double imaginary;

public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imaginary(i) {}

    double getReal() const { return real; }
    double getImaginary() const { return imaginary; }

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imaginary + other.imaginary);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imaginary - other.imaginary);
    }

    Complex operator*(const Complex& other) const {
        double newReal = real * other.real - imaginary * other.imaginary;
        double newImaginary = real * other.imaginary + imaginary * other.real;
        return Complex(newReal, newImaginary);
    }

    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imaginary * other.imaginary;
        if (denominator == 0) {
            std::cerr << "Ошибка: Деление на ноль." << std::endl;
            return Complex(0, 0);
        }
        double newReal = (real * other.real + imaginary * other.imaginary) / denominator;
        double newImaginary = (imaginary * other.real - real * other.imaginary) / denominator;
        return Complex(newReal, newImaginary);
    }

    friend std::ostream& operator<<(std::ostream& out, const Complex& complex) {
        out << complex.real;
        if (complex.imaginary >= 0) {
            out << " + " << complex.imaginary << "i";
        }
        else {
            out << " - " << -complex.imaginary << "i";
        }
        return out;
    }
    Complex operator-() const {
        return Complex(-real, -imaginary);
    }
};

int main() {
    Complex a(1.0, 2.0);
    Complex b(2.0, -1.0);

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;

    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "a - b = " << a - b << std::endl;
    std::cout << "a * b = " << a * b << std::endl;
    std::cout << "a / b = " << a / b << std::endl;

    Complex c(2.5, -3.7);
    std::cout << "c = " << c << std::endl;
    std::cout << "-c = " << -c << std::endl;


    return 0;
}

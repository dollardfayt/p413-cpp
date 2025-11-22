#include <iostream>
#include <vector>
#include <cmath>

class Equation {
public:
    virtual ~Equation() {}

    virtual std::vector<double> solve() = 0;

    void printRoots() {
        std::vector<double> roots = solve();
        if (roots.empty()) {
            std::cout << "Нет действительных корней." << std::endl;
        }
        else {
            std::cout << "Корни уравнения: ";
            for (double root : roots) {
                std::cout << root << " ";
            }
            std::cout << std::endl;
        }
    }
};

class LinearEquation : public Equation {
private:
    double a;
    double b;

public:
    LinearEquation(double a, double b) : a(a), b(b) {}

    std::vector<double> solve() override {
        std::vector<double> roots;
        if (a != 0) {
            roots.push_back(-b / a);
        }
        return roots;
    }
};

class QuadraticEquation : public Equation {
private:
    double a;
    double b;
    double c;

public:
    QuadraticEquation(double a, double b, double c) : a(a), b(b), c(c) {}

    std::vector<double> solve() override {
        std::vector<double> roots;
        double discriminant = b * b - 4 * a * c;

        if (discriminant > 0) {
            roots.push_back((-b + sqrt(discriminant)) / (2 * a));
            roots.push_back((-b - sqrt(discriminant)) / (2 * a));
        }
        else if (discriminant == 0) {
            roots.push_back(-b / (2 * a));
        }
        return roots;
    }
};

int main() 
{
    setlocale(LC_ALL, "Russian");
    Equation* equation1 = new LinearEquation(2, -5);
    equation1->printRoots();

    Equation* equation2 = new QuadraticEquation(1, -3, 2);
    equation2->printRoots();

    Equation* equation3 = new QuadraticEquation(1, 2, 1);
    equation3->printRoots();

    Equation* equation4 = new QuadraticEquation(1, 1, 1);
    equation4->printRoots();

    delete equation1;
    delete equation2;
    delete equation3;
    delete equation4;

    return 0;
}

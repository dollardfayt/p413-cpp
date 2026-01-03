#include <iostream>
#include <string>

class Overcoat {
private:
    std::string type;
    double price;

public:
    Overcoat(const std::string& t = "", double p = 0.0) : type(t), price(p) {}

    bool operator==(const Overcoat& other) const {
        return type == other.type;
    }

    Overcoat& operator=(const Overcoat& other) {
        if (this != &other) {
            type = other.type;
            price = other.price;
        }
        return *this;
    }

    bool operator>(const Overcoat& other) const {
        if (*this == other) {
            return price > other.price;
        }
        return false;
    }

    friend std::ostream& operator<<(std::ostream& os, const Overcoat& coat) {
        os << "Type: " << coat.type << ", Price: " << coat.price;
        return os;
    }
};


class Flat {
private:
    double area;
    double price;

public:
    Flat(double a = 0.0, double p = 0.0) : area(a), price(p) {}

    bool operator==(const Flat& other) const {
        return area == other.area;
    }

    Flat& operator=(const Flat& other) {
        if (this != &other) {
            area = other.area;
            price = other.price;
        }
        return *this;
    }

    bool operator>(const Flat& other) const {
        return price > other.price;
    }

    friend std::ostream& operator<<(std::ostream& os, const Flat& flat) {
        os << "Area: " << flat.area << ", Price: " << flat.price;
        return os;
    }
};


int main() {
    Overcoat coat1("Winter", 200.0);
    Overcoat coat2("Winter", 250.0);
    Overcoat coat3("Summer", 150.0);

    std::cout << "coat1 == coat2: " << (coat1 == coat2) << std::endl;
    std::cout << "coat1 == coat3: " << (coat1 == coat3) << std::endl;
    std::cout << "coat2 > coat1: " << (coat2 > coat1) << std::endl;

    Overcoat coat4 = coat3;
    std::cout << "coat4: " << coat4 << std::endl;


    Flat flat1(50.0, 100000.0);
    Flat flat2(50.0, 120000.0);
    Flat flat3(60.0, 150000.0);

    std::cout << "flat1 == flat2: " << (flat1 == flat2) << std::endl;
    std::cout << "flat1 == flat3: " << (flat1 == flat3) << std::endl;
    std::cout << "flat2 > flat1: " << (flat2 > flat1) << std::endl;

    Flat flat4 = flat3;
    std::cout << "flat4: " << flat4 << std::endl;

    return 0;
}

#include <iostream>
#include <string>

class Overcoat {
private:
    std::string type;
    double price;
    std::string manufacturer;

public:
    Overcoat(const std::string& t = "unknown", double p = 0.0, const std::string& man = "unknown") :
        type(t), price(p), manufacturer(man) {
    }

    std::string getType() const { return type; }
    double getPrice() const { return price; }
    std::string getManufacturer() const { return manufacturer; }

    void setType(const std::string& t) { type = t; }
    void setPrice(double p) { price = p; }
    void setManufacturer(const std::string& man) { manufacturer = man; }

    bool operator==(const Overcoat& other) const {
        return type == other.type;
    }

    Overcoat& operator=(const Overcoat& other) {
        if (this != &other) {
            type = other.type;
            price = other.price;
            manufacturer = other.manufacturer;
        }
        return *this;
    }

    bool operator>(const Overcoat& other) const {
        if (*this == other) {
            return price > other.price;
        }
        else {
            return false;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Overcoat& overcoat) {
        os << "Type: " << overcoat.type << ", Price: " << overcoat.price
            << ", Manufacturer: " << overcoat.manufacturer;
        return os;
    }
};

int main() 
{
    setlocale(LC_ALL, "Russian");
    Overcoat coat1("пальто", 15000.0, "BrandA");
    Overcoat coat2("пальто", 12000.0, "BrandB");
    Overcoat jacket("куртка", 8000.0, "BrandC");

    std::cout << "Coat 1: " << coat1 << std::endl;
    std::cout << "Coat 2: " << coat2 << std::endl;
    std::cout << "Jacket: " << jacket << std::endl;

    if (coat1 == coat2) {
        std::cout << "Coat 1 and Coat 2 are the same type of clothing." << std::endl;
    }
    else {
        std::cout << "Coat 1 and Coat 2 are different types of clothing." << std::endl;
    }

    if (coat1 > coat2) {
        std::cout << "Coat 1 is more expensive than Coat 2." << std::endl;
    }
    else {
        std::cout << "Coat 1 is not more expensive than Coat 2." << std::endl;
    }

    if (coat1 > jacket) {
        std::cout << "Coat 1 is more expensive than Jacket." << std::endl;
    }
    else {
        std::cout << "Coat 1 is not more expensive than Jacket (or they are different types)." << std::endl;
    }

    Overcoat coat3;
    coat3 = coat1;
    std::cout << "Coat 3 (after assignment): " << coat3 << std::endl;

    return 0;
}

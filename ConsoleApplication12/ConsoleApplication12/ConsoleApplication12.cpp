#include <iostream>

class Flat {
private:
    double area;
    double price;
    std::string address;

public:
    Flat(double a = 0.0, double p = 0.0, const std::string& addr = "unknown") :
        area(a), price(p), address(addr) {
    }

    double getArea() const { return area; }
    double getPrice() const { return price; }
    std::string getAddress() const { return address; }

    void setArea(double a) { area = a; }
    void setPrice(double p) { price = p; }
    void setAddress(const std::string& addr) { address = addr; }

    bool operator==(const Flat& other) const {
        return area == other.area;
    }

    Flat& operator=(const Flat& other) {
        if (this != &other) {
            area = other.area;
            price = other.price;
            address = other.address;
        }
        return *this;
    }

    bool operator>(const Flat& other) const {
        return price > other.price;
    }

    friend std::ostream& operator<<(std::ostream& os, const Flat& flat) {
        os << "Area: " << flat.area << ", Price: " << flat.price << ", Address: " << flat.address;
        return os;
    }
};

int main() {
    Flat flat1(50.0, 5000000.0, "ул. Пушкина, 10");
    Flat flat2(50.0, 6000000.0, "ул. Лермонтова, 5");
    Flat flat3(60.0, 7000000.0, "пр. Победы, 20");

    std::cout << "Flat 1: " << flat1 << std::endl;
    std::cout << "Flat 2: " << flat2 << std::endl;
    std::cout << "Flat 3: " << flat3 << std::endl;

    if (flat1 == flat2) {
        std::cout << "Flat 1 and Flat 2 have the same area." << std::endl;
    }
    else {
        std::cout << "Flat 1 and Flat 2 have different areas." << std::endl;
    }

    if (flat1 > flat2) {
        std::cout << "Flat 1 is more expensive than Flat 2." << std::endl;
    }
    else {
        std::cout << "Flat 1 is not more expensive than Flat 2." << std::endl;
    }

    Flat flat4;
    flat4 = flat3;
    std::cout << "Flat 4 (after assignment): " << flat4 << std::endl;

    return 0;
}

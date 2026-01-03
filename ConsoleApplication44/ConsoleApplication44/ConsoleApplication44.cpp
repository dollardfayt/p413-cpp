#include <iostream>

class Flat {
private:
    double area;
    double price;

public:
    Flat(double area, double price) : area(area), price(price) {}

    double getArea() const { return area; }
    double getPrice() const { return price; }

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
};

int main() 
{
    setlocale(LC_ALL, "Russian");
    Flat flat1(50.0, 100000.0);
    Flat flat2(50.0, 120000.0);
    Flat flat3(60.0, 150000.0);

    if (flat1 == flat2) {
        std::cout << "flat1 и flat2 имеют одинаковую площадь." << std::endl;
    }
    else {
        std::cout << "flat1 и flat2 имеют разную площадь." << std::endl;
    }

    if (flat2 > flat1) {
        std::cout << "flat2 дороже, чем flat1." << std::endl;
    }
    else {
        std::cout << "flat2 не дороже, чем flat1." << std::endl;
    }

    Flat flat4(40.0, 80000.0);
    flat4 = flat1;

    std::cout << "Площадь flat4 после присваивания: " << flat4.getArea() << std::endl;
    std::cout << "Цена flat4 после присваивания: " << flat4.getPrice() << std::endl;

    return 0;
}

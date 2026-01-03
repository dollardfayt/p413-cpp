#include <iostream>
#include <string>

class Overcoat {
private:
    std::string type;
    double price;

public:
    Overcoat(std::string type, double price) : type(type), price(price) {}

    std::string getType() const { return type; }
    double getPrice() const { return price; }

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
        if (type == other.type) {
            return price > other.price;
        }
        return false;
    }
};

int main() 
{
    setlocale(LC_ALL, "Russian");
    Overcoat coat1("Пальто", 150.0);
    Overcoat coat2("Пальто", 200.0);
    Overcoat jacket("Куртка", 100.0);

    if (coat1 == coat2) {
        std::cout << "coat1 и coat2 имеют одинаковый тип." << std::endl;
    }
    else {
        std::cout << "coat1 и coat2 имеют разный тип." << std::endl;
    }

    if (coat1 == jacket) {
        std::cout << "coat1 и jacket имеют одинаковый тип." << std::endl;
    }
    else {
        std::cout << "coat1 и jacket имеют разный тип." << std::endl;
    }

    if (coat2 > coat1) {
        std::cout << "coat2 дороже, чем coat1 (одинаковый тип)." << std::endl;
    }
    else {
        std::cout << "coat2 не дороже, чем coat1 (или типы разные)." << std::endl;
    }

    if (jacket > coat1) {
        std::cout << "jacket дороже, чем coat1 (одинаковый тип)." << std::endl;
    }
    else {
        std::cout << "jacket не дороже, чем coat1 (или типы разные)." << std::endl;
    }
    Overcoat coat3("Плащ", 120.0);
    coat3 = coat1;
    std::cout << "Тип coat3 после присваивания: " << coat3.getType() << std::endl;
    std::cout << "Цена coat3 после присваивания: " << coat3.getPrice() << std::endl;

    return 0;
}

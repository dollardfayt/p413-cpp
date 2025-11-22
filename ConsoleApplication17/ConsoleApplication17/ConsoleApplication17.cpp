#include <iostream>
#include <string>
#include <vector>

class Human {
private:
    std::string fullName;
    int age;

public:
    Human() : age(0) {}
    Human(const std::string& name, int a) : fullName(name), age(a) {}
    Human(const Human& other) : fullName(other.fullName), age(other.age) {}
    Human& operator=(const Human& other) {
        if (this != &other) {
            fullName = other.fullName;
            age = other.age;
        }
        return *this;
    }
    ~Human() {}
    const std::string& getFullName() const { return fullName; }
    int getAge() const { return age; }
    void setFullName(const std::string& name) { fullName = name; }
    void setAge(int a) { age = a; }
    void print() const {
        std::cout << "ФИО: " << fullName << ", Возраст: " << age << std::endl;
    }
};

class Apartment {
private:
    std::vector<Human> residents;
    int maxResidents;
    int apartmentNumber;

public:
    Apartment(int apartmentNumber) : maxResidents(0), apartmentNumber(apartmentNumber) {}
    Apartment(int max, int apartmentNumber) : maxResidents(max), apartmentNumber(apartmentNumber) {
        residents.reserve(maxResidents);
    }
    Apartment(const Apartment& other) : residents(other.residents), maxResidents(other.maxResidents), apartmentNumber(other.apartmentNumber) {}
    Apartment& operator=(const Apartment& other) {
        if (this != &other) {
            residents = other.residents;
            maxResidents = other.maxResidents;
            apartmentNumber = other.apartmentNumber;
        }
        return *this;
    }
    ~Apartment() {}
    bool addResident(const Human& human) {
        if (residents.size() < maxResidents) {
            residents.push_back(human);
            return true;
        }
        else {
            std::cout << "Квартира полна!" << std::endl;
            return false;
        }
    }
    void removeResident(int index) {
        if (index >= 0 && index < residents.size()) {
            residents.erase(residents.begin() + index);
        }
        else {
            std::cout << "Неверный индекс!" << std::endl;
        }
    }
    void printApartment() const {
        std::cout << "Квартира №" << apartmentNumber << ", Жителей: " << residents.size() << " (макс. " << maxResidents << ")" << std::endl;
        for (const auto& resident : residents) {
            std::cout << "  - ";
            resident.print();
        }
    }
};

class House {
private:
    std::vector<Apartment> apartments;
    int maxApartments;

public:
    House(int max) : maxApartments(max) {
        apartments.reserve(maxApartments);
        for (int i = 0; i < maxApartments; i++) {
            apartments.emplace_back(i + 1);
        }
    }
    House(const House& other) : apartments(other.apartments), maxApartments(other.maxApartments) {}
    House& operator=(const House& other) {
        if (this != &other) {
            apartments = other.apartments;
            maxApartments = other.maxApartments;
        }
        return *this;
    }
    ~House() {}
    Apartment& getApartment(int apartmentNumber) {
        return apartments[apartmentNumber - 1];
    }

    void printHouse() const {
        std::cout << "Дом, Квартир: " << apartments.size() << " (макс. " << maxApartments << ")" << std::endl;
        for (const auto& apartment : apartments) {
            apartment.printApartment();
        }
    }
};

int main() 
{
    setlocale(LC_ALL, "Russian");
    House house(5);

    Human human1("Иванов Иван Иванович", 30);
    Human human2("Петров Петр Петрович", 25);
    house.getApartment(1).addResident(human1);
    house.getApartment(1).addResident(human2);

    Human human3("Сидоров Сидор Сидорович", 40);
    house.getApartment(2).addResident(human3);

    house.printHouse();
    house.getApartment(1).removeResident(0);
    house.getApartment(1).printApartment();

    return 0;
}

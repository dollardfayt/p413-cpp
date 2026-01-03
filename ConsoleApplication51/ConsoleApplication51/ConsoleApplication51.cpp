#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <stdexcept>

using namespace std;

class Person {
private:
    char* fullName;
    int age;
    double salary;

public:
    Person() : age(0), salary(0.0) {
        fullName = new char[1];
        fullName[0] = '\0';
        cout << "Person: Конструктор по умолчанию" << endl;
    }

    Person(const char* name, int personAge, double personSalary)
        : age(personAge), salary(personSalary) {
        if (name) {
            fullName = new char[strlen(name) + 1];
            strcpy(fullName, name);
        }
        else {
            fullName = new char[1];
            fullName[0] = '\0';
        }
        cout << "Person: Конструктор с параметрами (" << name << ")" << endl;
    }

    Person(const Person& other) : age(other.age), salary(other.salary) {
        if (other.fullName) {
            fullName = new char[strlen(other.fullName) + 1];
            strcpy(fullName, other.fullName);
        }
        else {
            fullName = new char[1];
            fullName[0] = '\0';
        }
        cout << "Person: Конструктор копирования" << endl;
    }

    Person& operator=(const Person& other) {
        if (this != &other) {
            delete[] fullName;

            age = other.age;
            salary = other.salary;

            if (other.fullName) {
                fullName = new char[strlen(other.fullName) + 1];
                strcpy(fullName, other.fullName);
            }
            else {
                fullName = new char[1];
                fullName[0] = '\0';
            }
        }
        cout << "Person: Оператор присваивания" << endl;
        return *this;
    }

    ~Person() {
        delete[] fullName;
        cout << "Person: Деструктор" << endl;
    }

    const char* getFullName() const { return fullName; }
    int getAge() const { return age; }
    double getSalary() const { return salary; }

    void setFullName(const char* name) {
        delete[] fullName;
        if (name) {
            fullName = new char[strlen(name) + 1];
            strcpy(fullName, name);
        }
        else {
            fullName = new char[1];
            fullName[0] = '\0';
        }
    }

    void setAge(int personAge) { age = personAge; }
    void setSalary(double personSalary) { salary = personSalary; }

    void printInfo() const {
        cout << "ФИО: " << (fullName ? fullName : "Не указано")
            << ", Возраст: " << age
            << ", Зарплата: " << salary << endl;
    }
};

class Apartment {
private:
    int apartmentNumber;
    double area;
    Person* residents;
    int residentCount;
    int maxResidents;

public:
    Apartment() : apartmentNumber(0), area(0.0), residentCount(0), maxResidents(10) {
        residents = new Person[maxResidents];
        cout << "Apartment: Конструктор по умолчанию" << endl;
    }

    Apartment(int number, double apartmentArea, int maxCapacity = 10)
        : apartmentNumber(number), area(apartmentArea),
        residentCount(0), maxResidents(maxCapacity) {
        if (maxResidents <= 0) {
            throw invalid_argument("Максимальное количество жильцов должно быть больше 0");
        }
        residents = new Person[maxResidents];
        cout << "Apartment: Конструктор с параметрами (№" << number << ")" << endl;
    }

    Apartment(const Apartment& other)
        : apartmentNumber(other.apartmentNumber),
        area(other.area),
        residentCount(other.residentCount),
        maxResidents(other.maxResidents) {

        residents = new Person[maxResidents];
        for (int i = 0; i < residentCount; ++i) {
            residents[i] = other.residents[i];
        }
        cout << "Apartment: Конструктор копирования (№" << apartmentNumber << ")" << endl;
    }

    Apartment& operator=(const Apartment& other) {
        if (this != &other) {
            apartmentNumber = other.apartmentNumber;
            area = other.area;
            residentCount = other.residentCount;
            maxResidents = other.maxResidents;

            delete[] residents;

            residents = new Person[maxResidents];
            for (int i = 0; i < residentCount; ++i) {
                residents[i] = other.residents[i];
            }
        }
        cout << "Apartment: Оператор присваивания (№" << apartmentNumber << ")" << endl;
        return *this;
    }

    ~Apartment() {
        delete[] residents;
        cout << "Apartment: Деструктор (№" << apartmentNumber << ")" << endl;
    }

    bool addResident(const Person& person) {
        if (residentCount < maxResidents) {
            residents[residentCount++] = person;
            return true;
        }
        cout << "Ошибка: Квартира переполнена!" << endl;
        return false;
    }

    bool removeResident(int index) {
        if (index < 0 || index >= residentCount) {
            cout << "Ошибка: Неверный индекс жильца!" << endl;
            return false;
        }

        for (int i = index; i < residentCount - 1; ++i) {
            residents[i] = residents[i + 1];
        }
        residentCount--;
        return true;
    }

    int getApartmentNumber() const { return apartmentNumber; }
    double getArea() const { return area; }
    int getResidentCount() const { return residentCount; }

    void printInfo() const {
        cout << "\n=== Квартира №" << apartmentNumber
            << " (площадь: " << area << " кв.м) ===" << endl;
        cout << "Количество жильцов: " << residentCount << "/" << maxResidents << endl;
        for (int i = 0; i < residentCount; ++i) {
            cout << "Жилец " << (i + 1) << ": ";
            residents[i].printInfo();
        }
        if (residentCount == 0) {
            cout << "Квартира пустует" << endl;
        }
    }
};

class House {
private:
    string address;
    Apartment* apartments;
    int apartmentCount;
    int maxApartments;

public:
    House() : apartmentCount(0), maxApartments(20) {
        apartments = new Apartment[maxApartments];
        cout << "House: Конструктор по умолчанию" << endl;
    }

    House(const string& houseAddress, int maxCapacity = 20)
        : address(houseAddress), apartmentCount(0), maxApartments(maxCapacity) {
        if (maxApartments <= 0) {
            throw invalid_argument("Максимальное количество квартир должно быть больше 0");
        }
        apartments = new Apartment[maxApartments];
        cout << "House: Конструктор с параметрами (" << address << ")" << endl;
    }

    House(const House& other)
        : address(other.address),
        apartmentCount(other.apartmentCount),
        maxApartments(other.maxApartments) {

        apartments = new Apartment[maxApartments];
        for (int i = 0; i < apartmentCount; ++i) {
            apartments[i] = other.apartments[i];
        }
        cout << "House: Конструктор копирования (" << address << ")" << endl;
    }

    House& operator=(const House& other) {
        if (this != &other) {
            address = other.address;
            apartmentCount = other.apartmentCount;
            maxApartments = other.maxApartments;

            delete[] apartments;

            apartments = new Apartment[maxApartments];
            for (int i = 0; i < apartmentCount; ++i) {
                apartments[i] = other.apartments[i];
            }
        }
        cout << "House: Оператор присваивания (" << address << ")" << endl;
        return *this;
    }

    ~House() {
        delete[] apartments;
        cout << "House: Деструктор (" << address << ")" << endl;
    }

    bool addApartment(const Apartment& apartment) {
        if (apartmentCount < maxApartments) {
            apartments[apartmentCount++] = apartment;
            return true;
        }
        cout << "Ошибка: Дом переполнен!" << endl;
        return false;
    }

    bool removeApartment(int apartmentNumber) {
        int index = -1;
        for (int i = 0; i < apartmentCount; ++i) {
            if (apartments[i].getApartmentNumber() == apartmentNumber) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Ошибка: Квартира с номером " << apartmentNumber << " не найдена!" << endl;
            return false;
        }

        for (int i = index; i < apartmentCount - 1; ++i) {
            apartments[i] = apartments[i + 1];
        }
        apartmentCount--;
        return true;
    }

    Apartment* findApartment(int apartmentNumber) {
        for (int i = 0; i < apartmentCount; ++i) {
            if (apartments[i].getApartmentNumber() == apartmentNumber) {
                return &apartments[i];
            }
        }
        return nullptr;
    }

    const string& getAddress() const { return address; }
    int getApartmentCount() const { return apartmentCount; }

    void printInfo() const {
        cout << "\n" << string(60, '=') << endl;
        cout << "ДОМ ПО АДРЕСУ: " << address << endl;
        cout << "Общее количество квартир: " << apartmentCount << "/" << maxApartments << endl;
        cout << string(60, '=') << endl;

        if (apartmentCount == 0) {
            cout << "Дом пустует" << endl;
        }
        else {
            for (int i = 0; i < apartmentCount; ++i) {
                apartments[i].printInfo();
            }
        }
        cout << string(60, '=') << endl;
    }

    void printStatistics() const {
        int totalResidents = 0;
        double totalArea = 0.0;
        double totalSalary = 0.0;

        for (int i = 0; i < apartmentCount; ++i) {
            totalArea += apartments[i].getArea();
            for (int j = 0; j < apartments[i].getResidentCount(); ++j) {
                totalResidents++;
                totalSalary += apartments[i].getResidentCount() > j ?
                    0 : 0;
            }
        }

        cout << "\nСТАТИСТИКА ДОМА \"" << address << "\":" << endl;
        cout << "Всего квартир: " << apartmentCount << endl;
        cout << "Общая площадь: " << totalArea << " кв.м" << endl;
        cout << "Общее количество жильцов: " << totalResidents << endl;
    }
};

int main() 
{
    setlocale(LC_ALL, "Russian");
    try {
        cout << "=== ТЕСТИРОВАНИЕ СИСТЕМЫ МНОГОКВАРТИРНОГО ДОМА ===" << endl;
        cout << string(60, '-') << endl;

        cout << "\n1. СОЗДАНИЕ ЖИЛЬЦОВ:" << endl;
        Person ivanov("Иванов Иван Иванович", 35, 80000.0);
        Person petrova("Петрова Мария Сергеевна", 28, 65000.0);
        Person sidorov("Сидоров Петр Петрович", 42, 95000.0);
        Person smirnova("Смирнова Анна Владимировна", 31, 72000.0);

        cout << "\n2. ТЕСТИРОВАНИЕ КОНСТРУКТОРА КОПИРОВАНИЯ (Person):" << endl;
        Person ivanov_copy(ivanov);
        cout << "Оригинал: "; ivanov.printInfo();
        cout << "Копия: "; ivanov_copy.printInfo();

        cout << "\n3. СОЗДАНИЕ ДОМА:" << endl;
        House residentialComplex("ул. Ленина, д. 25");

        cout << "\n4. СОЗДАНИЕ И ДОБАВЛЕНИЕ КВАРТИР:" << endl;
        Apartment apt1(101, 65.5);
        apt1.addResident(ivanov);
        apt1.addResident(petrova);
        residentialComplex.addApartment(apt1);

        Apartment apt2(102, 72.0);
        apt2.addResident(sidorov);
        residentialComplex.addApartment(apt2);

        Apartment apt3(103, 58.3);
        apt3.addResident(smirnova);
        residentialComplex.addApartment(apt3);

        cout << "\n5. ИНФОРМАЦИЯ О ДОМЕ:" << endl;
        residentialComplex.printInfo();

        cout << "\n6. ТЕСТИРОВАНИЕ КОНСТРУКТОРА КОПИРОВАНИЯ (Apartment):" << endl;
        Apartment apt1_copy(apt1);
        cout << "Копия квартиры 101:" << endl;
        apt1_copy.printInfo();

        cout << "\n7. ТЕСТИРОВАНИЕ КОНСТРУКТОРА КОПИРОВАНИЯ (House):" << endl;
        House house_copy(residentialComplex);
        cout << "Информация о скопированном доме:" << endl;
        house_copy.printInfo();

        cout << "\n8. ТЕСТИРОВАНИЕ ОПЕРАТОРА ПРИСВАИВАНИЯ:" << endl;
        House anotherHouse("ул. Мира, д. 15");
        anotherHouse = residentialComplex;
        cout << "Информация о доме после присваивания:" << endl;
        anotherHouse.printInfo();

        cout << "\n9. ОПЕРАЦИИ С КВАРТИРАМИ И ЖИЛЬЦАМИ:" << endl;
        cout << "Удаление жильца из квартиры 101:" << endl;
        apt1.removeResident(0);
        apt1.printInfo();

        cout << "Добавление нового жильца в квартиру 102:" << endl;
        Person newResident("Козлов Дмитрий Александрович", 29, 68000.0);
        apt2.addResident(newResident);
        apt2.printInfo();

        cout << "\n10. ПОИСК КВАРТИРЫ:" << endl;
        Apartment* foundApt = residentialComplex.findApartment(102);
        if (foundApt) {
            cout << "Найдена квартира 102:" << endl;
            foundApt->printInfo();
        }

        cout << "\n11. СТАТИСТИКА ДОМА:" << endl;
        residentialComplex.printStatistics();

        cout << "\n12. УДАЛЕНИЕ КВАРТИРЫ:" << endl;
        residentialComplex.removeApartment(103);
        cout << "Информация о доме после удаления квартиры 103:" << endl;
        residentialComplex.printInfo();

        cout << "\n" << string(60, '=') << endl;
        cout << "ТЕСТИРОВАНИЕ ЗАВЕРШЕНО УСПЕШНО!" << endl;
        cout << string(60, '=') << endl;

    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}

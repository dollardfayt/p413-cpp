#include <iostream>
#include <string>

class Animal {
protected:
    std::string name;
    std::string breed;
    int age;

public:
    Animal(std::string name, std::string breed, int age) : name(name), breed(breed), age(age) {}

    virtual void makeSound() {
        std::cout << "Животное издает звук." << std::endl;
    }

    void displayInfo() {
        std::cout << "Имя: " << name << std::endl;
        std::cout << "Порода: " << breed << std::endl;
        std::cout << "Возраст: " << age << " лет" << std::endl;
    }

    std::string getName() const { return name; }
    std::string getBreed() const { return breed; }
    int getAge() const { return age; }
};

class Dog : public Animal {
private:
    std::string favoriteToy;

public:
    Dog(std::string name, std::string breed, int age, std::string favoriteToy) : Animal(name, breed, age), favoriteToy(favoriteToy) {}

    void makeSound() override {
        std::cout << "Гав!" << std::endl;
    }

    void displayInfo() {
        Animal::displayInfo();
        std::cout << "Любимая игрушка: " << favoriteToy << std::endl;
    }
    std::string getFavoriteToy() const { return favoriteToy; }
};

class Cat : public Animal {
private:
    std::string color;

public:
    Cat(std::string name, std::string breed, int age, std::string color) : Animal(name, breed, age), color(color) {}

    void makeSound() override {
        std::cout << "Мяу!" << std::endl;
    }

    void displayInfo() {
        Animal::displayInfo();
        std::cout << "Цвет: " << color << std::endl;
    }
    std::string getColor() const { return color; }
};

class Parrot : public Animal {
private:
    bool canTalk;

public:
    Parrot(std::string name, std::string breed, int age, bool canTalk) : Animal(name, breed, age), canTalk(canTalk) {}

    void makeSound() override {
        std::cout << "Чирик!" << std::endl;
    }

    void displayInfo() {
        Animal::displayInfo();
        std::cout << "Умеет говорить: " << (canTalk ? "Да" : "Нет") << std::endl;
    }
    bool getCanTalk() const { return canTalk; }
};

int main() 
{
    setlocale(LC_ALL, "Russian");
    Dog dog("Рекс", "Немецкая овчарка", 3, "Мячик");
    Cat cat("Муся", "Сиамская", 5, "Белый");
    Parrot parrot("Кеша", "Волнистый", 1, true);

    std::cout << "Собака:" << std::endl;
    dog.displayInfo();
    dog.makeSound();
    std::cout << std::endl;

    std::cout << "Кошка:" << std::endl;
    cat.displayInfo();
    cat.makeSound();
    std::cout << std::endl;

    std::cout << "Попугай:" << std::endl;
    parrot.displayInfo();
    parrot.makeSound();
    std::cout << std::endl;

    return 0;
}

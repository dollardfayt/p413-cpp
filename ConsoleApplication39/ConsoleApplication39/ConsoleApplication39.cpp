#include <iostream>
#include <cstring>

class String {
private:
    char* str;
    int length;
    static int objectCount;

public:
    String() : String(80) {}

    String(int size) : str(new char[size + 1]), length(size) {
        str[0] = '\0';
        objectCount++;
    }

    String(const char* s) : str(nullptr), length(0) {
        length = strlen(s);
        str = new char[length + 1];
        strcpy(str, s);
        objectCount++;
    }

    ~String() {
        delete[] str;
        objectCount--;
    }

    void input() {
        std::cin.getline(str, length + 1);
    }

    void print() const {
        std::cout << str << std::endl;
    }

    static int getObjectCount() {
        return objectCount;
    }
};

int String::objectCount = 0;

int main() 
{
    setlocale(LC_ALL, "Russian");
    String myStr("Привет мир!");
    myStr.print();

    std::cout << "Количество созданных объектов: " << String::getObjectCount() << std::endl;

    return 0;
}
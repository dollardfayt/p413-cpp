#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <utility>

class String {
private:
    char* data;
    size_t length;

public:
    String() : data(nullptr), length(0) {
        std::cout << "String() constructor" << std::endl;
    }

    String(const char* str) : length(std::strlen(str)) {
        std::cout << "String(const char*) constructor" << std::endl;
        data = new char[length + 1];
        std::strcpy(data, str);
    }

    String(const String& other) : length(other.length) {
        std::cout << "String(const String&) copy constructor" << std::endl;
        data = new char[length + 1];
        std::strcpy(data, other.data);
    }

    String(String&& other) : data(other.data), length(other.length) {
        std::cout << "String(String&&) move constructor" << std::endl;
        other.data = nullptr;
        other.length = 0;
    }

    String& operator=(const String& other) {
        std::cout << "operator=(const String&) copy assignment" << std::endl;
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            std::strcpy(data, other.data);
        }
        return *this;
    }

    String& operator=(String&& other) {
        std::cout << "operator=(String&&) move assignment" << std::endl;
        if (this != &other) {
            delete[] data;
            data = other.data;
            length = other.length;
            other.data = nullptr;
            other.length = 0;
        }
        return *this;
    }

    ~String() {
        std::cout << "~String() destructor" << std::endl;
        delete[] data;
    }

    char* get_data() const {
        return data;
    }

    size_t get_length() const {
        return length;
    }

    void print() const {
        if (data) {
            std::cout << "String: " << data << std::endl;
        }
        else {
            std::cout << "String: (empty)" << std::endl;
        }
    }
};

int main() {
    String str1 = "Hello";
    String str2 = std::move(str1);

    str1.print();
    str2.print();

    String str3;
    str3 = std::move(str2);
    str3.print();
    str2.print();

    return 0;
}

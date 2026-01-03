#include <iostream>
#include <cstring>

class String {
private:
    char* str;
    size_t len;

public:
    String() : str(nullptr), len(0) {}

    String(const char* s) : len(strlen(s)) {
        str = new char[len + 1];
        strcpy(str, s);
    }

    String(const String& other) : len(other.len) {
        str = new char[len + 1];
        strcpy(str, other.str);
    }

    String(String&& other) noexcept : str(other.str), len(other.len) {
        other.str = nullptr;
        other.len = 0;
    }

    String& operator=(const String& other) {
        if (this != &other) {
            delete[] str;
            len = other.len;
            str = new char[len + 1];
            strcpy(str, other.str);
        }
        return *this;
    }

    String& operator=(String&& other) noexcept {
        if (this != &other) {
            delete[] str;
            str = other.str;
            len = other.len;
            other.str = nullptr;
            other.len = 0;
        }
        return *this;
    }

    ~String() {
        delete[] str;
    }

    const char* c_str() const {
        return str;
    }

    size_t length() const {
        return len;
    }
};

int main() {
    String str1 = "Hello";
    String str2 = std::move(str1);

    std::cout << "str2: " << str2.c_str() << std::endl;

    return 0;
}

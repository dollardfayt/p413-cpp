#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

class String {
protected:
    char* str;
    size_t len;

public:
    String() : str(nullptr), len(0) {}

    String(const char* cstr) : len(std::strlen(cstr)) {
        str = new char[len + 1];
        std::strcpy(str, cstr);
    }

    String(const String& other) : len(other.len) {
        str = new char[len + 1];
        std::strcpy(str, other.str);
    }

    String& operator=(const String& other) {
        if (this != &other) {
            delete[] str;
            len = other.len;
            str = new char[len + 1];
            std::strcpy(str, other.str);
        }
        return *this;
    }

    size_t length() const { return len; }

    void clear() {
        delete[] str;
        str = nullptr;
        len = 0;
    }

    ~String() { delete[] str; }

    String operator+(const String& other) const {
        String result;
        result.len = len + other.len;
        result.str = new char[result.len + 1];
        std::strcpy(result.str, str);
        std::strcat(result.str, other.str);
        return result;
    }

    String& operator+=(const String& other) {
        *this = *this + other;
        return *this;
    }

    bool operator==(const String& other) const {
        return (len == other.len) && (std::strcmp(str, other.str) == 0);
    }

    bool operator!=(const String& other) const {
        return !(*this == other);
    }

    const char* c_str() const {
        return str;
    }
};

class BitString : public String {
public:
    BitString() : String() {}

    BitString(const char* cstr) : String() {
        bool valid = true;
        for (size_t i = 0; cstr[i] != '\0'; ++i) {
            if (cstr[i] != '0' && cstr[i] != '1') {
                valid = false;
                break;
            }
        }
        if (valid) {
            String::str = new char[std::strlen(cstr) + 1];
            std::strcpy(String::str, cstr);
            String::len = std::strlen(cstr);
        }
    }

    BitString(const BitString& other) : String(other) {}

    BitString& operator=(const BitString& other) {
        String::operator=(other);
        return *this;
    }

    long toInt() const {
        if (str == nullptr) return 0;

        long result = 0;
        long sign = 1;
        size_t num_bits = len;

        if (len > 0 && str[0] == '1') {
            sign = -1;
        }


        for (size_t i = 0; i < len; ++i) {
            result = (result << 1) | (str[i] - '0');
        }


        if (sign == -1) {
            result = -((~result & ((1LL << len) - 1)) + 1);

        }

        return result;
    }
};

int main() {
    String str1("Hello");
    String str2 = str1;
    String str3("World");

    std::cout << "str1: " << str1.c_str() << std::endl;
    std::cout << "str2: " << str2.c_str() << std::endl;
    std::cout << "Length of str1: " << str1.length() << std::endl;

    String str4 = str1 + " " + str3;
    std::cout << "str4: " << str4.c_str() << std::endl;

    str1 += "!";
    std::cout << "str1: " << str1.c_str() << std::endl;

    if (str1 == str2) {
        std::cout << "str1 and str2 are equal" << std::endl;
    }
    else {
        std::cout << "str1 and str2 are not equal" << std::endl;
    }

    BitString bitStr1("101010");
    BitString bitStr2("1111111111111111111111111111111");
    BitString bitStr3("1000000000000000000000000000000");

    std::cout << "bitStr1: " << bitStr1.c_str() << ", toInt: " << bitStr1.toInt() << std::endl;
    std::cout << "bitStr2: " << bitStr2.c_str() << ", toInt: " << bitStr2.toInt() << std::endl;
    std::cout << "bitStr3: " << bitStr3.c_str() << ", toInt: " << bitStr3.toInt() << std::endl;


    return 0;
}
#include <iostream>
#include <string>

class String {
private:
    std::string data;

public:
    String() = default;
    String(const std::string& str) : data(str) {}
    String(const char* str) : data(str) {}

    char& operator[](size_t index) {
        return data[index];
    }

    int operator()(char c) {
        size_t pos = data.find(c);
        if (pos != std::string::npos) {
            return static_cast<int>(pos);
        }
        else {
            return -1;
        }
    }

    explicit operator int() const {
        return static_cast<int>(data.length());
    }
};

int main() {
    String str("Hello");
    std::cout << str[0] << std::endl;
    std::cout << str('l') << std::endl;
    std::cout << static_cast<int>(str) << std::endl;
    return 0;
}
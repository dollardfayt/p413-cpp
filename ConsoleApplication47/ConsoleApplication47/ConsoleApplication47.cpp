#include <iostream>
#include <cstring>

class String {
private:
    char* data;
    size_t length;
    size_t capacity;

public:
    String() : data(nullptr), length(0), capacity(0) {}
    String(const char* str);
    String(const String& other);
    String(String&& other) noexcept;

    ~String();

    String& operator=(const String& other);
    String& operator=(String&& other) noexcept;

    size_t getLength() const { return length; }
    size_t getCapacity() const { return capacity; }

    char& operator[](size_t index);
    const char& operator[](size_t index) const;
    int operator()(char c) const;
    explicit operator int() const;

    void print() const;

private:
    void allocate(size_t newCapacity);
};


String::String(const char* str) {
    if (str == nullptr) {
        data = nullptr;
        length = 0;
        capacity = 0;
        return;
    }

    length = std::strlen(str);
    capacity = length + 1;
    data = new char[capacity];
    std::strcpy(data, str);
}

String::String(const String& other) : length(other.length), capacity(other.capacity) {
    data = new char[capacity];
    std::strcpy(data, other.data);
}

String::String(String&& other) noexcept : data(other.data), length(other.length), capacity(other.capacity) {
    other.data = nullptr;
    other.length = 0;
    other.capacity = 0;
}

String::~String() {
    delete[] data;
}

String& String::operator=(const String& other) {
    if (this == &other) {
        return *this;
    }

    if (capacity < other.length + 1) {
        delete[] data;
        capacity = other.length + 1;
        data = new char[capacity];
    }

    length = other.length;
    std::strcpy(data, other.data);

    return *this;
}

String& String::operator=(String&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    delete[] data;

    data = other.data;
    length = other.length;
    capacity = other.capacity;

    other.data = nullptr;
    other.length = 0;
    other.capacity = 0;

    return *this;
}

char& String::operator[](size_t index) {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

const char& String::operator[](size_t index) const {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

int String::operator()(char c) const {
    for (size_t i = 0; i < length; ++i) {
        if (data[i] == c) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

String::operator int() const {
    return static_cast<int>(length);
}

void String::allocate(size_t newCapacity) {
    if (newCapacity == capacity) return;

    char* newData = new char[newCapacity];
    if (data) {
        std::strncpy(newData, data, std::min(newCapacity, capacity));
        delete[] data;
    }
    data = newData;
    capacity = newCapacity;
}

void String::print() const {
    if (data) {
        std::cout << data << std::endl;
    }
    else {
        std::cout << "(empty string)" << std::endl;
    }
}

int main() {
    String str1 = "Hello";
    String str2 = str1;

    std::cout << "str1: ";
    str1.print();
    std::cout << "str2: ";
    str2.print();

    std::cout << "str1[0]: " << str1[0] << std::endl;

    str1[0] = 'J';
    std::cout << "str1 after modification: ";
    str1.print();

    int index = str1('l');
    std::cout << "Index of 'l' in str1: " << index << std::endl;

    int len = static_cast<int>(str1);
    std::cout << "Length of str1: " << len << std::endl;

    String str3 = "World";
    str3 = std::move(str1);

    std::cout << "str3 after move: ";
    str3.print();

    std::cout << "str1 after move (should be empty): ";
    str1.print();

    return 0;
}

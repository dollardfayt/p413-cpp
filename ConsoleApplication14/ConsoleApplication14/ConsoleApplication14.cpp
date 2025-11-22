#include <iostream>
#include <algorithm>

class Array {
private:
    int* data;
    size_t size;

public:
    Array() : data(nullptr), size(0) {}

    Array(size_t size) : size(size) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = 0;
        }
    }

    Array(const Array& other) : size(other.size) {
        data = new int[size];
        std::copy(other.data, other.data + size, data);
    }

    Array(Array&& other) : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            std::copy(other.data, other.data + size, data);
        }
        return *this;
    }

    Array& operator=(Array&& other) {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }

    ~Array() {
        delete[] data;
    }

    size_t getSize() const {
        return size;
    }

    int getElement(size_t index) const {
        if (index < size) {
            return data[index];
        }
        return -1;
    }
};

int main() {
    Array arr1(10);
    Array arr2 = std::move(arr1);

    std::cout << "Size of arr1: " << arr1.getSize() << std::endl;
    std::cout << "Size of arr2: " << arr2.getSize() << std::endl;

    return 0;
}

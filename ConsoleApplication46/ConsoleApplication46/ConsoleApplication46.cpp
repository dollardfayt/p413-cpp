#include <iostream>
#include <algorithm>

class Array {
private:
    int* data;
    size_t size;
    size_t capacity;

public:
    Array() : data(nullptr), size(0), capacity(0) {}

    Array(size_t capacity) : data(new int[capacity]), size(0), capacity(capacity) {}

    Array(const Array& other) : size(other.size), capacity(other.capacity) {
        data = new int[capacity];
        std::copy(other.data, other.data + size, data);
    }

    Array(Array&& other) noexcept : data(other.data), size(other.size), capacity(other.capacity) {
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            int* newData = new int[other.capacity];
            std::copy(other.data, other.data + other.size, newData);
            delete[] data;
            data = newData;
            size = other.size;
            capacity = other.capacity;
        }
        return *this;
    }

    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            capacity = other.capacity;

            other.data = nullptr;
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }


    ~Array() {
        delete[] data;
    }

    void push_back(int value) {
        if (size == capacity) {
            return;
        }
        data[size++] = value;
    }

    int get(size_t index) const {
        return data[index];
    }

    size_t getSize() const {
        return size;
    }
};

int main() {
    Array arr1(5);
    arr1.push_back(1);
    arr1.push_back(2);
    arr1.push_back(3);

    Array arr2 = std::move(arr1);

    std::cout << "arr2 size: " << arr2.getSize() << std::endl;


    return 0;
}

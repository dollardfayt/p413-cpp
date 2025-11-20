#include <iostream>
#include <string>

template <typename T1, typename T2>
class Base {
public:
    Base(T1 v1, T2 v2) : value1(v1), value2(v2) {
        std::cout << "Base constructor" << std::endl;
    }
    ~Base() {
        std::cout << "Base destructor" << std::endl;
    }

    void printBase() const {
        std::cout << "Value1: " << value1 << std::endl;
        std::cout << "Value2: " << value2 << std::endl;
    }

protected:
    T1 value1;
    T2 value2;
};

template <typename T1, typename T2, typename T3, typename T4>
class Child : public Base<T1, T2> {
public:
    Child(T1 v1, T2 v2, T3 v3, T4 v4) : Base<T1, T2>(v1, v2), value3(v3), value4(v4) {
        std::cout << "Child constructor" << std::endl;
    }
    ~Child() {
        std::cout << "Child destructor" << std::endl;
    }

    void printChild() const {
        Base<T1, T2>::printBase();
        std::cout << "Value3: " << value3 << std::endl;
        std::cout << "Value4: " << value4 << std::endl;
    }

private:
    T3 value3;
    T4 value4;
};

template <typename T1, typename T2, typename T5, typename T6>
class Child2 : public Base<T1, T2> {
public:
    Child2(T1 v1, T2 v2, T5 v5, T6 v6) : Base<T1, T2>(v1, v2), value5(v5), value6(v6) {
        std::cout << "Child2 constructor" << std::endl;
    }
    ~Child2() {
        std::cout << "Child2 destructor" << std::endl;
    }

    void printChild2() const {
        Base<T1, T2>::printBase();
        std::cout << "Value5: " << value5 << std::endl;
        std::cout << "Value6: " << value6 << std::endl;
    }

private:
    T5 value5;
    T6 value6;
};

int main() {
    Child<int, double, std::string, char> child(10, 3.14, "Hello", 'A');
    child.printChild();
    std::cout << std::endl;

    Child2<float, int, bool, float> child2(2.71f, 42, true, 1.618f);
    child2.printChild2();

    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

class FileHandler {
public:
    virtual void Display(const char* path) {
        std::ifstream file(path);
        if (file.is_open()) {
            std::string line;
            while (getline(file, line)) {
                std::cout << line << std::endl;
            }
            file.close();
        }
        else {
            std::cerr << "Не удалось открыть файл: " << path << std::endl;
        }
    }
};

class AsciiFileHandler : public FileHandler {
public:
    void Display(const char* path) override {
        std::ifstream file(path);
        if (file.is_open()) {
            char c;
            while (file.get(c)) {
                std::cout << static_cast<int>(c) << " ";
            }
            std::cout << std::endl;
            file.close();
        }
        else {
            std::cerr << "Не удалось открыть файл: " << path << std::endl;
        }
    }
};

class BinaryFileHandler : public FileHandler {
public:
    void Display(const char* path) override {
        std::ifstream file(path, std::ios::binary);
        if (file.is_open()) {
            unsigned char c;
            while (file.read(reinterpret_cast<char*>(&c), 1)) {
                for (int i = 7; i >= 0; --i) {
                    std::cout << ((c >> i) & 1);
                }
                std::cout << " ";
            }
            std::cout << std::endl;
            file.close();
        }
        else {
            std::cerr << "Не удалось открыть файл: " << path << std::endl;
        }
    }
};

int main() 
{
    setlocale(LC_ALL, "Russian");
    FileHandler* handler1 = new FileHandler();
    FileHandler* handler2 = new AsciiFileHandler();
    FileHandler* handler3 = new BinaryFileHandler();

    handler1->Display("test.txt");
    handler2->Display("test.txt");
    handler3->Display("test.txt");

    delete handler1;
    delete handler2;
    delete handler3;

    return 0;
}

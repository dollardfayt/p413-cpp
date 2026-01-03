#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class PhoneBookEntry {
private:
    char* fullName;
    std::string homePhone;
    std::string workPhone;
    std::string mobilePhone;
    std::string additionalInfo;

public:
    PhoneBookEntry(const char* name = "", const std::string& home = "", const std::string& work = "", const std::string& mobile = "", const std::string& info = "")
        : homePhone(home), workPhone(work), mobilePhone(mobile), additionalInfo(info) {
        fullName = new char[strlen(name) + 1];
        strcpy(fullName, name);
    }

    ~PhoneBookEntry() {
        delete[] fullName;
    }

    void display() const {
        std::cout << "ФИО: " << fullName << std::endl;
        std::cout << "Домашний телефон: " << homePhone << std::endl;
        std::cout << "Рабочий телефон: " << workPhone << std::endl;
        std::cout << "Мобильный телефон: " << mobilePhone << std::endl;
        std::cout << "Дополнительная информация: " << additionalInfo << std::endl;
    }

    const char* getFullName() const {
        return fullName;
    }

    void setFullName(const char* name) {
        delete[] fullName;
        fullName = new char[strlen(name) + 1];
        strcpy(fullName, name);
    }

    friend std::ostream& operator<<(std::ostream& os, const PhoneBookEntry& entry) {
        os << entry.fullName << std::endl;
        os << entry.homePhone << std::endl;
        os << entry.workPhone << std::endl;
        os << entry.mobilePhone << std::endl;
        os << entry.additionalInfo << std::endl;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, PhoneBookEntry& entry) {
        char buffer[256];
        is.getline(buffer, 256);
        entry.setFullName(buffer);
        std::getline(is, entry.homePhone);
        std::getline(is, entry.workPhone);
        std::getline(is, entry.mobilePhone);
        std::getline(is, entry.additionalInfo);
        return is;
    }
};

void addEntry(std::vector<PhoneBookEntry>& book) {
    char name[256];
    std::string home, work, mobile, info;

    std::cout << "Введите ФИО: ";
    std::cin.getline(name, 256);
    std::cout << "Введите домашний телефон: ";
    std::getline(std::cin, home);
    std::cout << "Введите рабочий телефон: ";
    std::getline(std::cin, work);
    std::cout << "Введите мобильный телефон: ";
    std::getline(std::cin, mobile);
    std::cout << "Введите дополнительную информацию: ";
    std::getline(std::cin, info);

    book.emplace_back(name, home, work, mobile, info);
}

void deleteEntry(std::vector<PhoneBookEntry>& book, const std::string& name) {
    for (size_t i = 0; i < book.size(); ++i) {
        if (strcmp(book[i].getFullName(), name.c_str()) == 0) {
            book.erase(book.begin() + i);
            std::cout << "Запись удалена." << std::endl;
            return;
        }
    }
    std::cout << "Запись не найдена." << std::endl;
}

void searchEntry(const std::vector<PhoneBookEntry>& book, const std::string& name) {
    for (const auto& entry : book) {
        if (strcmp(entry.getFullName(), name.c_str()) == 0) {
            entry.display();
            return;
        }
    }
    std::cout << "Запись не найдена." << std::endl;
}

void displayAllEntries(const std::vector<PhoneBookEntry>& book) {
    if (book.empty()) {
        std::cout << "Книга пуста." << std::endl;
        return;
    }
    for (const auto& entry : book) {
        entry.display();
        std::cout << std::endl;
    }
}

void saveToFile(const std::vector<PhoneBookEntry>& book, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& entry : book) {
            file << entry;
        }
        file.close();
        std::cout << "Информация сохранена в файл " << filename << std::endl;
    }
    else {
        std::cerr << "Не удалось открыть файл для записи." << std::endl;
    }
}

void loadFromFile(std::vector<PhoneBookEntry>& book, const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        book.clear();
        PhoneBookEntry entry;
        while (file.peek() != EOF) {
            file >> entry;

            if (file.good()) book.push_back(entry);
        }
        file.close();
        std::cout << "Информация загружена из файла " << filename << std::endl;
    }
    else {
        std::cerr << "Не удалось открыть файл для чтения." << std::endl;
    }
}

int main() {
    std::vector<PhoneBookEntry> phoneBook;
    std::string filename = "phonebook.txt";

    while (true) {
        std::cout << "Меню:\n1. Добавить абонента\n2. Удалить абонента\n3. Поиск абонента\n4. Показать всех абонентов\n5. Сохранить в файл\n6. Загрузить из файла\n0. Выход\nВыберите действие: ";
        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            addEntry(phoneBook);
            break;
        case 2: {
            std::string name;
            std::cout << "Введите ФИО абонента для удаления: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            deleteEntry(phoneBook, name);
            break;
        }
        case 3: {
            std::string name;
            std::cout << "Введите ФИО абонента для поиска: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            searchEntry(phoneBook, name);
            break;
        }
        case 4:
            displayAllEntries(phoneBook);
            break;
        case 5:
            saveToFile(phoneBook, filename);
            break;
        case 6:
            loadFromFile(phoneBook, filename);
            break;
        case 0:
            return 0;
        default:
            std::cout << "Неверный выбор." << std::endl;
        }
    }

    return 0;
}
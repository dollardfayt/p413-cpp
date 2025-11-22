#include <iostream>
#include <string>
#include <vector>

class Passport {
private:
    std::string name;
    std::string surname;
    std::string patronymic;
    std::string birthDate;
    std::string issueDate;
    std::string issuingAuthority;
    std::string idNumber;

public:
    Passport(std::string name, std::string surname, std::string patronymic, std::string birthDate,
        std::string issueDate, std::string issuingAuthority, std::string idNumber) :
        name(name), surname(surname), patronymic(patronymic), birthDate(birthDate),
        issueDate(issueDate), issuingAuthority(issuingAuthority), idNumber(idNumber) {
    }

    std::string getName() const { return name; }
    std::string getSurname() const { return surname; }
    std::string getPatronymic() const { return patronymic; }
    std::string getBirthDate() const { return birthDate; }
    std::string getIssueDate() const { return issueDate; }
    std::string getIssuingAuthority() const { return issuingAuthority; }
    std::string getIdNumber() const { return idNumber; }

    void setName(const std::string& newName) { name = newName; }
    void setSurname(const std::string& newSurname) { surname = newSurname; }
    void setPatronymic(const std::string& newPatronymic) { patronymic = newPatronymic; }
    void setBirthDate(const std::string& newBirthDate) { birthDate = newBirthDate; }
    void setIssueDate(const std::string& newIssueDate) { issueDate = newIssueDate; }
    void setIssuingAuthority(const std::string& newIssuingAuthority) { issuingAuthority = newIssuingAuthority; }
    void setIdNumber(const std::string& newIdNumber) { idNumber = newIdNumber; }

    virtual void displayInfo() const {
        std::cout << "Имя: " << name << std::endl;
        std::cout << "Фамилия: " << surname << std::endl;
        std::cout << "Отчество: " << patronymic << std::endl;
        std::cout << "Дата рождения: " << birthDate << std::endl;
        std::cout << "Дата выдачи: " << issueDate << std::endl;
        std::cout << "Кем выдан: " << issuingAuthority << std::endl;
        std::cout << "Номер паспорта: " << idNumber << std::endl;
    }
};

class ForeignPassport : public Passport {
private:
    std::string foreignPassportNumber;
    std::vector<std::string> visas;

public:
    ForeignPassport(std::string name, std::string surname, std::string patronymic, std::string birthDate,
        std::string issueDate, std::string issuingAuthority, std::string idNumber,
        std::string foreignPassportNumber) :
        Passport(name, surname, patronymic, birthDate, issueDate, issuingAuthority, idNumber),
        foreignPassportNumber(foreignPassportNumber) {
    }

    std::string getForeignPassportNumber() const { return foreignPassportNumber; }

    void setForeignPassportNumber(const std::string& newForeignPassportNumber) { foreignPassportNumber = newForeignPassportNumber; }

    void addVisa(const std::string& visa) { visas.push_back(visa); }
    void removeVisa(const std::string& visa) {
        for (size_t i = 0; i < visas.size(); ++i) {
            if (visas[i] == visa) {
                visas.erase(visas.begin() + i);
                return;
            }
        }
    }

    std::vector<std::string> getVisas() const { return visas; }


    void displayInfo() const override {
        Passport::displayInfo();
        std::cout << "Номер загранпаспорта: " << foreignPassportNumber << std::endl;
        std::cout << "Визы:" << std::endl;
        for (const auto& visa : visas) {
            std::cout << "- " << visa << std::endl;
        }
    }
};

int main() 
{
    setlocale(LC_ALL, "Russian");
    Passport ukrainianPassport("Иван", "Иванов", "Иванович", "01.01.1990", "01.01.2010", "ДМС Украины", "АВ123456");
    ForeignPassport foreignPassport("Петр", "Петров", "Петрович", "02.02.1992", "02.02.2012", "ДМС Украины", "КЕ654321", "ZA1234567");

    std::cout << "Информация об украинском паспорте:" << std::endl;
    ukrainianPassport.displayInfo();

    std::cout << "\nИнформация о загранпаспорте:" << std::endl;
    foreignPassport.displayInfo();

    foreignPassport.addVisa("США (B1/B2)");
    foreignPassport.addVisa("Шенгенская зона");

    std::cout << "\nИнформация о загранпаспорте (с визами):" << std::endl;
    foreignPassport.displayInfo();

    foreignPassport.removeVisa("США (B1/B2)");

    std::cout << "\nИнформация о загранпаспорте (после удаления визы):" << std::endl;
    foreignPassport.displayInfo();

    return 0;
}

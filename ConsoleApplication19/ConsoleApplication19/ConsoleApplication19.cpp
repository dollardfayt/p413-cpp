#include <iostream>
#include <string>

class Student {
private:
    std::string name;
    std::string group;
    int studentId;
    double averageGrade;

public:
    Student(std::string name, std::string group, int studentId, double averageGrade) :
        name(name), group(group), studentId(studentId), averageGrade(averageGrade) {
    }

    std::string getName() const { return name; }
    std::string getGroup() const { return group; }
    int getStudentId() const { return studentId; }
    double getAverageGrade() const { return averageGrade; }

    void setName(const std::string& newName) { name = newName; }
    void setGroup(const std::string& newGroup) { group = newGroup; }
    void setStudentId(int newStudentId) { studentId = newStudentId; }
    void setAverageGrade(double newAverageGrade) { averageGrade = newAverageGrade; }


    virtual void displayInfo() const {
        std::cout << "Имя: " << name << std::endl;
        std::cout << "Группа: " << group << std::endl;
        std::cout << "ID: " << studentId << std::endl;
        std::cout << "Средний балл: " << averageGrade << std::endl;
    }
};

class Aspirant : public Student {
private:
    std::string researchTopic;
    std::string supervisor;

public:
    Aspirant(std::string name, std::string group, int studentId, double averageGrade, std::string researchTopic, std::string supervisor) :
        Student(name, group, studentId, averageGrade), researchTopic(researchTopic), supervisor(supervisor) {
    }

    std::string getResearchTopic() const { return researchTopic; }
    std::string getSupervisor() const { return supervisor; }

    void setResearchTopic(const std::string& newTopic) { researchTopic = newTopic; }
    void setSupervisor(const std::string& newSupervisor) { supervisor = newSupervisor; }

    void displayInfo() const override {
        Student::displayInfo();
        std::cout << "Тема исследования: " << researchTopic << std::endl;
        std::cout << "Научный руководитель: " << supervisor << std::endl;
    }
};

int main() 
{
    setlocale(LC_ALL, "Russian");
    Student student1("Иван Иванов", "ИВТ-21", 12345, 4.5);
    Aspirant aspirant1("Петр Петров", "ИВТ-22", 67890, 4.8, "Алгоритмы машинного обучения", "Проф. Сидоров");

    std::cout << "Информация о студенте:" << std::endl;
    student1.displayInfo();

    std::cout << "\nИнформация об аспиранте:" << std::endl;
    aspirant1.displayInfo();


    Student* ptr = &aspirant1;
    std::cout << "\nИнформация об аспиранте через указатель на Student:" << std::endl;
    ptr->displayInfo();


    return 0;
}

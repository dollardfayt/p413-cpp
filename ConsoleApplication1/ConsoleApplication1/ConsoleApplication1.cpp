#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <clocale>
#include <ctime>

class Worker {
private:
    std::string fio;
    std::string dolzhnost;
    int godPostupleniya;
    double zarplata;

public:
    Worker(const std::string& fio, const std::string& dolzhnost, int godPostupleniya, double zarplata)
        : fio(fio), dolzhnost(dolzhnost), godPostupleniya(godPostupleniya), zarplata(zarplata) {
    }

    const std::string& getFio() const { return fio; }
    const std::string& getDolzhnost() const { return dolzhnost; }
    int getGodPostupleniya() const { return godPostupleniya; }
    double getZarplata() const { return zarplata; }

    int getStazh() const {
        time_t t = time(nullptr);
        tm* now = localtime(&t);
        int currentYear = now->tm_year + 1900;
        return currentYear - godPostupleniya;
    }


    void displayWorker() const {
        std::cout << "ФИО: " << fio << std::endl;
        std::cout << "Должность: " << dolzhnost << std::endl;
        std::cout << "Год поступления: " << godPostupleniya << std::endl;
        std::cout << "Зарплата: " << zarplata << std::endl;
        std::cout << "Стаж: " << getStazh() << std::endl;
        std::cout << std::endl;
    }
};

void showWorkersByStazh(const std::vector<Worker>& workers, int stazh) {
    bool found = false;
    for (const auto& worker : workers) {
        if (worker.getStazh() > stazh) {
            worker.displayWorker();
            found = true;
        }
    }
    if (!found) {
        std::cout << "Работники со стажем более " << stazh << " лет не найдены." << std::endl;
    }
}

void showWorkersByZarplata(const std::vector<Worker>& workers, double zarplata) {
    bool found = false;
    for (const auto& worker : workers) {
        if (worker.getZarplata() > zarplata) {
            worker.displayWorker();
            found = true;
        }
    }
    if (!found) {
        std::cout << "Работники с зарплатой больше " << zarplata << " не найдены." << std::endl;
    }
}

void showWorkersByDolzhnost(const std::vector<Worker>& workers, const std::string& dolzhnost) {
    bool found = false;
    for (const auto& worker : workers) {
        if (worker.getDolzhnost() == dolzhnost) {
            worker.displayWorker();
            found = true;
        }
    }
    if (!found) {
        std::cout << "Работники на должности \"" << dolzhnost << "\" не найдены." << std::endl;
    }
}


int main() {
    setlocale(LC_ALL, "Russian");

    std::vector<Worker> workers;
    workers.emplace_back("Иванов Иван Иванович", "Инженер", 2010, 70000.0);
    workers.emplace_back("Петров Петр Петрович", "Менеджер", 2015, 80000.0);
    workers.emplace_back("Сидоров Сидор Сидорович", "Программист", 2018, 90000.0);
    workers.emplace_back("Смирнова Анна Ивановна", "Бухгалтер", 2012, 60000.0);
    workers.emplace_back("Козлова Екатерина Петровна", "Менеджер", 2020, 75000.0);

    std::cout << "Работники со стажем более 10 лет:" << std::endl;
    showWorkersByStazh(workers, 10);

    std::cout << "Работники с зарплатой больше 75000:" << std::endl;
    showWorkersByZarplata(workers, 75000);

    std::cout << "Работники на должности Менеджер:" << std::endl;
    showWorkersByDolzhnost(workers, "Менеджер");

    return 0;
}

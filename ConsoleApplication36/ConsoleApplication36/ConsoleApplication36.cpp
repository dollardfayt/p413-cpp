#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <random>

struct PrintJob {
public:
    PrintJob(std::string user, int priority, int submission_time)
        : user(user), priority(priority), submission_time(submission_time) {
    }

    std::string getUser() const { return user; }
    int getPriority() const { return priority; }
    int getSubmissionTime() const { return submission_time; } 

private:
    std::string user;
    int priority;
    int submission_time;
};

struct JobComparison {
    bool operator()(const PrintJob& a, const PrintJob& b) {
        return a.getPriority() > b.getPriority();
    }
};

struct PrintJobHistory {
    std::string user;
    int print_start_time;
    int print_end_time;
};

class Printer {
private:
    std::priority_queue<PrintJob, std::vector<PrintJob>, JobComparison> queue;
    std::vector<PrintJobHistory> history;
    int currentTime = 0;
    std::mt19937 generator;

public:
    Printer(int seed) : generator(seed) {}

    void addJob(PrintJob job) {
        queue.push(job);
    }

    void processJobs() {
        while (!queue.empty()) {
            PrintJob job = queue.top();
            queue.pop();

            int printDuration = generatePrintDuration();
            int startTime = currentTime;
            currentTime += printDuration;
            int endTime = currentTime;

            history.push_back({ job.getUser(), startTime, endTime });

            std::cout << "Printing job for " << job.getUser()
                << " (Priority: " << job.getPriority() << ")"
                << " from " << startTime << " to " << endTime << std::endl;
        }
    }

    void displayStatistics() {
        std::cout << "\n--- Printing Statistics ---" << std::endl;
        for (const auto& record : history) {
            std::cout << "User: " << record.user
                << ", Start Time: " << record.print_start_time
                << ", End Time: " << record.print_end_time << std::endl;
        }
    }

private:
    int generatePrintDuration() {
        std::uniform_int_distribution<> distrib(5, 15);
        return distrib(generator);
    }
};

int main() {
    Printer printer(42);

    printer.addJob({ "Alice", 1, 0 });
    printer.addJob({ "Bob", 3, 1 });
    printer.addJob({ "Charlie", 2, 2 });
    printer.addJob({ "David", 1, 3 });

    printer.processJobs();

    printer.displayStatistics();

    return 0;
}

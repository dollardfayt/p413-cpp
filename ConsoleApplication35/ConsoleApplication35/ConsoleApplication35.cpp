#include <iostream>
#include <queue>
#include <random>
#include <vector>

struct Passenger {
    int arrival_time;
    int wait_time;
};

struct Minibus {
    int arrival_time;
    int seats_available;
};

class BusStop {
public:
    BusStop(bool is_terminal) : is_terminal_(is_terminal) {}

    void addPassenger(int arrival_time) {
        passengers_.push({ arrival_time, 0 });
    }

    void addMinibus(int arrival_time, int seats) {
        minibuses_.push({ arrival_time, seats });
    }

    Passenger getNextPassenger() {
        Passenger passenger = passengers_.front();
        passengers_.pop();
        return passenger;
    }

    Minibus getNextMinibus() {
        Minibus minibus = minibuses_.front();
        minibuses_.pop();
        return minibus;
    }

    bool hasPassengers() const {
        return !passengers_.empty();
    }

    bool hasMinibuses() const {
        return !minibuses_.empty();
    }

    int getNumberOfPassengers() const {
        return passengers_.size();
    }

private:
    std::queue<Passenger> passengers_;
    std::queue<Minibus>     minibuses_;
    bool                    is_terminal_;
};

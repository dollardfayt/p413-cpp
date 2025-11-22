#include <iostream>
#include <string>

class TransportVehicle {
public:
    virtual double calculateTravelTime(double distance) = 0;
    virtual double calculateCost(double distance, double cargoWeight) = 0;
    virtual std::string getType() const = 0;

    virtual ~TransportVehicle() {}
};

class Car : public TransportVehicle {
private:
    double speed;
    double fuelConsumption;
    double fuelPrice;
    double driverWagePerHour;

public:
    Car(double speed, double fuelConsumption, double fuelPrice, double driverWagePerHour) :
        speed(speed), fuelConsumption(fuelConsumption), fuelPrice(fuelPrice), driverWagePerHour(driverWagePerHour) {
    }

    double calculateTravelTime(double distance) override {
        return distance / speed;
    }

    double calculateCost(double distance, double cargoWeight) override {
        double fuelCost = (distance / 100) * fuelConsumption * fuelPrice;
        double travelTime = calculateTravelTime(distance);
        double driverCost = travelTime * driverWagePerHour;
        return fuelCost + driverCost;
    }

    std::string getType() const override {
        return "Автомобиль";
    }
};

class Bicycle : public TransportVehicle {
private:
    double speed;
    double energyCostPerKm;

public:
    Bicycle(double speed, double energyCostPerKm) : speed(speed), energyCostPerKm(energyCostPerKm) {}

    double calculateTravelTime(double distance) override {
        return distance / speed;
    }

    double calculateCost(double distance, double cargoWeight) override {
        return distance * energyCostPerKm + cargoWeight * 0.1;
    }

    std::string getType() const override {
        return "Велосипед";
    }
};

class Cart : public TransportVehicle {
private:
    double speed;
    double horseFeedCostPerDay;
    double maintenanceCostPerDay;
public:
    Cart(double speed, double horseFeedCostPerDay, double maintenanceCostPerDay) :
        speed(speed), horseFeedCostPerDay(horseFeedCostPerDay), maintenanceCostPerDay(maintenanceCostPerDay) {
    }

    double calculateTravelTime(double distance) override {
        return distance / speed;
    }

    double calculateCost(double distance, double cargoWeight) override {
        double travelTime = calculateTravelTime(distance);
        double days = travelTime / 24.0;
        double horseFeedCost = days * horseFeedCostPerDay;
        double maintenanceCost = days * maintenanceCostPerDay;
        return horseFeedCost + maintenanceCost + cargoWeight * 0.05;
    }

    std::string getType() const override {
        return "Повозка";
    }
};

int main() 
{
    setlocale(LC_ALL, "Russian");
    Car car(80.0, 10.0, 60.0, 400.0);
    Bicycle bicycle(20.0, 10.0);
    Cart cart(10.0, 200.0, 100.0);

    double distance = 200.0;
    double cargoWeight = 50.0;

    TransportVehicle* vehicles[] = { &car, &bicycle, &cart };
    for (TransportVehicle* vehicle : vehicles) {
        std::cout << "Тип транспорта: " << vehicle->getType() << std::endl;
        std::cout << "Время в пути: " << vehicle->calculateTravelTime(distance) << " часов" << std::endl;
        std::cout << "Стоимость перевозки: " << vehicle->calculateCost(distance, cargoWeight) << " руб" << std::endl;
        std::cout << std::endl;
    }


    return 0;
}

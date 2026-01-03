#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

class Reservoir;

enum class ReservoirType {
    SEA,
    LAKE,
    POND,
    POOL,
    OTHER
};

ReservoirType stringToReservoirType(const std::string& str) {
    if (str == "SEA") return ReservoirType::SEA;
    if (str == "LAKE") return ReservoirType::LAKE;
    if (str == "POND") return ReservoirType::POND;
    if (str == "POOL") return ReservoirType::POOL;
    return ReservoirType::OTHER;
}


std::string reservoirTypeToString(ReservoirType type) {
    switch (type) {
    case ReservoirType::SEA: return "SEA";
    case ReservoirType::LAKE: return "LAKE";
    case ReservoirType::POND: return "POND";
    case ReservoirType::POOL: return "POOL";
    default: return "OTHER";
    }
}


class Reservoir {
private:
    std::string name;
    double width;
    double length;
    double maxDepth;
    ReservoirType type;

public:

    explicit Reservoir() : name("Undefined"), width(0.0), length(0.0), maxDepth(0.0), type(ReservoirType::OTHER) {
        std::cout << "Reservoir default constructor called." << std::endl;
    }

    explicit Reservoir(const std::string& name, double width, double length, double maxDepth, ReservoirType type)
        : name(name), width(width), length(length), maxDepth(maxDepth), type(type) {
        std::cout << "Reservoir parameterized constructor called." << std::endl;
    }

    Reservoir(const Reservoir& other) : name(other.name), width(other.width), length(other.length), maxDepth(other.maxDepth), type(other.type) {
        std::cout << "Reservoir copy constructor called." << std::endl;
    }

    ~Reservoir() {
        std::cout << "Reservoir destructor called for: " << name << std::endl;
    }


    Reservoir& operator=(const Reservoir& other) {
        std::cout << "Reservoir assignment operator called." << std::endl;
        if (this != &other) {
            name = other.name;
            width = other.width;
            length = other.length;
            maxDepth = other.maxDepth;
            type = other.type;
        }
        return *this;
    }


    double approximateVolume() const {
        return width * length * maxDepth;
    }

    double surfaceArea() const {
        return width * length;
    }

    bool isSameType(const Reservoir& other) const {
        return type == other.type;
    }

    bool compareSurfaceArea(const Reservoir& other) const {
        if (isSameType(other)) {
            return surfaceArea() > other.surfaceArea();
        }
        else {
            std::cout << "Warning: Reservoirs are of different types.  Comparison may not be meaningful." << std::endl;
            return false;
        }
    }

    void setName(const std::string& name) {
        this->name = name;
    }

    void setWidth(double width) {
        this->width = width;
    }

    void setLength(double length) {
        this->length = length;
    }

    void setMaxDepth(double maxDepth) {
        this->maxDepth = maxDepth;
    }

    void setType(ReservoirType type) {
        this->type = type;
    }

    const std::string& getName() const {
        return name;
    }

    double getWidth() const {
        return width;
    }

    double getLength() const {
        return length;
    }

    double getMaxDepth() const {
        return maxDepth;
    }

    ReservoirType getType() const {
        return type;
    }


    void displayReservoirInfo() const {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Type: " << reservoirTypeToString(type) << std::endl;
        std::cout << "Width: " << width << std::endl;
        std::cout << "Length: " << length << std::endl;
        std::cout << "Max Depth: " << maxDepth << std::endl;
        std::cout << "Approximate Volume: " << approximateVolume() << std::endl;
        std::cout << "Surface Area: " << surfaceArea() << std::endl;
    }

    void saveToTextFile(std::ofstream& file) const {
        file << name << std::endl;
        file << width << std::endl;
        file << length << std::endl;
        file << maxDepth << std::endl;
        file << reservoirTypeToString(type) << std::endl;
    }

    void loadFromTextFile(std::ifstream& file) {
        if (file.is_open()) {
            std::getline(file, name);
            file >> width;
            file >> length;
            file >> maxDepth;
            std::string typeStr;
            file >> typeStr;
            type = stringToReservoirType(typeStr);

            file.ignore();
        }
        else {
            std::cerr << "Error: Unable to open file for reading." << std::endl;
        }
    }

    void saveToBinaryFile(std::ofstream& file) const {
        size_t nameLength = name.length();
        file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        file.write(name.c_str(), nameLength);
        file.write(reinterpret_cast<const char*>(&width), sizeof(width));
        file.write(reinterpret_cast<const char*>(&length), sizeof(length));
        file.write(reinterpret_cast<const char*>(&maxDepth), sizeof(maxDepth));
        file.write(reinterpret_cast<const char*>(&type), sizeof(type));
    }

    void loadFromBinaryFile(std::ifstream& file) {
        size_t nameLength;
        file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        name.resize(nameLength);
        file.read(&name[0], nameLength);
        file.read(reinterpret_cast<char*>(&width), sizeof(width));
        file.read(reinterpret_cast<char*>(&length), sizeof(length));
        file.read(reinterpret_cast<char*>(&maxDepth), sizeof(maxDepth));
        file.read(reinterpret_cast<char*>(&type), sizeof(type));
    }
};


class ReservoirManager {
private:
    std::vector<Reservoir> reservoirs;

public:
    void addReservoir(const Reservoir& reservoir) {
        reservoirs.push_back(reservoir);
    }

    bool removeReservoir(const std::string& name) {
        for (size_t i = 0; i < reservoirs.size(); ++i) {
            if (reservoirs[i].getName() == name) {
                reservoirs.erase(reservoirs.begin() + i);
                return true;
            }
        }
        std::cout << "Reservoir with name '" << name << "' not found." << std::endl;
        return false;
    }

    Reservoir& getReservoir(size_t index) {
        if (index < reservoirs.size()) {
            return reservoirs[index];
        }
        else {
            throw std::out_of_range("Index out of range");
        }
    }

    const Reservoir& getReservoir(size_t index) const {
        if (index < reservoirs.size()) {
            return reservoirs[index];
        }
        else {
            throw std::out_of_range("Index out of range");
        }
    }


    size_t getSize() const {
        return reservoirs.size();
    }

    void saveAllToTextFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << reservoirs.size() << std::endl;
            for (const auto& reservoir : reservoirs) {
                reservoir.saveToTextFile(file);
            }
            file.close();
            std::cout << "Reservoirs saved to text file: " << filename << std::endl;
        }
        else {
            std::cerr << "Error: Unable to open file for writing." << std::endl;
        }
    }

    void loadAllFromTextFile(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            size_t count;
            file >> count;
            file.ignore();

            reservoirs.clear();
            for (size_t i = 0; i < count; ++i) {
                Reservoir reservoir;
                reservoir.loadFromTextFile(file);
                reservoirs.push_back(reservoir);
            }
            file.close();
            std::cout << "Reservoirs loaded from text file: " << filename << std::endl;
        }
        else {
            std::cerr << "Error: Unable to open file for reading." << std::endl;
        }
    }



    void saveAllToBinaryFile(const std::string& filename) const {
        std::ofstream file(filename, std::ios::binary);
        if (file.is_open()) {
            size_t size = reservoirs.size();
            file.write(reinterpret_cast<const char*>(&size), sizeof(size));
            for (const auto& reservoir : reservoirs) {
                reservoir.saveToBinaryFile(file);
            }
            file.close();
            std::cout << "Reservoirs saved to binary file: " << filename << std::endl;
        }
        else {
            std::cerr << "Error: Unable to open file for writing." << std::endl;
        }
    }

    void loadAllFromBinaryFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (file.is_open()) {
            size_t size;
            file.read(reinterpret_cast<char*>(&size), sizeof(size));
            reservoirs.clear();
            for (size_t i = 0; i < size; ++i) {
                Reservoir reservoir;
                reservoir.loadFromBinaryFile(file);
                reservoirs.push_back(reservoir);
            }
            file.close();
            std::cout << "Reservoirs loaded from binary file: " << filename << std::endl;
        }
        else {
            std::cerr << "Error: Unable to open file for reading." << std::endl;
        }
    }
};


int main() {
    ReservoirManager manager;

    Reservoir sea("Black Sea", 1000, 500, 2000, ReservoirType::SEA);
    Reservoir lake("Baikal", 600, 80, 1642, ReservoirType::LAKE);
    Reservoir pond("Pond", 10, 5, 3, ReservoirType::POND);
    Reservoir pool("Swimming Pool", 25, 10, 2, ReservoirType::POOL);


    manager.addReservoir(sea);
    manager.addReservoir(lake);
    manager.addReservoir(pond);
    manager.addReservoir(pool);



    std::cout << "\nDisplaying all reservoirs:\n";
    for (size_t i = 0; i < manager.getSize(); ++i) {
        std::cout << "Reservoir #" << i + 1 << ":\n";
        manager.getReservoir(i).displayReservoirInfo();
        std::cout << std::endl;
    }


    manager.saveAllToTextFile("reservoirs.txt");
    ReservoirManager loadedManagerText;
    loadedManagerText.loadAllFromTextFile("reservoirs.txt");

    std::cout << "\nLoaded from text file:\n";
    for (size_t i = 0; i < loadedManagerText.getSize(); ++i) {
        std::cout << "Reservoir #" << i + 1 << ":\n";
        loadedManagerText.getReservoir(i).displayReservoirInfo();
        std::cout << std::endl;
    }


    manager.saveAllToBinaryFile("reservoirs.bin");
    ReservoirManager loadedManagerBinary;
    loadedManagerBinary.loadAllFromBinaryFile("reservoirs.bin");

    std::cout << "\nLoaded from binary file:\n";
    for (size_t i = 0; i < loadedManagerBinary.getSize(); ++i) {
        std::cout << "Reservoir #" << i + 1 << ":\n";
        loadedManagerBinary.getReservoir(i).displayReservoirInfo();
        std::cout << std::endl;
    }


    manager.removeReservoir("Baikal");

    std::cout << "\nAfter removing Baikal:\n";
    for (size_t i = 0; i < manager.getSize(); ++i) {
        std::cout << "Reservoir #" << i + 1 << ":\n";
        manager.getReservoir(i).displayReservoirInfo();
        std::cout << std::endl;
    }


    return 0;
}

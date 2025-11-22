#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

enum class ReservoirType {
    SEA,
    LAKE,
    POND,
    POOL,
    OTHER
};

std::ostream& operator<<(std::ostream& os, const ReservoirType& type) {
    switch (type) {
    case ReservoirType::SEA: os << "Sea"; break;
    case ReservoirType::LAKE: os << "Lake"; break;
    case ReservoirType::POND: os << "Pond"; break;
    case ReservoirType::POOL: os << "Pool"; break;
    default: os << "Other"; break;
    }
    return os;
}

std::istream& operator>>(std::istream& is, ReservoirType& type) {
    int enumValue;
    is >> enumValue;
    type = static_cast<ReservoirType>(enumValue);
    return is;
}



class Reservoir {
private:
    std::string name;
    double width;
    double length;
    double maxDepth;
    ReservoirType type;

public:
    Reservoir() : name(""), width(0.0), length(0.0), maxDepth(0.0), type(ReservoirType::OTHER) {}
    explicit Reservoir(const std::string& name) : name(name), width(0.0), length(0.0), maxDepth(0.0), type(ReservoirType::OTHER) {}
    Reservoir(const std::string& name, double width, double length, double maxDepth, ReservoirType type)
        : name(name), width(width), length(length), maxDepth(maxDepth), type(type) {
    }

    Reservoir(const Reservoir& other) : name(other.name), width(other.width), length(other.length), maxDepth(other.maxDepth), type(other.type) {}

    Reservoir& operator=(const Reservoir& other) {
        if (this != &other) {
            name = other.name;
            width = other.width;
            length = other.length;
            maxDepth = other.maxDepth;
            type = other.type;
        }
        return *this;
    }

    ~Reservoir() {}

    std::string getName() const { return name; }
    void setName(const std::string& name) { this->name = name; }

    double getWidth() const { return width; }
    void setWidth(double width) { this->width = width; }

    double getLength() const { return length; }
    void setLength(double length) { this->length = length; }

    double getMaxDepth() const { return maxDepth; }
    void setMaxDepth(double maxDepth) { this->maxDepth = maxDepth; }

    ReservoirType getType() const { return type; }
    void setType(ReservoirType type) { this->type = type; }

    double approximateVolume() const { return width * length * maxDepth; }
    double surfaceArea() const { return width * length; }

    bool isSameType(const Reservoir& other) const { return type == other.type; }

    int compareSurfaceArea(const Reservoir& other) const {
        if (!isSameType(other)) return 0;
        double area1 = surfaceArea();
        double area2 = other.surfaceArea();
        if (area1 < area2) return -1;
        if (area1 > area2) return 1;
        return 0;
    }

    Reservoir clone() const { return Reservoir(*this); }

    void displayInfo() const {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Type: " << type << std::endl;
        std::cout << "Width: " << width << std::endl;
        std::cout << "Length: " << length << std::endl;
        std::cout << "Max Depth: " << maxDepth << std::endl;
        std::cout << "Approximate Volume: " << approximateVolume() << std::endl;
        std::cout << "Surface Area: " << surfaceArea() << std::endl;
    }
};

void addReservoir(std::vector<Reservoir>& reservoirs) {
    std::string name;
    double width, length, maxDepth;
    int type;

    std::cout << "Enter reservoir name: ";
    std::cin >> name;
    std::cout << "Enter width: ";
    std::cin >> width;
    std::cout << "Enter length: ";
    std::cin >> length;
    std::cout << "Enter max depth: ";
    std::cin >> maxDepth;

    std::cout << "Enter reservoir type (0-SEA, 1-LAKE, 2-POND, 3-POOL, 4-OTHER): ";
    std::cin >> type;

    ReservoirType reservoirType = static_cast<ReservoirType>(type);

    reservoirs.emplace_back(name, width, length, maxDepth, reservoirType);
}

void removeReservoir(std::vector<Reservoir>& reservoirs) {
    std::string name;
    std::cout << "Enter the name of the reservoir to remove: ";
    std::cin >> name;

    auto it = std::remove_if(reservoirs.begin(), reservoirs.end(), [&name](const Reservoir& r) {
        return r.getName() == name;
        });

    if (it == reservoirs.end()) {
        std::cout << "Reservoir not found." << std::endl;
    }
    else {
        reservoirs.erase(it, reservoirs.end());
        std::cout << "Reservoir removed." << std::endl;
    }
}

void displayReservoirs(const std::vector<Reservoir>& reservoirs) {
    for (const auto& reservoir : reservoirs) {
        reservoir.displayInfo();
        std::cout << std::endl;
    }
}

void saveToTextFile(const std::vector<Reservoir>& reservoirs, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& reservoir : reservoirs) {
            file << reservoir.getName() << std::endl;
            file << reservoir.getWidth() << std::endl;
            file << reservoir.getLength() << std::endl;
            file << reservoir.getMaxDepth() << std::endl;
            file << static_cast<int>(reservoir.getType()) << std::endl;
        }
        file.close();
        std::cout << "Data saved to " << filename << std::endl;
    }
    else {
        std::cout << "Unable to open file." << std::endl;
    }
}

void loadFromTextFile(std::vector<Reservoir>& reservoirs, const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        while (file.peek() != EOF) {
            std::string name;
            double width, length, maxDepth;
            int type;

            std::getline(file, name);
            file >> width >> length >> maxDepth >> type;
            file.ignore();

            if (file.fail()) {
                break;
            }
            reservoirs.emplace_back(name, width, length, maxDepth, static_cast<ReservoirType>(type));
        }
        file.close();
        std::cout << "Data loaded from " << filename << std::endl;
    }
    else {
        std::cout << "Unable to open file." << std::endl;
    }
}

void saveToBinaryFile(const std::vector<Reservoir>& reservoirs, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        size_t size = reservoirs.size();
        file.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
        for (const auto& reservoir : reservoirs) {
            size_t nameSize = reservoir.getName().size();
            file.write(reinterpret_cast<const char*>(&nameSize), sizeof(size_t));
            file.write(reservoir.getName().c_str(), nameSize);
            file.write(reinterpret_cast<const char*>(&reservoir.getWidth()), sizeof(double));
            file.write(reinterpret_cast<const char*>(&reservoir.getLength()), sizeof(double));
            file.write(reinterpret_cast<const char*>(&reservoir.getMaxDepth()), sizeof(double));
            int reservoirTypeInt = static_cast<int>(reservoir.getType());
            file.write(reinterpret_cast<const char*>(&reservoirTypeInt), sizeof(int));
        }
        file.close();
        std::cout << "Data saved to " << filename << std::endl;
    }
    else {
        std::cout << "Unable to open file." << std::endl;
    }
}

void loadFromBinaryFile(std::vector<Reservoir>& reservoirs, const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {
        size_t size;
        file.read(reinterpret_cast<char*>(&size), sizeof(size_t));
        reservoirs.clear();
        reservoirs.reserve(size);


        for (size_t i = 0; i < size; ++i) {
            size_t nameSize;
            file.read(reinterpret_cast<char*>(&nameSize), sizeof(size_t));
            std::string name(nameSize, '\0');
            file.read(&name[0], nameSize);
            double width, length, maxDepth;
            int type;

            file.read(reinterpret_cast<char*>(&width), sizeof(double));
            file.read(reinterpret_cast<char*>(&length), sizeof(double));
            file.read(reinterpret_cast<char*>(&maxDepth), sizeof(double));
            file.read(reinterpret_cast<char*>(&type), sizeof(int));

            reservoirs.emplace_back(name, width, length, maxDepth, static_cast<ReservoirType>(type));
        }

        file.close();
        std::cout << "Data loaded from " << filename << std::endl;
    }
    else {
        std::cout << "Unable to open file." << std::endl;
    }
}


int main() {
    std::vector<Reservoir> reservoirs;
    int choice;

    do {
        std::cout << "\nMenu:" << std::endl;
        std::cout << "1. Add reservoir" << std::endl;
        std::cout << "2. Remove reservoir" << std::endl;
        std::cout << "3. Display reservoirs" << std::endl;
        std::cout << "4. Save to text file" << std::endl;
        std::cout << "5. Load from text file" << std::endl;
        std::cout << "6. Save to binary file" << std::endl;
        std::cout << "7. Load from binary file" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            addReservoir(reservoirs);
            break;
        case 2:
            removeReservoir(reservoirs);
            break;
        case 3:
            displayReservoirs(reservoirs);
            break;
        case 4: {
            std::string filename;
            std::cout << "Enter filename to save to: ";
            std::cin >> filename;
            saveToTextFile(reservoirs, filename);
            break;
        }
        case 5: {
            std::string filename;
            std::cout << "Enter filename to load from: ";
            std::cin >> filename;
            loadFromTextFile(reservoirs, filename);
            break;
        }
        case 6: {
            std::string filename;
            std::cout << "Enter filename to save to: ";
            std::cin >> filename;
            saveToBinaryFile(reservoirs, filename);
            break;
        }
        case 7: {
            std::string filename;
            std::cout << "Enter filename to load from: ";
            std::cin >> filename;
            loadFromBinaryFile(reservoirs, filename);
            break;
        }
        case 0:
            std::cout << "Exiting program." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Try again." << std::endl;
        }
    } while (choice != 0);

    return 0;
}

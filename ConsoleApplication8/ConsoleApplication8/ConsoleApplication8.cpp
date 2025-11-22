#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Shape {
public:
    virtual void Show() = 0;
    virtual void Save(std::ofstream& file) = 0;
    virtual void Load(std::ifstream& file) = 0;
    virtual ~Shape() {}

    virtual std::string GetType() const = 0;
};

class Square : public Shape {
private:
    int x;
    int y;
    int side;

public:
    Square(int x, int y, int side) : x(x), y(y), side(side) {}

    void Show() override {
        std::cout << "Square: x=" << x << ", y=" << y << ", side=" << side << std::endl;
    }

    void Save(std::ofstream& file) override {
        file << "Square\n";
        file << x << "\n";
        file << y << "\n";
        file << side << "\n";
    }

    void Load(std::ifstream& file) override {
        file >> x;
        file >> y;
        file >> side;
    }

    std::string GetType() const override {
        return "Square";
    }
};

class Rectangle : public Shape {
private:
    int x;
    int y;
    int width;
    int height;

public:
    Rectangle(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

    void Show() override {
        std::cout << "Rectangle: x=" << x << ", y=" << y << ", width=" << width << ", height=" << height << std::endl;
    }

    void Save(std::ofstream& file) override {
        file << "Rectangle\n";
        file << x << "\n";
        file << y << "\n";
        file << width << "\n";
        file << height << "\n";
    }

    void Load(std::ifstream& file) override {
        file >> x;
        file >> y;
        file >> width;
        file >> height;
    }

    std::string GetType() const override {
        return "Rectangle";
    }
};

class Circle : public Shape {
private:
    int centerX;
    int centerY;
    int radius;

public:
    Circle(int centerX, int centerY, int radius) : centerX(centerX), centerY(centerY), radius(radius) {}

    void Show() override {
        std::cout << "Circle: centerX=" << centerX << ", centerY=" << centerY << ", radius=" << radius << std::endl;
    }

    void Save(std::ofstream& file) override {
        file << "Circle\n";
        file << centerX << "\n";
        file << centerY << "\n";
        file << radius << "\n";
    }

    void Load(std::ifstream& file) override {
        file >> centerX;
        file >> centerY;
        file >> radius;
    }

    std::string GetType() const override {
        return "Circle";
    }
};

class Ellipse : public Shape {
private:
    int x;
    int y;
    int width;
    int height;

public:
    Ellipse(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

    void Show() override {
        std::cout << "Ellipse: x=" << x << ", y=" << y << ", width=" << width << ", height=" << height << std::endl;
    }

    void Save(std::ofstream& file) override {
        file << "Ellipse\n";
        file << x << "\n";
        file << y << "\n";
        file << width << "\n";
        file << height << "\n";
    }

    void Load(std::ifstream& file) override {
        file >> x;
        file >> y;
        file >> width;
        file >> height;
    }

    std::string GetType() const override {
        return "Ellipse";
    }
};

void SaveShapes(const std::vector<Shape*>& shapes, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& shape : shapes) {
            shape->Save(file);
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file for saving: " << filename << std::endl;
    }
}

std::vector<Shape*> LoadShapes(const std::string& filename) {
    std::vector<Shape*> shapes;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string type;
        while (std::getline(file, type)) {
            Shape* shape = nullptr;
            if (type == "Square") {
                shape = new Square(0, 0, 0);
                shape->Load(file);
            }
            else if (type == "Rectangle") {
                shape = new Rectangle(0, 0, 0, 0);
                shape->Load(file);
            }
            else if (type == "Circle") {
                shape = new Circle(0, 0, 0);
                shape->Load(file);
            }
            else if (type == "Ellipse") {
                shape = new Ellipse(0, 0, 0, 0);
                shape->Load(file);
            }
            else {
                std::cerr << "Unknown shape type: " << type << std::endl;
                continue;
            }
            if (shape) {
                shapes.push_back(shape);
            }
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file for loading: " << filename << std::endl;
    }
    return shapes;
}

int main() {
    std::vector<Shape*> shapes;
    shapes.push_back(new Square(10, 20, 30));
    shapes.push_back(new Rectangle(40, 50, 60, 70));
    shapes.push_back(new Circle(80, 90, 100));
    shapes.push_back(new Ellipse(110, 120, 130, 140));

    SaveShapes(shapes, "shapes.txt");

    for (auto& shape : shapes) {
        delete shape;
    }
    shapes.clear();

    std::vector<Shape*> loadedShapes = LoadShapes("shapes.txt");

    std::cout << "Loaded shapes:" << std::endl;
    for (const auto& shape : loadedShapes) {
        shape->Show();
    }

    for (auto& shape : loadedShapes) {
        delete shape;
    }
    loadedShapes.clear();

    return 0;
}

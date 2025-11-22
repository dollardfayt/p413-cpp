#include <iostream>

class Component {
public:
    Component(int id) : id_(id) {
        std::cout << "Component constructor, id = " << id_ << std::endl;
    }
    ~Component() {
        std::cout << "Component destructor, id = " << id_ << std::endl;
    }

protected:
    int id_;
};

class Renderer : virtual public Component {
public:
    Renderer(int id) : Component(id) {
        std::cout << "Renderer constructor" << std::endl;
    }
    ~Renderer() {
        std::cout << "Renderer destructor" << std::endl;
    }
    void render() {
        std::cout << "Rendering with id = " << id_ << std::endl;
    }
};

class Input : virtual public Component {
public:
    Input(int id) : Component(id) {
        std::cout << "Input constructor" << std::endl;
    }
    ~Input() {
        std::cout << "Input destructor" << std::endl;
    }
    void getInput() {
        std::cout << "Getting input with id = " << id_ << std::endl;
    }
};

class GameEntity : public Renderer, public Input {
public:
    GameEntity(int id) : Component(id), Renderer(id), Input(id) {
        std::cout << "GameEntity constructor" << std::endl;
    }
    ~GameEntity() {
        std::cout << "GameEntity destructor" << std::endl;
    }
};

int main() {
    GameEntity entity(10);
    entity.render();
    entity.getInput();

    return 0;
}

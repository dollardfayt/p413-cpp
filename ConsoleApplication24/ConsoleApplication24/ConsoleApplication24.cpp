#include <iostream>

class ListItem {
public:
    int data;
    ListItem* next;

    ListItem(int data) : data(data), next(nullptr) {}
};

class List {
public:
    List() : head(nullptr) {}
    virtual ~List() { clear(); }

    virtual void insert(int data) {
        ListItem* newItem = new ListItem(data);
        newItem->next = head;
        head = newItem;
    }
    virtual int remove() {
        if (head == nullptr) {
            return -1;
        }
        int data = head->data;
        ListItem* temp = head;
        head = head->next;
        delete temp;
        return data;
    }

    void print() {
        ListItem* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

protected:
    ListItem* head;

private:
    void clear() {
        while (head != nullptr) {
            ListItem* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

class Stack : public List {
public:
    void insert(int data) override {
        List::insert(data);
    }

    int remove() override {
        return List::remove();
    }
};

class Queue : public List {
public:
    Queue() : tail(nullptr) {}

    void insert(int data) override {
        ListItem* newItem = new ListItem(data);
        if (tail == nullptr) {
            head = tail = newItem;
        }
        else {
            tail->next = newItem;
            tail = newItem;
        }
    }

    int remove() override {
        if (head == nullptr) {
            tail = nullptr;
            return -1;
        }
        int data = head->data;
        ListItem* temp = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete temp;
        return data;
    }

private:
    ListItem* tail;
};

int main() {
    std::cout << "Stack:" << std::endl;
    Stack stack;
    stack.insert(1);
    stack.insert(2);
    stack.insert(3);
    stack.print();
    std::cout << "Popped: " << stack.remove() << std::endl;
    stack.print();

    std::cout << "\nQueue:" << std::endl;
    Queue queue;
    queue.insert(1);
    queue.insert(2);
    queue.insert(3);
    queue.print();
    std::cout << "Dequeued: " << queue.remove() << std::endl;
    queue.print();

    return 0;
}

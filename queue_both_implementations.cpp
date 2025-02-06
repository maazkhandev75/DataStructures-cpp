/// NOTES FOR QUEUE DATA STRUCTURE :

//Linked List based queue

#include <iostream>
#include <stdexcept>

template <typename T>
class LinkedQueue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* front;
    Node* rear;

public:
    LinkedQueue() : front(nullptr), rear(nullptr) {}

    bool isEmpty() const {
        return front == nullptr;
    }

    void enqueue(const T& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue() {
        if (isEmpty()) {
            std::cerr << "Queue is empty. Cannot dequeue.\n";
            return;
        }
        Node* temp = front;
        front = front->next;
        delete temp;

        if (front == nullptr) {
            rear = nullptr;
        }
    }

    T frontValue() const {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty.");
        }
        return front->data;
    }

    // Copy Constructor
    LinkedQueue(const LinkedQueue& other) : front(nullptr), rear(nullptr) {
        Node* current = other.front;
        while (current) {
            enqueue(current->data);
            current = current->next;
        }
    }

    // Copy Assignment Operator
    LinkedQueue& operator=(const LinkedQueue& other) {
        if (this != &other) {
            while (!isEmpty()) {
                dequeue();
            }
            Node* current = other.front;
            while (current) {
                enqueue(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    ~LinkedQueue() {
        Node* current = front;
        while (current) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

int main() {
    std::cout << "Testing LinkedQueue...\n";

    LinkedQueue<int> linkedQueue;

    linkedQueue.enqueue(1);
    linkedQueue.enqueue(2);
    linkedQueue.enqueue(3);

    std::cout << "Front value after enqueueing 1, 2, 3: " << linkedQueue.frontValue() << std::endl;

    linkedQueue.dequeue();
    std::cout << "Front value after one dequeue: " << linkedQueue.frontValue() << std::endl;

    linkedQueue.enqueue(4);
    std::cout << "Front value after enqueueing 4: " << linkedQueue.frontValue() << std::endl;

    // Copy Constructor Test
    LinkedQueue<int> copiedQueue(linkedQueue);
    std::cout << "Front value of copied queue: " << copiedQueue.frontValue() << std::endl;

    // Assignment Operator Test
    LinkedQueue<int> assignedQueue;
    assignedQueue = linkedQueue;
    std::cout << "Front value of assigned queue: " << assignedQueue.frontValue() << std::endl;

    // Dequeue all elements to test empty state
    linkedQueue.dequeue();
    linkedQueue.dequeue();
    linkedQueue.dequeue();  // Now it should be empty

    std::cout << "Queue emptied. Is it empty? " << (linkedQueue.isEmpty() ? "Yes" : "No") << std::endl;

    // Trying to access front value on empty queue
    try {
        linkedQueue.frontValue();
    } catch (const std::out_of_range& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}

//-----------------------------------------------------------

//Array-Based Queue

#include <iostream>
#include <stdexcept>

template <typename T>
class ArrayQueue {
private:
    T* arr;
    int front;
    int rear;
    int capacity;

public:
    // Constructor
    ArrayQueue(int size) : front(-1), rear(-1), capacity(size) {
        arr = new T[capacity];
    }

    // Copy Constructor
    ArrayQueue(const ArrayQueue& other) 
        : front(other.front), rear(other.rear), capacity(other.capacity) {
        arr = new T[capacity];
        for (int i = 0; i < capacity; i++) {
            arr[i] = other.arr[i];
        }
    }

    // Copy Assignment Operator
    ArrayQueue& operator=(const ArrayQueue& other) {
        if (this != &other) {
            delete[] arr;  // Delete existing array
            
            front = other.front;
            rear = other.rear;
            capacity = other.capacity;
            arr = new T[capacity];

            for (int i = 0; i < capacity; i++) {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }

    bool isEmpty() const {
        return front == -1;
    }

    bool isFull() const {
        return (rear + 1) % capacity == front;
    }

    void enqueue(const T& value) {
        if (isFull()) {
            std::cerr << "Queue is full. Cannot enqueue.\n";
            return;
        }
        if (isEmpty()) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % capacity;
        }
        arr[rear] = value;
    }

    void dequeue() {
        if (isEmpty()) {
            std::cerr << "Queue is empty. Cannot dequeue.\n";
            return;
        }
        if (front == rear) {  // Last element
            front = rear = -1;
        } else {
            front = (front + 1) % capacity;
        }
    }

    T frontValue() const {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty.");
        }
        return arr[front];
    }

    // Destructor
    ~ArrayQueue() {
        delete[] arr;
    }
};

// Driver Code
int main() {
    ArrayQueue<int> arrayQueue(5);
    
    arrayQueue.enqueue(1);
    arrayQueue.enqueue(2);
    arrayQueue.enqueue(3);

    std::cout << "Front value: " << arrayQueue.frontValue() << std::endl;

    // Copy constructor test
    ArrayQueue<int> copiedQueue = arrayQueue;

    arrayQueue.dequeue();
    arrayQueue.enqueue(4);

    std::cout << "Front value after dequeue and enqueue: " << arrayQueue.frontValue() << std::endl;
    std::cout << "Copied queue front value (should be original front): " << copiedQueue.frontValue() << std::endl;

    return 0;
}

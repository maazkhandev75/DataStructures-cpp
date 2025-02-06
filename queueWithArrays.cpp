#include<iostream>
using namespace std;

template<class T>
class Queue {
private:
	int MaxSize; // max Queue size
	int front, rear;
	T* queueArray;
	int size; // curr no. of elements in the Queue
public:
	Queue(int s = 10) { //s is maxSize
		if (s <= 0)
			MaxSize = 10;
		else {
			MaxSize = s;
			queueArray = new T[MaxSize];
			size = 0;
			rear = -1; // points to the last element
			front = 0; // points to first element
		}
	}

	bool isFull() {
		return MaxSize == size;
	}
	bool isEmpty() {
		return size == 0;
	}
	bool add(T n) {
		if (!isFull()) {
			rear++;
			if (rear == MaxSize)
				rear = 0;
			queueArray[rear] = n;
			size++;
			return true;
		}
		else return false;
	}
	bool remove(T& n) {
		if (!isEmpty()) {
			n = queueArray[front];
			front++;
			if (front == MaxSize)
				front = 0;
			size--;
			return true;

		}
		else return false;
	}
	void print() {
		for (int i = 0; i < size; i++) {
			cout << queueArray[i]<<" ";
		}
		cout << endl;
	}

	~Queue() {
		delete[] queueArray;
	}
};

int main() 
{
	Queue<int> q(5);
	q.add(1);
	q.add(2);
	q.add(3);
	q.add(4);
	q.add(0);
	q.add(0);

	q.print();

	system("pause");
	return 0;
}

#include<iostream>
using namespace std;

template<class T>
class Queue{

private:
	class Node{
	public:
		T data;
		Node* next;

		Node(){
			next = nullptr;
		}
		Node(T d, Node* n){
			data = d;
			next = n;
		}
		Node(T d){
			data = d;
			next = nullptr;
		}
		Node(const Node& rhs) {
			data = rhs.data;
			next = rhs.next;
		}
		const Node& operator=(const Node& rhs) {
			if (this!=&rhs) {
				data = rhs.data;
				next = rhs.next;
			}
			return *this;
		}
	};

	Node* head;
	Node* tail;
	int count;


public:
	Queue(){
		head = tail = nullptr;
		count = 0;
	}
	Queue(const Queue& rhs) {
		head = rhs.head;
		tail = rhs.tail;
		count = rhs.count;
	}
	const Queue& operator=(const Queue& rhs) {
		if (this != &rhs) {
			head = rhs.head;
			tail = rhs.tail;
			count = rhs.count;
		}
		return *this;
	}

	void EnQue(T d){
		Node* newNode = new Node(d, nullptr);

		if (head == NULL){
			head = newNode;
			tail = newNode;
			count++;
		}
		else{
			
			newNode->next = tail->next;
			tail->next = newNode;
			tail = newNode;
			count++;

		}
	}



	void display(){


		if (head != NULL)
		{
		Node* current = head;

		while (current != NULL)
		{
		cout << current->data << " ";
		current = current->next;
		}
	   }
		else{
		cout << "the queue is empty!\n";
        }

	}


	void merge(const Queue& q1, const Queue& q2){

		Node* ptr1 = q1.head;
		Node* ptr2 = q2.head;

		int n1 = q1.count;
		int n2 = q2.count;
		int totalCount = n1 + n2;

		Queue q3;     //class ka andar jab obj banana tu template type nahi likhni wo obvious hogi jo                   use horhi hogi oper....
			
		if (ptr1 != NULL && ptr2 != NULL){

				for (int i = 0; i < n1; i++, ptr1 =ptr1->next){
					q3.EnQue(ptr1->data);
				}
				for (int i = 0; i < n2; i++, ptr2 = ptr2->next) {
					q3.EnQue(ptr2->data);
				}
				//all data is simply placed the third queue

				//now we will sort this third queue...(KIND OF BUBBLE SORT ALGO)
				
				for (Node* a = q3.head; a != nullptr; a = a->next) {
					for (Node* b = a->next; b != nullptr; b= b->next) {
						if (a->data > b->data) {
							int temp = a->data;
							a->data = b->data;
							b->data = temp;
						}
					}
				}

				//q3.display();   for checking ....
				//now making our linked list an exact copy of this q3...
				Node* t = q3.head;
				for (int i = 0; i < totalCount; i++, t = t->next) {
					EnQue(t->data);
				}
				
			}
		else{
			cout << "the queues are not valid !\n";
		}
	}

	
	~Queue(){
		if (head != nullptr){

			while (head){
				Node* h = head;
				head = h->next;
				delete h;
			}
		}
	}
};


int main()
{
	cout << "Queue 1: ";
	Queue<int>q1;
	q1.EnQue(1);
	q1.EnQue(6);
	q1.EnQue(4);
	q1.display();

	cout << endl;

	cout << "Queue 2: ";
	Queue<int>q2;
	q2.EnQue(4);
	q2.EnQue(8);
	q2.EnQue(2);
	q2.display();

	cout << endl;

	cout << "Merged Queue: ";
	Queue<int>q;
	q.merge(q1,q2);
	q.display();

	system("pause");
	return 0;
}
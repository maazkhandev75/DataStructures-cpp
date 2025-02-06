#include<iostream>	
using namespace std;


template<class T>
class List
{
private:
	class Node			//Node class is in private of List class
	{
	public:
		T data;
		Node* next;
		Node* prev;

		Node()
		{
			next = nullptr;
			prev = nullptr;
			//data cannot be initialized because its datatype is template....
		}
		Node(T d) {
			data = d;
			next = nullptr;
			prev = nullptr;
		}
		Node(T d, Node* n, Node* p)
		{
			data = d;
			next = n;
			prev = p;
		}
	};

	Node* head;
	Node* tail;
public:

	class Iterator			//iterator class is in public List class
	{
		Node* curr;
		friend class List;			//for accessing private members of class List
	public:
		Iterator(Node* n = nullptr) {
			curr = n;
		}
		Iterator(const Iterator& rhs) {   //copy constructor....
			curr = rhs.curr;
		}
		const Iterator& operator=(const Iterator& rhs) {
			if (this != &rhs) {
				curr = rhs.curr;
			}
			return *this;
		}
		Iterator& operator++() {    //pre-increment operator.
			curr = curr->next;
			return *this;
		}
		Iterator& operator--() {
			curr = curr->prev;
			return *this;
		}
		T& operator*() {
			return curr->data;
		}
		bool operator<(const Iterator& rhs) const {
			if (curr->data < rhs.curr->data) {
				return true;
			}
			else return false;
		}
		bool operator==(const Iterator& rhs) const {
			if (curr == rhs.curr) {
				return true;
			}
			else
				return false;
		}
		bool operator!=(const Iterator& rhs) const {
			if (curr != rhs.curr) {
				return true;
			}
			else
				return false;
		}

	};

	List()
	{
		//head and tail are dummy nodes always and the prev of head and the next of tail is always NULL....
		//we will always deal with the next of head and prev of the tail

		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->prev = head;
		head->prev = tail->next = nullptr;
	}
	List(const List& rhs) {     //copy constructor

		//cout << "copy-constructor called\n";
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->prev = head;
		head->prev = tail->next = nullptr;

		Node* curr = rhs.head->next;

		while (curr != rhs.tail) {
			PushBack(curr->data);
			curr = curr->next;
		}
	}

	const List& operator=(const List& rhs) {    //assignment operator.
		if (this != &rhs) {
			//cout << "=operator called\n";
			while (head->next != tail) {    //deleting the existing list to update it after with new ones
				Node* t = head->next;
				head->next = t->next;
				delete[] t;
			}
			//same code as copy constructor...
			head = new Node;
			tail = new Node;
			head->next = tail;
			tail->prev = head;
			head->prev = tail->next = nullptr;

			Node* curr = rhs.head->next;

			while (curr != rhs.tail) {
				PushBack(curr->data);
				curr = curr->next;
			}
		}
		return *this;
	}

	Iterator Begin() {
		Iterator itr(head->next);
		return itr;
	}
	Iterator End() {
		Iterator itr(tail);
		return itr;
	}
	void Print() {
		Iterator itr;
		for (itr = Begin(); itr != End(); ++itr) {
			cout << *(itr);
			cout << " ";
		}
	}
	void PushBack(const T& val) {			//simply pushback the value in the list ar end and update all pointers
		Node* newNode = new Node(val);
		newNode->prev = tail->prev;
		newNode->next = tail;
		tail->prev->next = newNode;
		tail->prev = newNode;
	}

	Iterator& Search(int accNo) {                  ///way_1  ( para:int and ==op with int )
		Iterator itr;
		for (itr = Begin(); itr != End(); ++itr) {
			if (*(itr) == accNo) {
				return itr;
			}
		}
		itr = 0;
		return itr;
	}


	Iterator Insert(Iterator it, T d) {
		Node* p = it.curr;
		Node* t = new Node;
		t->data = d;
		t->next = p;
		t->prev = p->prev;
		p->prev->next = t;
		p->prev = t;
		return it;     //pointer
	}
	void InsertAtStart(T d) {
		Iterator it(head->next);
		Insert(it, d);
	}
	void InsertAtEnd(T d) {
		Iterator it(tail);
		Insert(it, d);
	}

	Iterator& Remove(Iterator& it) {
		Node* p = it.curr;
		Iterator itr(p->next);
		p->prev->next = p->next;
		p->next->prev = p->prev;
		delete p;
		return itr;
	}
	void DeleteAtEnd() {
		Iterator itr(tail->prev);
		Remove(itr);
	}
	void DeleteAtStart() {
		Iterator itr(head->next);
		Remove(itr);
	}
	bool IsEmpty() const
	{
		if (head == NULL) {
			return true;
		}
		else {
			return false;
		}
	}

	void removeValue(T const V){
		Iterator itr;
		for (itr = Begin(); itr != End(); ++itr) {
			if (*(itr) == V) {
				itr = Remove(itr);
				if (itr == tail) {
					break;
				}
			}
		}
	}
	void removeDuplicate() {
		Iterator itr;
		for (itr = Begin(); itr != End(); ++itr) {
			
			
			Iterator it;          
			int count_found = 0;
			for (it = Begin(); it != End(); ++it) {

				if (*(itr) == *(it)) {
					count_found++;
					if (count_found > 1) {    //first time similarity donot delete but then onwards delete them
						it = Remove(it);
						if (it == tail) {
							break;
						}
					}
				}
			}
		}
	}
	void reverseList()
	{
		Iterator beg = Begin();
		Node* temp = 0;
		--beg;
		//swaping head and tail...
		temp = head;
		head = tail;
		tail = temp;
		while (beg != 0)
		{
			temp = beg.curr->prev;
			beg.curr->prev = beg.curr->next;
			beg.curr->next = temp;
			--beg;
		}
	}
	~List() {
		///destructor for doubly linked list

		Node* p1 = head;
		Node* p2 = tail;
		while (head->next != tail) {
				Node* t = head->next;
				if (t != NULL) {
					head->next = t->next;
				}
				delete[] t;
		}
		delete[] p1;
		delete[] p2;
	}
};
int main() {

	List<int> l1;
	l1.InsertAtEnd(5);
	l1.InsertAtEnd(1);
	l1.InsertAtEnd(1);
	l1.InsertAtEnd(4);
	l1.InsertAtEnd(5);
	l1.InsertAtEnd(2);
	l1.InsertAtEnd(3);
	l1.InsertAtEnd(4);
	l1.InsertAtEnd(5);
	l1.Print();
	l1.removeValue(5);
	l1.removeDuplicate();

	List<int>::Iterator it1;
	it1= l1.Begin();
	--it1;
	List<int>::Iterator it2;
	it2 = l1.End();
	--it2;
	cout << "\nprinting orignal list\n";
	l1.Print();

	///PRINTING REVERSE JUST....
	cout << "\njust printing reversely!\n";
	for (; it2 != it1; --it2) {  //just printing
		cout << it2.operator*() << " ";
	}
	///ACTUAL REVERSE MAKING FUNCTION...

	l1.reverseList();
	cout << "\n\nprinting reversed list using iterator\n\n";
	l1.Print();

	cout << "\n\n\n";
	system("pause");
	return 0;
}

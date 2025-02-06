#include<iostream>	
using namespace std;

template<class T>
class List {

	class Node {
	public:
		T data;
		Node* next;
		Node* prev;

		Node() {
			next = nullptr;
			prev = nullptr;
		}
		Node(T d) {
			data = d;
			next = nullptr;
			prev = nullptr;
		}
		Node(T d, Node* n, Node* p) {
			data = d;
			next = n;
			prev = p;
		}
		Node(const Node& rhs) {
			data = rhs.data;
			next = rhs.next;
			prev = rhs.prev;
		}
		const Node& operator=(const Node& rhs) {
			if (this != &rhs) {

			
			data = rhs.data;
			next = rhs.next;
			prev = rhs.prev;
			}
			return *this;
		}
};
	Node* head;
	Node* tail;
public:
	class Iterator {    ///has 9 total functions...
		Node* curr;
		friend class List;
	public:
		Iterator(Node* n = nullptr) {
			curr = n;
		}
		Iterator(const Iterator& rhs ) {
			curr = rhs.curr;
		}
		const Iterator& operator=(const Iterator& rhs) {
			if (this != &rhs) {
				curr = rhs.curr;
			}
			return *this;
		}
		Iterator& operator++(){
			curr = curr->next;
			return *this;
		}
		Iterator& operator--() {
			curr = curr->prev;
			return *this;
		}
		T& operator*(){
			return curr->data;
		}
		bool operator<(const Iterator& rhs) {
			if (curr->data < rhs.curr->data) {
				return true;
			}
			else return false;
		}
		bool operator==(const Iterator& rhs) const {
			if (curr == rhs.curr) {
				return true;
			}
			else return false;
		}
		bool operator!=(const Iterator& rhs) const {
			if (curr != rhs.curr) {
				return true;
			}
			else return false;
		}
		
	};  
	//total 15 / 16 func. of doubly linked list...
	List() {
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->prev = head;
		head->prev = tail->next = nullptr;
	}
	
	List(const List& rhs) {
		head = rhs.head;
		tail = rhs.tail;

		Node* temp = head->next;
		while (temp != tail) {
			insertAtEnd(temp->data);
			temp = temp->next;
		}
	}
	const List& operator=(const List& rhs) {

		if (this != &rhs) {
			while (head->next != tail) {
				deleteAtStart();
			}
			//or
			/*while (head->next != tail) {
				Node* t = head->next;
				head->next = t->next;
				delete t;
			}*/



			head = rhs.head;
			tail = rhs.tail;

			Node* temp = head->next;
			while (temp != tail) {
				insertAtEnd(temp->data);
				temp = temp->next;
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


	void print()
	{
		Iterator itr;
		for (itr = Begin(); itr != End(); ++itr) {
			cout << *(itr);
			cout << "\n-------------------\n";
		}
	}
	
	Iterator Search(int value)
	{ 
		Iterator itr;
		for (itr = Begin(); itr != End(); ++itr)
		{
			if (*(itr) == value)
			{
				return itr;
			}
		}
		itr = 0;
		return itr;
	}
	void pushBack(const T& value) {
		Node* newNode = new Node;
		newNode->data = value;
		newNode->prev = tail -> prev;
		newNode->next = tail;
		tail->prev->next = newNode;
		tail->prev = newNode;
	}

	Iterator insert(Iterator it, T d) {
		Node* p = it.curr;
		Node* t = new Node;
		t->data = d;
		t->next = p;
		t->prev = p->prev;
		p->prev->next = t;
		p->prev = t;
		return it;
	}
	void insertAtStart(T d) {
		Iterator itr(head->next);
		insert(itr, d);
	}
	void insertAtEnd(T d) {
		Iterator itr(tail);
		insert(itr, d);
	}
	
	Iterator remove(Iterator it) {
		Node* p = it.curr;
		Iterator itr(p->next);
		p->next->prev = p->prev;
		p->prev->next = p->next;
		delete p;
		return itr;
	}

	void deleteAtStart() {
		Iterator itr(head->next);
		remove(itr);
	}
	void deleteAtEnd() {
		Iterator itr(tail->prev);    //always remember tail->prev here...
		remove(itr);
	}


	void reverse() {
		Node* current = head;
		Node* temp = nullptr;

		while (current != nullptr) {
			temp = current->prev;
			current->prev = current->next;
			current->next = temp;

			current = current->prev;
		}

		if (temp != nullptr) {
			tail = head;
			head = temp->prev;
		}
	}

	~List() {

		while (head->next != tail) {
			deleteAtStart();
		}
		delete head;
		delete tail;
}


};

class Item {
private:
	int ID;
	string title;
	string author;
	string category;
	string age;

public: 
	Item(int _ID = 0, string _title = "", string _author = "", string _category = "", string _age = "") {
		ID = _ID;
		title = _title;
		author = _author;
		category = _category;
		age = _age;
	}
	bool operator==(int num) {
		if (ID == num) {
			return true;
		}
		else 
			return false;
	}

	friend ostream& operator<<(ostream& out, const Item& obj);
};

ostream& operator<<(ostream& out, const Item& obj) {
	out << "ID :" << obj.ID<<" ";
	out << "title :" << obj.title << " ";
	out << "author :" << obj.author << " ";
	out << "category :" << obj.category << " ";
	out << "age :" << obj.age << " ";

	return out;
}


class Library {
private:
	List<Item> items;
  //	friend class Iterator;
public:
	

	void addItem() {
		int ID = 0;
		string title;
		string author;
		string category;
		string age;
		cout << "enter ID : ";
		cin >> ID;
		cout << "enter title : ";
		cin >> title;
		cout << "enter author : ";
		cin >> author;
		cout << "enter category : ";
		cin >> category;
		cout << "enter age : ";
		cin >> age;


		Item i(ID, title, author,category,age);
		items.insertAtStart(i);
	}
	void removeItem() {
		int id;
		cout << "enter ID to be removed : ";
		cin >> id;
		List<Item>::Iterator itr;
		itr = items.Search(id);
		if (itr != 0) {
			items.remove(itr);
		}

	}
	void displayItems() {
		items.print();
	}
	
};
int main() 
{
	Library l;
	l.addItem();
	l.addItem();
	l.addItem();
	l.removeItem();
	l.displayItems();


	
	
	system("pause");
	return 0;
}
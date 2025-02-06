//using count for no of nodes
#include<iostream>
using namespace std;

template<class T>
class List
{
private:
	class Node
	{
	public:
		T data;
		Node* next;

		Node()
		{
			next = nullptr;
			//data cannot be initialized because its datatype is template....
		}
		Node(T d, Node* n)
		{
			data = d;
			next = n;
		}
	};
	int count;
	Node* tail;
public:
	List()
	{
		count = 0;
		tail = nullptr;
	}
	
	void insertAtStart(T const& d)
	{
		Node* t = new Node;
		t->data = d;
		count++;

		if (tail == NULL){   //empty list
			tail = t;
			t->next = t;
		}
		else{
			t->next = tail->next; 
			tail->next = t;
		}
	}
	void insertAtEnd(T const& d)
	{
		Node* t = new Node;
		t->data = d;
		count++;

		if (tail == NULL){
			tail = t;
			t->next = t;
		}
		else{
			t->next = tail->next;
			tail->next = t;
			tail = t;
		}
	}

	

	void print() const
	{
		if (tail == NULL){
			cout << "the circular linked list is empty!\n";
		}
		else{
			Node* t = tail->next;

			for (int i = 0; i < count; i++)
			{
				cout << t->data << " ";
				t = t->next;
			}
			cout << endl;
		}
	}
	
	
	bool addAfter(T const data, T const item) 
	{
		if (tail != NULL)
		{
			Node* t = tail->next;
			for (int i = 0; i < count; i++, t = t->next)
			{
				if (t->data == item)
				{
					Node* newNode = new Node(data, t->next);
					t->next = newNode;
					count++;
					return true;
				}
			}
			return false;
		}
		else {
			cout << "\nThe circular linked list is empty!\n";
			return false;
		}

	}
	
	bool deleteNode(T key)
	{
		if (tail != NULL)
		{
			Node* t = tail->next;
			
			bool flag = true;
			for (int i = 0; i < count; i++, t = t->next)
			{
				Node* after = t->next;

				if (t->data == key && flag){        //if first element to be deleted
					tail->next = t->next;
					delete t;
					count--;
					return true;
				}

				flag = false;

				if (after->data == key)
				{
					t->next = after->next;
					delete after;
					count--;
					return true;
				}
			}
			return false;
		}
		else {
			cout << "\nThe circular linked list is empty!\n";
			return false;
		}

	}


	

	~List()
	{
		Node* t = tail->next;
		while (t != tail) {
			Node* p = t;
			t = t->next;
			delete p;

			if (t == tail) {
				delete t;
				break;
			}
		}
	}

};
int main()
{
	List<int>l1;
	l1.insertAtStart(3);
	l1.insertAtStart(2);
	l1.insertAtStart(1);
	l1.insertAtEnd(5);
	l1.print();

	l1.addAfter(9,3);
	l1.print();

	l1.deleteNode(3);
	l1.print();


	system("pause");
	return 0;
}


//without using count for no of nodes 
#include<iostream>
using namespace std;

template<class T>
class List
{
private:
	class Node
	{
	public:
		T data;
		Node* next;

		Node()
		{
			next = nullptr;
			//data cannot be initialized because its datatype is template....
		}
		Node(T d, Node* n)
		{
			data = d;
			next = n;
		}
	};
	Node* tail;
public:
	List()
	{
		tail = nullptr;
	}

	void insertAtStart(T const& d)
	{
		Node* t = new Node;
		t->data = d;

		if (tail == NULL) {   //empty list
			tail = t;
			t->next = t;
		}
		else {
			t->next = tail->next;
			tail->next = t;
		}
	}
	void insertAtEnd(T const& d)
	{
		Node* t = new Node;
		t->data = d;

		if (tail == NULL) {
			tail = t;
			t->next = t;
		}
		else {
			t->next = tail->next;
			tail->next = t;
			tail = t;
		}
	}



	void print() const
	{
		if (tail == NULL) {
			cout << "the circular linked list is empty!\n";
		}
		else {
			Node* t = tail->next;

			while (t != tail) {
				cout << t->data<<" ";
				t = t->next;
				if (t == tail) {       //cond. can also be (t->next==tail->next)
					cout << t->data << " ";

				}
			}
			cout << endl;
		}
	}


	bool addAfter(T const data, T const item)
	{
		if (tail != NULL)
		{
			Node* t = tail->next;
			while (t != tail) {
				if (t->data == item)
				{
					Node* newNode = new Node(data, t->next);
					t->next = newNode;
					return true;
				}
				t = t->next;

				if (t == tail && t->data==item) {    //on last element

					Node* newNode = new Node(data, t->next);
					t->next = newNode;
					return true;
				}
			}
				
		return false;
		}
		else {
			cout << "\nThe circular linked list is empty!\n";
			return false;
		}

	}

	bool deleteNode(T key)
	{
		if (tail != NULL)
		{
			Node* t = tail->next;

			bool flag = true;
			while(t != tail)
			{
				Node* after = t->next;

				if (t->data == key && flag) {        //if first element to be deleted
					tail->next = t->next;
					delete t;
					return true;
				}

				flag = false;

				if (after->data == key)
				{
					t->next = after->next;
					delete after;
					return true;
				}
				t = t->next;
			}
			return false;
		}
		else {
			cout << "\nThe circular linked list is empty!\n";
			return false;
		}

	}




	~List()
	{
		Node* t = tail->next;
		while (t != tail) {
			Node* p = t;
			t = t->next;
			delete p;

			if (t == tail) {
				delete t;
				break;
			}
		}
	}

};
int main()
{
	List<int>l1;
	l1.insertAtStart(3);
	l1.insertAtStart(2);
	l1.insertAtStart(1);
	l1.insertAtEnd(5);
	l1.print();

	l1.addAfter(9, 3);
	l1.print();

	l1.deleteNode(3);
	l1.print();


	system("pause");
	return 0;
}
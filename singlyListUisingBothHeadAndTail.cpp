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
		Node(T d,Node* n)
		{
		data = d;
		next = n;
		}
		Node(T d) {
			data = d; 
			next = nullptr;
		}

	};

int count;
Node* head;   
Node* tail;
public: 
	List() 
	{
		head = nullptr;
		tail = nullptr;
		count = 0;
	}

	List(const List& rhs){     //copy constructor

		//cout << "copy-constructor called\n";
		count = rhs.count;
		head = nullptr;
		tail = nullptr;

		Node* srcPtr = rhs.head;

		while (srcPtr != NULL) {
			Node* newNode = new Node(srcPtr->data,srcPtr->next);

			if (head == NULL) {
				head = newNode;
				tail = newNode;
			}
			else {
				tail->next = newNode;
				tail = newNode;
			}

			srcPtr = srcPtr->next;
		}


	}

	const List& operator=(const List& rhs) {    //assignment operator.
				if (this != &rhs) {
					//cout << "=operator called\n";
					while (head != 0) {    //deleting the existing list to update it after with new ones
						Node* t = head;
						head = t->next;
						delete[] t;
					}
					//same code as copy constructor...
					count = rhs.count;
					head = nullptr;
					tail = nullptr;

					Node* srcPtr = rhs.head;

					while (srcPtr != NULL) {

						insertAtStart(srcPtr->data);
						/*Node* newNode = new Node(srcPtr->data, srcPtr->next);

						if (head == NULL) {
							head = newNode;
							tail = newNode;
						}
						else {
							tail->next = newNode;
							tail = newNode;
						}*/

						insertAtStart(srcPtr->data);
						srcPtr = srcPtr->next;
					}
			    }
				return *this;
	}

	void insertAtEnd(T const& element)
	{
		if (head == nullptr) {
			head = new Node(element, nullptr);
			count++;
			tail = head;
		}
		else {
			tail->next = new Node(element, nullptr);
			count++;
			tail = tail->next;
		}
	}

	void insertAtStart(T const& element) 
	{
		if (head == nullptr) {
			Node* temp = new Node(element, head);   //overloaded constr called simply...
			head = temp;
			tail = temp;
			count++;
		}
		else {
			Node* temp = new Node(element, head);
			head = temp;
			count++;
			//no need to change the tail 
		}
	}

	void print() const 
	{
		Node* h = head;
		while (h != NULL)
		{
			cout << h->data<<" ";
			h = h->next;
		}
		cout << endl;
	}
	bool search(T const& element) const 
	{
		if (head != NULL) {
			Node* h = head;
			for (int i = 0; i < count; i++, h = h->next)
			{
				if (h->data == element)
				{
					cout << element << " is found\n";
					return true;
				}
			}
			cout << element << " is not found!\n";
			return false;
		}
		else {
			cout << "\nthe list is empty!\n";
			return false;
		}
	}
	bool isEmpty() const
	{
		if (head == NULL) {
			return true;
		}
		else {
			return false;
		}
	}
	void insertBefore(T const v1, T const v2) const
	{
		if (head != NULL)
		{
			Node* h = head;
			for (int i = 0; i < count; i++, h = h->next)
			{
				if (h->data == v2)
				{
					Node* newNode = new Node(v1, h);
					//missing the previous pointer of doublely linked list so we have again iterate...
					Node* toBeSearch = h;
					Node* n = head;        //again iterating through loop
					for (int i = 0; i < count; i++, n = n->next) {
						if (n->next == toBeSearch) {
							n->next = newNode;
						}
					}
				}
			}

		}
		else {
			cout << "\nthe list is empty!\n";
		}

	}
	void deleteAll(T const value) {

		if (head != NULL) {
			Node* h = head;

			for (int i = 0; i < count; i++ , h = h->next)
			{
				if (h->data == value)
				{
					Node* toBeSearch = h;
					Node* n = head;    //again iterating through loop
					for (int i = 0; i < count; i++, n = n->next) {
						if (n->next == toBeSearch) {
							n->next = toBeSearch->next;
							break;
						}
					}
					delete h;
					count--;
				}
			}
		}
		else {
			cout << "\nthe list is empty!\n";
		}
	}

	void DeleteAtStart() {
		if (head != NULL) {
			Node* h = head;
			head = head->next;
			delete h;
			count--;
			cout << "\nelement deleted from start!\n";
		}
		else {
			cout << "\nthe list is empty!\n";
		}
	}

	~List() 
	{
		while (head != 0) {
			Node* t = head;
			head = t->next;
			delete t;
		}
		count = 0;
	}

};
int main() 
{


	







	List<int>l1;
	l1.insertAtStart(2);
	l1.insertAtStart(6);
	l1.insertAtStart(7);
	l1.insertAtEnd(9);
	l1.insertAtStart(7);
	l1.insertAtStart(8);
	l1.insertAtStart(9);
	l1.deleteAll(7);
	l1.print();
	l1.search(2);
	l1.search(9);
	l1.search(10);
	l1.DeleteAtStart();

	List<char>mycharlist;
	mycharlist.insertAtStart('a');
	mycharlist.insertAtStart('a');
	mycharlist.insertAtStart('m');
	mycharlist.insertAtEnd('z');
	mycharlist.insertAtStart(' ');
	mycharlist.insertAtEnd('.');
	mycharlist.print();

	List<char>duplicatelist(mycharlist);
	duplicatelist.print();

	//no need to explicitly called destructors in main if you haven't take memory dynamically in main func()
	//the static obj created in main as above automatically called its destructor after the execution of the main func.
	//you can check it my marking a breakpoint before system("pause") in main func


	system("pause");
	return 0;
}
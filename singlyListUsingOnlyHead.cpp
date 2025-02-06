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
	};

int count;
Node* head;   //aik hi head maintain krna hota hai...
public: 
	List() 
	{
		head = nullptr;
		count = 0;
	}
	void insertAtStart(T const& element) 
	{
		Node* temp = new Node(element,head);   //overloaded constr called simply...
		//or
		//temp->data = d;
		//temp->next = head;

		head = temp;
		count++;
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
		Node* h = head;
		for (int i = 0; i < count; i++, h = h->next) 
		{
			if (h->data == element) 
			{
				cout << element << " is found\n";
				return true;
			}
		}
		cout << element << " is not found\n";
		return false;
	}
	~List() 
	{
		while (head != 0) {
			Node* t = head;
			head = t->next;
			delete t;
		}
	}

};
int main() 
{
	List<int>l1;
	l1.insertAtStart(2);
	l1.insertAtStart(6);
	l1.insertAtStart(7);
	l1.print();
	l1.search(2);
	l1.search(9);
	l1.search(10);
	
	system("pause");
	return 0;
}
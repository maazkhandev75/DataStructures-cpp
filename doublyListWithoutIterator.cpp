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
		const Node& operator=(const Node& rhs) {
			if (this != &rhs) {
				data = rhs.data;
				next = rhs.next;
				prev = rhs.prev;
			}
			return *this;
		}

		Node(const Node& rhs) {
			data = rhs.data;
			next = rhs.next;
			prev = rhs.prev;
		}
	};

	Node* head;
	Node* tail;
public:
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



		///simply do this 

		/*head = rhs.head;
		tail = rhs.tail;
		Node* temp = head->next;
		while (temp != tail) {
			InsertAtEnd(temp->data);
			temp = temp->next;
		}*/
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


	void Print() {
		Node* t = head->next;
		while (t != tail) {
			cout << t->data << " ";
			t = t->next;
		}		
	}
	void PushBack(const T& val) {			//simply pushback the value in the list at end and update all pointers
		Node* newNode = new Node(val);
		newNode->prev = tail->prev;
		newNode->next = tail;
		tail->prev->next = newNode;
		tail->prev = newNode;
	}

	
	
	void InsertAtStart(T d) {
		if (head->next == NULL) {
			Node* newNode = new Node(d);
			newNode->prev = head;
			newNode->next = tail;
			head->next = newNode;
			tail->prev = newNode;
		}
		else {
			Node* newNode = new Node(d);
			head->next->prev = newNode;
			newNode->next = head->next;
			head->next = newNode;
			newNode->prev = head;
		}
	}
	void InsertAtEnd( T d) {
		if (head->next == tail) {    //empty list
			Node* newNode = new Node(d);
			newNode->prev = head;
			newNode->next = tail;
			head->next = newNode;
			tail->prev = newNode;
		}
		else {
			Node* newNode = new Node(d);
			newNode->prev = tail->prev;
			newNode->next = tail;
			tail->prev->next = newNode;
			tail->prev = newNode;
		}
	}

	
	void DeleteAtStart() {
		Node* t = head->next;
		head->next = t->next; //head->next->next
		t->next->prev = head;
		delete[] t;
		}
	void DeleteAtEnd() {
		Node* t = tail->prev;
		tail->prev = t->prev;   //tail->prev->prev
		t->prev->next = tail;
		delete[] t;
	}

	bool insertBefore(T const v1, T const v2) const
	{
		if (head->next != tail)   //not an empty list
		{
			Node* h = head->next;
			while (h->next != tail)
			{
				if (h->data == v2)
				{
					Node* newNode = new Node(v1);
					newNode->prev = h->prev;
					newNode->next = h;
					h->prev->next = newNode;
					h->prev = newNode;
				}
				h = h->next;
			}
		

		}
		else {
			cout << "\nthe list is empty!\n";
			return false;
		}

	}
	void Reverse() {
		Node* current = head;
		Node* temp = nullptr;

		while (current != nullptr) {
			// Swap the 'prev' and 'next' pointers of the current node
			temp = current->prev;
			current->prev = current->next;
			current->next = temp;

			// Move to the next node
			current = current->prev; // After the swap, the 'prev' is now the next node
		}

		// Update the head to point to the last node (which was the original first node)
		if (temp != nullptr) {
			tail = head;
			head = temp->prev; // 'temp' now points to the last node
		}
	}
	




	/*void Reverse() {
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

	}*/








   Node*& Remove(Node*& n) {
		Node* p = n->next;
		n->prev->next = p;
		p->prev = n->prev;
		delete[] n;
		return p;
	}



	void removeValue(T const V){

		if (head->next != tail) {
			Node* t1 = head->next;
			while (t1 != tail) {
				if (t1->data == V) {
					t1=Remove(t1);
				}
				t1 = t1->next;
				if (t1 == NULL) {
					break;
				}
			}
		}
		else {
			cout << "list is empty!\n";
		}
	}
	void removeDuplicates() {
		if (head->next != tail) {
			Node* t1 = head->next;
			while (t1!=tail) {

				Node* t2 = head->next;
				int count_found = 0;
				while (t2 != tail) {
					if (t1->data == t2->data) {
						count_found++;
						if (count_found > 1) {
							t2 = Remove(t2);
							
						}
					}
					t2 = t2->next;
					if (t2 == NULL) {
						break;
					}
					
				}
				t1 = t1->next;
				if (t1 == NULL) {
					break;
				}
			}

		}
		else {
			cout << "list is empty!\n";
		}
	}
	~List() 
	{
		///destructor for doubly linked list

		Node* p1 = head;
		Node* p2 = tail;

			while (head->next != tail) 
			{
			Node* t = head->next;
			if (t != NULL) 
			{
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
	l1.InsertAtStart(1);
	l1.InsertAtStart(2);
	l1.InsertAtStart(3);
	l1.InsertAtStart(4);
	l1.InsertAtStart(5);
	l1.Print();
	l1.DeleteAtStart();
	l1.DeleteAtEnd();
	l1.DeleteAtEnd();

	l1.insertBefore(7, 4);
	l1.insertBefore(1, 7);
	l1.insertBefore(7, 7);


	cout << "\n\n";
	l1.Print();
	cout << "\n\n";
	l1.removeValue(3);
	l1.Print();

	l1.removeDuplicates();
	cout << "\n\n";
	l1.Print();
	cout << "\n\n";


	l1.Reverse();   
	l1.Print();
	cout << "\n\n";
	

	
	system("pause");
	return 0;
}
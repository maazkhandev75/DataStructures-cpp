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
		Node(T d)
		{
			data = d;
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
			cout << h->data << " ";
			h = h->next;
		}
		cout << endl;
	}
	void deepCopy(List const& obj) {
		
		clear();   //to clear the initial list...

		//helper func for deep copy
		recursiveDeepCopy(obj.head , head);
	}

	void recursiveDeepCopy(Node* src, Node*& des) {
		if (src) {
			des = new Node(src->data);
			recursiveDeepCopy(src->next, des->next);
		}
	}

	bool isEqual(List const& obj) {
		if (recursiveEqualCheck(obj.head,this->head) == 1)    //writing this-> is optional
		{
			cout << "the linked lists are equal!\n";
			return true;
		}
		else {
			cout << "the linked lists are not equal!\n";
			return false;
		}
	}

	
	static bool recursiveEqualCheck(const Node * n1, const Node * n2) 
	{
			if (n1 == NULL && n2 == NULL) {
				return true;
			}
			if (n1 == NULL || n2 == NULL) {
				return false;
			}

			if (n1->data != n2->data) {
				return false;
			}
			 return recursiveEqualCheck(n1->next, n2->next);   //writing return is optional
	}
	

	void recursiveReverse() {
	    head = recursiveReverseHelper(head);
	}

	Node* recursiveReverseHelper(Node* current) {

		if (current == nullptr || current->next == nullptr) 
		{   //if empty or only one element in list
			//this also tranverse through the list and terminate recursion when it completes the complate traversal of the linked list...
			return current;
		}

		Node* reversePtr = recursiveReverseHelper(current->next);

		//when the stack unwind from top to bottom ,previous respective values (e.g : current ptr)appear one by one 
		// 
		// Reversing the current node's link
		current->next->next = current;
		current->next = nullptr;

		return reversePtr;
	}




	void clear() {
		while (head) {
			Node* temp = head;
			head = head->next;
			delete temp;
		}
	}
	~List()
	{
		clear();
	}

};


int StringCompare(const char* str1,const char*  str2) {
	if (*str1 == '\0' && *str2 == '\0') {    //if empty str's
		return 0;
	}

	//compare current characters 
	if (*str1 < *str2) {
		return -1;
	}
	else if (*str1 > *str2) {
		return 1;
	}

	//if characters are equal recursively compare next characters.
	return StringCompare(str1 + 1, str2 + 1);
}

void StrCpy(char* &dest,const char* src) {
	int i = 0;
	while (src[i] != '\0') {
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

}


int product(int a, int b) {
	if (b == 0)
		return 0;
	if (b < 0)     ///made b positive and out source to the main return 
	{
		return -1 * product(a, -b);    //it will pass to the lower and in the end it x with -1
	}
	return a + product(a, b - 1);
}


int main() 
{

	///............................................................
	char temp[50];
	int size = 0;

	cout << "enter 1st string : ";
	cin.getline(temp, 50);
	size = strlen(temp);
	char* string1 = new char[size + 1];
	StrCpy(string1, temp);


	cout << "enter 2nd string : ";
	cin.getline(temp, 50);
	size = strlen(temp);
	char* string2 = new char[size + 1];
	StrCpy(string2,temp);

	if (StringCompare(string1, string2) == 1) {
		cout << "string 1 is greater!\n";
	}
	if (StringCompare(string1, string2) == -1) {
		cout << "string 2 is greater\n";
	}
	if(StringCompare(string1, string2) == 0) {
		cout << "string 1 and string 2 are equal\n";
	}
	

	delete[] string1;
	delete[] string2;


	///............................................................

	int n1, n2;
	cout << "enter the 1st number : ";
	cin >> n1;

	cout << "enter the 2nd number : ";
	cin >> n2;
	cout << product(n1, n2) << endl;


	///............................................................

	List<int> l1;
	l1.insertAtStart(10);
	l1.insertAtStart(9);
	l1.insertAtStart(7);
	l1.insertAtStart(5);


	List<int> l2;
	l2.deepCopy(l1);
	l2.print();

	l2.isEqual(l1);
	cout << "\n\n";

	l1.recursiveReverse();
	l1.print();
	cout << "\n\n";

	l2.isEqual(l1);



	system("pause");
	return 0;
}

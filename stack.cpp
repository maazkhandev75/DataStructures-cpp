#include<iostream>
using namespace std;

template<class T>
class Stack
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
	int size;
	Node* top;
public:
	Stack(){
		size = 0;
		top = NULL;
		
	}
	int Size(){
		return size;
	}
	bool IsEmpty(){
		return (size == 0);
	}
	void Push(T const& e){
		if (top != NULL){
			Node* temp = new Node;
			temp->data = e;
			temp->next = top;
			top = temp;
			size++;
		}
		else{                       //stack is empty
			 top = new Node;
			 top->data = e;
			 top->next = NULL;
			 size++;
		}
	}

	void Pop(){
		if (top != NULL){
			Node* temp = top->next;
			delete top;
			top = temp;
			size--;
		}
		else{                                                 //stack is empty
			cout << "`ERROR` ( the stack is empty! )\n";
			}
	}
	bool Top(T& para) {
		if (top != NULL) {
			para = top->data;
			return true;
		}
		else {                    //stack is empty
			return false;
		}
	}

	~Stack() {
		int i = size;
		while (i != 0) {
			Pop();
			i--;
		}
	}

};


int main()
{
	
	Stack<int>s;
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);

	s.Pop();

	int t;
	s.Top(t);
	cout << "top element is : " << t<<endl;

	if (s.IsEmpty()) {
		cout << "Stack is empty\n";
	}
	else {
		cout << "the Stack is not empty!\n";
	}

	cout << "the size of Stack (no of elements in it ) :" << s.Size()<<endl;



	system("pause");
	return 0;
}
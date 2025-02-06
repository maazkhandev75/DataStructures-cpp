#include<iostream>
using namespace std;

///nested classes ka case mn parent class se phla likh dia aik bar template tu hojata kam
///<k,v> sirf obj declare krta waqt likhna hota pointers ka saath se nahi likha karta..
///class se bahir function likh raha hon tu bhi template likhna parta har func se phla ur < > wala kam bhi krna parta function se phla 

template<class k, class v>
class Tree
{
	//private  it should be like that but we change to learn the syntax in nested classes!
public:      //make it public just to get the idea of template in nested classes syntax....
	class TNode
	{
	public:
		///The Value is what you put into that container, and the Key is how you mark the container so that you can retrieve it later.

		k key;
		v value;
		TNode* leftChild;
		TNode* rightChild;


		TNode()
		{
			leftChild = rightChild = nullptr;
		}
		TNode(k n, v d, TNode* l, TNode* r)         // n for number(key) and d for data(value)
		{
			key = n;
			value = d;
			leftChild = l;
			rightChild = r;
		}
		TNode(k,v);  // params in prototype are not compulsory to write but dataTypes are compulsory to write btw!

		TNode(const TNode& obj) {
			key = obj.key;
			value = obj.value;
			leftChild = obj.leftChild;
			rightChild = obj.rightChild;
		}
	};

	TNode* root;
//public:
	Tree() {
		root = nullptr;
	}

	Tree(const Tree& t) {
		copyAll(t.root,root);   //src,des
	}
	void copyAll(TNode* c,TNode*& r) {
		if (c != nullptr) {
			r = new TNode(c->key, c->value, NULL, NULL);
			copyAll(c->leftChild, r->leftChild);
			copyAll(c->rightChild, r->rightChild);
		}
	}



   void insert(k const n, v const d);

	void insertRecursive(TNode*& r, k n, v d) {
		if (r == nullptr) {
			r = new TNode(n, d, nullptr, nullptr);
		}
		else {
			if (d < r->value) {
				insertRecursive(r->leftChild, n, d);
			}
			if (d > r->value) {
				insertRecursive(r->rightChild, n, d);
			}
			if (d == r->value) {
				r->value = d;
				r->key = n;
			}
		}

	}

	
	void inOrderPrintKeys()
	{
		printRecursive(root);
	}
	void printRecursive(TNode*& r) {
		if (r) {
			printRecursive(r->leftChild);
			cout << r->key<<"->"<<r->value<<"  ";
			printRecursive(r->rightChild);
		}
	}

	int lenght()  //this overall func is constand means that it cannot change value of anything
	{
		return lengthRecursive(root);
	}
	int lengthRecursive(TNode*& r) {
		if (r == nullptr) {
			return 0;
		}
		int leftLen = lengthRecursive(r->leftChild);
		int rightLen = lengthRecursive(r->rightChild);
		return 1 + leftLen + rightLen;
	}


	v* search(k key) {
		return searchRecursive(root, key);
	}
	v* searchRecursive(TNode*& curr, int key) {
		if (curr == nullptr) {
			return nullptr; // Key not found
		}

		if (key < curr->key) {
			return searchRecursive(curr->leftChild, key);
		}
		else if (key > curr->key) {
			return searchRecursive(curr->rightChild, key);
		}
		else {
			return &(curr->value);
		}
	}



	int findMax() {
		return findMaxRecursive(root);
	}
	int findMaxRecursive(TNode* r) {   //here if we write & (by ref pass copy not formed) our answer length becomes wrong!
		if (r == nullptr) {
			return 0;
		}

		while (r->rightChild != nullptr) {
			r = r->rightChild;
		}

		return r->value;
	}

	//(OR)
	/*int findMaxRecursive(TNode*& r) 
	{
		if (r->rightChild == NULL) {
			return r->value;
		}
		else {
			findMaxRecursive(r->rightChild);
		}
	}	

*/


	void deleteKey(int key) {
		  deleteKeyRecursive(root, key);
	}
	void deleteKeyRecursive(TNode*& r, int key)
	{
		if (r != nullptr) 
		{

			if (key == r->key)  //key founded
			{   //now update everything effectively while considering all the cases..
				if (r->leftChild == nullptr && r->rightChild == nullptr) {   //case_1
					delete r;
					r = nullptr;
				}
				else if (r->leftChild != nullptr && r->rightChild == nullptr) {   //case_2a
					TNode* temp = r->leftChild;
					delete r;
					r = temp;
				}
				else if (r->rightChild != nullptr && r->leftChild == nullptr) {    //case_2b
					TNode* temp = r->rightChild;
					delete r;
					r = temp;
				}
				else if (r->leftChild != nullptr && r->rightChild != nullptr) {
					v m = findMaxRecursive(r->leftChild);
					r->value = m;
					deleteKeyRecursive(r->leftChild, m);
				}

			}
			else if(key < r->key){
				return deleteKeyRecursive(r->leftChild, key);
			}
			else if (key > r->key) {
				return deleteKeyRecursive(r->rightChild, key);
			}

		}
	}



	void destroyTree(TNode*& r) {
		if (r != NULL) {
			destroyTree(r->leftChild);
			destroyTree(r->rightChild);
			delete r;
		}
	}
	~Tree() {
		destroyTree(root);
	}

};

//just for practicing the syntax to write it outside
template<typename k,typename v>
void Tree<k,v>::insert(k const n, v const d) 
{
	insertRecursive(root, n, d);
}

template<typename k, typename v>            //USING TEMPLATE IN NESTED CLASSES (make TNode class public to run it)
Tree<k,v>::TNode::TNode(k n, v d) {
	key = n;
	value = d;
	leftChild = NULL;
	rightChild = NULL;
}












int main()
{
	Tree<int,int> t1;
	t1.insert(3,3);
	t1.insert(0,0);
	t1.insert(2,2);
	t1.insert(1,1);
	t1.insert(4,4);

	t1.inOrderPrintKeys();
	cout << "\n\n---------------\n\n";

	Tree<int, int> t2;
	t2.insert(1,3);
	t2.insert(2,0);
	t2.insert(3,2);
	t2.insert(4,1);
	t2.insert(5,4);

	//we can here change func according to our need whether we want to print according to data or according to key..
	//by making change in the insert func...



	t1.inOrderPrintKeys();
	cout << "\n\n---------------\n\n";
	Tree<int, int> t3(t1);
	t3.inOrderPrintKeys();
	cout << "\n\n---------------\n\n";
	t3.deleteKey(20);
	t3.deleteKey(500);
	t3.deleteKey(1000);

	t3.inOrderPrintKeys();
	cout << "---------------\n";
	cout << endl << endl;
	cout << "T2 Length: " << t2.lenght() << endl;

	int* val = t3.search(1);

	if (val != nullptr)
	{
		cout << "1 found" << endl;
	}

	val = t3.search(123);
	if (val == nullptr)
	{
		cout << "123 not found" << endl;
	}


	system("pause");
	return 0;
}
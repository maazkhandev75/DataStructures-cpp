#include<iostream>
#include<conio.h>
using namespace std;
//heavier batata kh kon sa case hai inward ya outward.....



int max(int r, int l)    //global func to calculate max..//can also be made static func in the helper class...
{
	if (r > l)
		return r;
	else return l;
}

template<class T>
class AVL
{
private:
	class TNode
	{
	public:

		T data;
		TNode* left;
		TNode* right;
		int height;


		TNode()
		{
			left = right = nullptr;
			//height=0;
		}
		TNode(T d, TNode* l, TNode* r, int h = 0)
		{
			data = d;
			height = h;
			left = l;
			right = r;
		}
		TNode(T d,int h=0) {
			data = d;
			height=h;
			left = nullptr;
			right = nullptr;
		}

		TNode(const TNode& obj) {
			data = obj.data;
			height=obj.height;
			left = obj.left;
			right = obj.right;
		}
	};
	TNode* root;

public:
	AVL() {
		root = nullptr;
	}
	AVL(TNode* r) {
		root = r;
	}
	TNode* getRoot() {
		return root;
	}

	void copyAll(TNode* c, TNode*& r) //c->orignal and r->copy
	{
		if (c != nullptr) {
			r = new TNode(c->data, nullptr, nullptr);
			copyAll(c->left, r->left);
			copyAll(c->right, r->right);
		}
	}

	AVL(const AVL& other) {
		copyAll(other.root, root);
	}

   int geth(TNode* r){
       if(r)
           return r->height;
           return -1;     
   }



	void insert(T d) {
		insertRecursive(root, d);
	}

	void insertRecursive(TNode*& r,T d) {
		if (r == nullptr) 
		{
			r = new TNode(d, nullptr, nullptr,0);
		}
		else
		{
			if (d < r->data) 
			{
				insertRecursive(r->left,d);
				if(geth(r->left)-geth(r->right)==2 || geth(r->left) - geth(r->right) == -2)
				{
				    if(d < r->left->data)
				        rotateRight(r);
				        else
				        DRRight(r);
				    
				}
			}
			else if(d > r->data)
			{
				insertRecursive(r->right,d);
				if(geth(r->right)-geth(r->left)==2 || geth(r->right) - geth(r->left) == -2)
				{
				    if(d > r->right->data)
				        rotateLeft(r);
				        else
				        DRLeft(r);
				   }
				}
				r->height=1 + max(geth(r->left),geth(r->right));
			}   //else ended...
			
		}

	void rotateRight(TNode*& x) {
		TNode* y = x->left;
		x->left = y->right;
		y->right = x;
		x->height = 1 + max(geth(x->left), geth(x->right));
		y->height = 1 + max(geth(y->left), geth(y->right));
		x = y;
	}
	void rotateLeft(TNode*& x) {
		TNode* y = x->right;
		x->right = y->left;
		y->left = x;
		x->height = 1 + max(geth(x->left), geth(x->right));
		y->height = 1 + max(geth(y->left), geth(y->right));
		x = y;
	}
  
  void DRRight(TNode* x) {
	   rotateLeft(x->left);
	   rotateRight(x);
  }
  void DRLeft(TNode* x){
      rotateRight(x->right);
      rotateLeft(x);
  }
 
  int balanceFactor(TNode* l, TNode* r) {
	   return (geth(l) - geth(r));
  }

	void inOrderPrintKeys()
	{
		printRecursive(root);
	}
	void printRecursive(TNode* r) {
		if (r) {
			printRecursive(r->left);
			cout <<"DATA: "<< r->data << "  |  HEIGHT: " << r->height << "\n";
			printRecursive(r->right);
		}
	}
	
	TNode* search(int value) {
		return searchRecursive(root, value);
	}
	
	TNode* searchRecursive(TNode*& r, int value) {
		if (r == nullptr) {
			cout << value << " not founded in the tree\n\n";
			return nullptr; // Key not found
		}

		if (value < r->data) {
			 searchRecursive(r->left, value);
		}
		else if (value > r->data) {
			return searchRecursive(r->right, value);
		}
		else {
			cout << value<<" founded in the tree\n\n";
			return r;
		}
	}

	void destroyAll(TNode*& r) {
		if (r != nullptr) {
			destroyAll(r->left);
			destroyAll(r->right);
			delete r;
		}
	}
	~AVL() {
		destroyAll(root);
	}

};



int main()
{
   AVL<int> t;
	t.insert(5);
	t.insert(30);
	t.insert(60);
	t.insert(100);
	t.insert(300);
	t.insert(600);
	t.insert(10);
	t.insert(2);
	t.insert(1000);
	t.insert(80);
   t.inOrderPrintKeys();
	cout << endl << endl;
   
	while (1) {
		cout << "what do you want to search : ";
		int value;
		cin >> value;
		t.search(value);
		cout << endl;
		cout << "to search again press 1 otherwise press any other key \n ";
		char input = _getch();
		if (input == '1')
			continue;
		else break;
		
	}
	
	system("pause");
	return 0;
}
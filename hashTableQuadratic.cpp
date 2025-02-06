#include<iostream>
#include<vector>
#include<string>
using namespace std;

//our's numbering =   //0->empty 1->occupied 2->deleted numbering in our case is little bit different

template< class v>
class HashItem
{	public:
	HashItem(){
		status = 0;
	}
public:
	int key;
	v value;
	int status;
	void print()
	{
		cout << "key: " << key<<" | " << "value: " << value << endl;
	}

};

template <class v>
class HashMap
{
protected:
	vector<HashItem<v>> hashArray;
	int capacity;
	int currentElements;
public:
	HashMap(int s){
		hashArray = vector<HashItem<v>>(s);
		capacity = s;
		currentElements = 0;
	}
	HashMap(){
		capacity = 0;
		currentElements = 0;
	}
	int GetNextIndexUsingLinear(int index){
		if (index + 1 >= capacity){
			index = 0;
		}
		if (hashArray[index + 1].status == 0)
			return index + 1;
		else{
			GetNextIndexUsingLinear(index + 1);
		}
	}
	int GetNextIndexUsingQuad(int index){
		if (index*index + 1 >= capacity){
			index = 0;
		}
		if (hashArray[index*index + 1].status == 0)
			return index*index + 1;
		else{
			GetNextIndexUsingLinear(index*index + 1);
		}
	}
	void insertLinearly(int key,v val){  
		float loadFactor = float(currentElements) /float(capacity);
		if (loadFactor < 0.7){

		int index = key% capacity;
		if (hashArray[index].status == 0){
			hashArray[index].value = val;
			hashArray[index].status = 1;
			hashArray[index].key = key;
		}
		else{
			index=GetNextIndexUsingLinear(index);
			hashArray[index].value = val;
			hashArray[index].status = 1;
			hashArray[index].key = key;
		}
		currentElements++;
		}
		else{
			vector<HashItem<v>> PreviousArr = hashArray;
			hashArray.resize(0);
			hashArray.resize(capacity*2);

			currentElements = 0;
			capacity *= 2;
			for (int i = 0; i < PreviousArr.size(); i++){
				if (PreviousArr[i].status == 1){
					insertLinearly(PreviousArr[i].key, PreviousArr[i].value);
				}
			}
			insertLinearly(key, val);

		}
	}

	void insertQuad(int key, v val){
		float loadFactor = float(currentElements) / float(capacity);
		if (loadFactor < 0.7){

			int index = key % capacity;
			if (hashArray[index].status == 0){
				hashArray[index].value = val;
				hashArray[index].status = 1;
				hashArray[index].key = key;
			}
			else{
				index = GetNextIndexUsingQuad(index);
				hashArray[index].value = val;
				hashArray[index].status = 1;
				hashArray[index].key = key;
			}
			currentElements++;
		}
		else{
			vector<HashItem<v>> PreviousArr = hashArray;
			hashArray.resize(0);
			hashArray.resize(capacity * 2);

			currentElements = 0;
			capacity *= 2;
			for (int i = 0; i < PreviousArr.size(); i++){
				if (PreviousArr[i].status == 1){   //2
					insertQuad(PreviousArr[i].key, PreviousArr[i].value);
				}
			}
			insertQuad(key, val);

		}
	}

	void Print(){
		for (int i = 0; i < capacity;i++)
		{
			if (hashArray[i].status == 1)
				hashArray[i].print();
		}
	}

	int hash1(int key) {
		return key % capacity;
	}
	int hash2(int key) {
		// Using a simple secondary hash function for demonstration
		return 1 + (key % (capacity - 1));
	}
	void insertDoubleHash(int key, v val){
		float loadFactor = float(currentElements) / float(capacity);
		if (loadFactor < 0.7){

			int index = hash1(key);
			if (hashArray[index].status == 0){
				hashArray[index].value = val;
				hashArray[index].status = 1;
				hashArray[index].key = key;
			}
			else{
				int step = hash2(key);
				index = (hash1(key) + index * step) % capacity;
				hashArray[index].value = val;
				hashArray[index].status = 1;
				hashArray[index].key = key;
			}
			currentElements++;
		}
		else{
			vector<HashItem<v>> PreviousArr = hashArray;
			hashArray.resize(0);
			hashArray.resize(capacity * 2);

			currentElements = 0;
			capacity *= 2;
			for (int i = 0; i < PreviousArr.size(); i++){
				if (PreviousArr[i].status == 1)  //	1 means occupied...
				{
					insertDoubleHash(PreviousArr[i].key, PreviousArr[i].value);
				}
			}
			insertDoubleHash (key, val);

		}
	}

};

int main(){
	HashMap<int> m1(10);
	m1.insertLinearly(56, 5);
	m1.insertLinearly(36, 5);
	m1.insertLinearly(46, 5);
	m1.insertLinearly(52, 5);
	m1.insertLinearly(51, 5);
	m1.insertLinearly(69, 5);
	m1.insertLinearly(32, 5);
	m1.insertLinearly(15, 5);
	m1.insertLinearly(69, 5);
	m1.Print();

	cout << "\n\n\n\n\n";

	HashMap<int> m2(10);
	m2.insertQuad(56, 5);
	m2.insertQuad(36, 5);
	m2.insertQuad(46, 5);
	m2.insertQuad(52, 5);
	m2.insertQuad(51, 5);
	m2.insertQuad(69, 5);
	m2.insertQuad(32, 5);
	m2.insertQuad(15, 5);
	m2.insertQuad(69, 5);
	m2.Print();

	cout << "\n\n\n\n\n";


	
	HashMap<string> Students(10);
	Students.insertDoubleHash(101, "Alice");
	Students.insertDoubleHash(201, "Bob");
	Students.insertDoubleHash(301, "Charlie");
	Students.insertDoubleHash(401, "David");
	Students.Print();
	system("pause");

}
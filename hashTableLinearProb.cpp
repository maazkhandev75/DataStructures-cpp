#include<iostream>
using namespace std;

// pointer ka saath arrow lagta
// obj ka saath . lagta

template<class v>
class HashItem
{
public:
	int key;
	v value;
	int status;

	HashItem()
	{
		key = 0;
		status = 0;
	}

	void  print()
	{
		cout << "key: " << key << "  value: " << value << endl;
	}

};

template <class v>
class HashMap
{
protected:
	HashItem<v>* hashArray;
	int capacity;
	int currentElements;
public:
	HashMap() {
		capacity = 10;
		currentElements = 0;
		hashArray = new HashItem<v>[capacity];
		for (int i = 0; i < capacity; i++) {
			hashArray[i].status = 0;
		}
	}
	HashMap(int const capacity)
	{
		if (capacity < 1) {
			cout << " Error (size is less the !\n\n";
		}
		else
		{
			hashArray = new HashItem<v>[capacity];
			for (int i = 0; i < capacity; i++) {
				hashArray[i].status = 0;
			}

		}
	}

	int findFirstCandidateIndex(int k) {
		return k % capacity;
	}

	int getNextCandidateIndex(int key, int i) {
		return((key % capacity) + i) % capacity;
	}

	void doubleCapacity()
	{
		int oldCapacity = capacity;
		capacity *= 2;
		HashItem<v>* oldHashArray = hashArray;
		hashArray = new HashItem<v>[capacity];
		currentElements = 0;
		for (int i = 0; i < oldCapacity; i++) {
			if (oldHashArray[i].status == 2) {
				insert(oldHashArray[i].key, oldHashArray[i].value); //this of orignal hashArray
			}
		}
		delete[] oldHashArray;
	}

	void insert(int const key, v const value)
	{
		float loadFactor = currentElements / capacity;
		int index = findFirstCandidateIndex(key);
		if (loadFactor < 0.75 && hashArray[index].status != 2) {
			hashArray[index].value = value;
			hashArray[index].status = 2;
			hashArray[index].key = key;

		}
		else {
			if (hashArray[index].status == 2) {

				int i = 1;
				int newIndex = getNextCandidateIndex(key, i);

				while (hashArray[newIndex].status == 2)
				{
					i++;
					newIndex = getNextCandidateIndex(key, i);
				}
				hashArray[newIndex].value = value;
				hashArray[newIndex].status = 2;
				hashArray[newIndex].key = key;
				currentElements++;
			}
			if (loadFactor > 0.75) {
				doubleCapacity();
			}
		}

	}

	bool deleteKey(int const k) const
	{
		for (int i = 0; i < capacity; i++) {
			if (hashArray[i].key == k) {
				hashArray[i].status == 1;
				return true;
			}
		}
		return false; //key not found...
	}

	v* get(int const k) const
	{
		v* val = NULL;

		for (int i = 0; i < capacity; i++)
		{
			if (hashArray[i].key == k)
			{
				val = &hashArray[i].value;
			}
		}
		return val; //key not found...
	}

	void print() {
		for (int i = 0; i < capacity; i++) {
			if (hashArray[i].status == 2) {
				hashArray[i].print();
			}
		}
	}
	~HashMap() {
		delete[] hashArray;
	}
};


int main()
{
	HashMap<string> map;
	map.insert(89, "maaz");
	map.insert(89, "hassan");
	map.insert(18, "ali");
	map.insert(49, "ayaan");
	map.insert(58, "ahsan");
	map.insert(69, "baber");
	map.print();

	system("pause");
	return 0;
}
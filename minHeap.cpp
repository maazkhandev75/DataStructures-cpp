template<class k>
class MinHeap
{
	k* arr;
	int capacity;
	int count;
public:
	MinHeap(int size = 0)
	{
		if (size)
		{
			arr = new k[size];
			capacity = size;
		}
		else
		{
			arr = 0;
			capacity = 0;
		}
		count = -1;   //here we have set -1 currentCount initially instead of zero...
		// we will first inc it and then we will make an insertion in the heap
	}
	static void swap(k& h1, k& h2)
	{
		k temp = h1;
		h1 = h2;
		h2 = temp;
	}
	bool isEmpty()
	{
		if (count == -1)
			return true;
		return false;
	}
	int parent(int i)
	{
		if (i > 0)
			return ((i - 1) / 2);
		return -1;    //root has no parent....
	}
	int left(int i)
	{
		return((i * 2) + 1);
	}
	int right(int i)
	{
		return((i * 2) + 2);
	}
	void insert(k key)
	{
		count++;   //first incremented!
		if (capacity == 0)
		{
			capacity++;
			arr = new k[capacity];
		}
		else if (count == capacity)
		{
			int _capacity = capacity * 2;
			k* newArr = new k[_capacity];
			for (int i = 0; i < capacity; i++)
				newArr[i] = arr[i];
			capacity = _capacity;
			delete[]arr;
			arr = newArr;
		}
		arr[count] = key;
		int i = count;
		while (i > 0 && arr[i] < arr[parent(i)])
		{
			swap(arr[i], arr[parent(i)]);
			i = parent(i);
		}
	}

	void minHeapify(int index)
	{
		int smallest = index;
		int l = left(index);
		int r = right(index);

		if (l < count && arr[l] < arr[smallest]) {   //l < count means left child exists..
			smallest = l;
		}
		if (r < count && arr[r] < arr[smallest]) {
			smallest = r;
		}
		if (smallest != index) {   //if the value of smallest is changed from the orignal index swap smallest and the orignal index..
			swap(arr[index], arr[smallest]);
			minHeapify(smallest);
		}
	}

	k extractMin()
	{
		k val = 0;  // Variable to store the minimum value

		// Check if the heap is empty
		if (count < 0)
			return 0;
		else if (count == 0)
			val = arr[count--];  // If there is only one element, extract and decrement count (IT EXTRACTS THE CURRENT COUNT INDEX ELEMENT AND AFTER THAT DECREMENT THE COUNT)
		else
		{
			val = arr[0];        // Store the minimum value (at the root of the heap)
			arr[0] = arr[count--];  // Replace the root with the last element and decrement count
			minHeapify(0);       // Restore the heap property by heapifying from the root
		}
		return val;  // Return the extracted minimum value
	}

	void deleteMin()
	{
		if (isEmpty())
			throw runtime_error("\nHeap is empty\n");
		else {
			arr[0] = arr[count--];   //min will go outside of the array....
			minHeapify(0);
		}
	}

	void decreaseKey(k key, k val)
	{
		//If the loop condition were i < count,
		//the loop would iterate up to count - 1, excluding the last element.
		//because initially count were -1 and count 0 means one element added..

		int i = 0;
		for (i = 0; i <= count; i++)
		{
			if (arr[i] == key) {
				break;
			}
		}
		if (i > count)  //if the whole for loop executes and i's value will  incremented at last to falsify the condition...
		{
			std::cerr << "Element with key not found.\n";
			return;
		}
		arr[i] = val;
		while (i > 0 && arr[i] < arr[parent(i)])
		{
			swap(arr[i], arr[parent(i)]);
			i = parent(i);
		}
	}

	void deleteKey(k key)
	{
		if (isEmpty())
			throw runtime_error("\nHeap is empty\n");
		else {
			for (int i = 0; i <= count; i++)
			{
				if (arr[i] == key) {
					swap(arr[i], arr[count]);  //will also went outside of the array... //we can also do [count--]
					count--;
					minHeapify(0);
					break;
				}
			}
		}
	}

	~MinHeap()
	{
		if (arr)
			delete[] arr;
	}
};
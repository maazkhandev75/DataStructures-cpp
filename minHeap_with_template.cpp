#include <iostream>
#include <cassert>
using namespace std;

template <typename k, typename v>
struct HeapItem
{
   k key;
   v value;
};

template <typename k, typename v>
class MinHeap
{
private:
   HeapItem<k, v>* arr;
   int capacity;
   int totalItems;

public:
   MinHeap() : arr(nullptr), capacity(0), totalItems(0) {}

   MinHeap(int _capacity) : arr(new HeapItem<k, v>[_capacity]), capacity(_capacity), totalItems(0) {}

   void insert(k key, v value)
   {
       if (totalItems == capacity)
       {
           // Double the capacity of the heap array
           capacity *= 2;
           HeapItem<k, v>* newArr = new HeapItem<k, v>[capacity];
           for (int i = 0; i < totalItems; i++)
           {
               newArr[i] = arr[i];
           }
           delete[] arr;
           arr = newArr;
       }

       int currentIndex = totalItems;
       arr[currentIndex].key = key;
       arr[currentIndex].value = value;
       totalItems++;

       while (currentIndex > 0)
       {
           int parentIndex = (currentIndex - 1) / 2;
           if (arr[currentIndex].key < arr[parentIndex].key)
           {
               swap(arr[currentIndex], arr[parentIndex]);
               currentIndex = parentIndex;
           }
           else
           {
               break;
           }
       }
   }

   void decreaseKey(k key, v value)
   {
       for (int i = 0; i < totalItems; i++)
       {
           if (arr[i].key == key)
           {
               arr[i].value = value;
               break;
           }
       }
   }

   void deleteKey(k key)
   {
       for (int i = 0; i < totalItems; i++)
       {
           if (arr[i].key == key)
           {
               swap(arr[i], arr[totalItems - 1]);
               totalItems--;
               heapify(0);
               break;
           }
       }
   }

   void getMin(v& _value)
   {
       if (isEmpty())
       {
           throw runtime_error("Heap is empty");
       }
       _value = arr[0].value;
   }

   void print() const
   {
       for (int i = 0; i < totalItems; i++)
       {
           cout << "Key: " << arr[i].key << ", Value: " << arr[i].value << endl;
       }
   }

   void deleteMin()
   {
       if (isEmpty())
       {
           throw runtime_error("Heap is empty");
       }
       totalItems--;
       swap(arr[0], arr[totalItems]);
       heapify(0);
   }

   bool isEmpty() const
   {
       return totalItems == 0;
   }

   ~MinHeap()
   {
       delete[] arr;
   }

private:
   void heapify(int index)
   {
       int smallest = index;
       int left = 2 * index + 1;
       int right = 2 * index + 2;

       if (left < totalItems && arr[left].key < arr[smallest].key)
       {
           smallest = left;
       }

       if (right < totalItems && arr[right].key < arr[smallest].key)
       {
           smallest = right;
       }

       if (smallest != index)
       {
           swap(arr[index], arr[smallest]);
           heapify(smallest);
       }
   }
};

int main()
{
   MinHeap<int, int> heap(10);

   heap.insert(1,1);
   heap.insert(2, 2);
   heap.insert(3, 3);
   heap.insert(4, 4);
   heap.insert(6, 6);
   heap.insert(5, 5);
   heap.print();
   int minItem;
   heap.getMin(minItem);
   cout << "Minimum item: " << minItem << endl;

   heap.decreaseKey(5, 5);

   heap.deleteKey(1);

   int deletedItem;
   heap.deleteMin();
   heap.getMin(deletedItem);
   cout << "Deleted item: " << deletedItem << endl;
   heap.print();

   while (!heap.isEmpty())
   {
       heap.deleteMin();
   }

   heap.print();
   cout << "Is the heap empty? " << (heap.isEmpty() ? "Yes" : "No") << endl;

   return 0;
}
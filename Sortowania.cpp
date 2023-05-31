// ALGO2 IS1 212A LAB07
// Michał Sprysak
// sm49406@zut.edu.pl

#include <iostream>
#include <time.h>


using namespace std;
template <typename T>
class BH {

public:
	T* arr;
	int largest;
	unsigned int size = 0; //aktualny rozmiar
	BH(T* arr, int size)
	{
		this->arr = arr;
		this->size = size;
	}

	int parent(int id) {
		return (id - 1) / 2;
	}
	int leftChild(int id) {
		return 2 * id + 1;
	}
	int rightChild(int id) {
		return 2 * id + 2;
	}

	void maxHeapify(T* arr, int size, int id) {
		int leftC = leftChild(id);
		int rightC = rightChild(id);
		largest = id;

		if (leftC <= size && arr[leftC] > arr[largest])
			largest = leftC;
		else
			largest = id;

		if (rightC <= size && arr[rightC] > arr[largest])
			largest = rightC;

		if (largest != id) {
			T tmp = arr[largest];
			arr[largest ] = arr[id];
			arr[id] = tmp;
			maxHeapify(arr, size, largest);
		}
	}



	void sort(T* arr, int size)
	{
		for (int i = size / 2; i >= 0; i--)
			maxHeapify(arr, size - 1, i);
		for (int i = size - 1; i >= 1; i--)
		{
			T tmp = arr[i];
			arr[i] = arr[0];
			arr[0] = tmp;
			maxHeapify(arr, i - 1, 0);
		}
	}
};
template<typename T>
void CountingSort(T* arr, int size, int rangeOfSetValues) {
	int* counter = new int[rangeOfSetValues];
	int id = 0;
	for (int i = 0; i < rangeOfSetValues; i++)
		counter[i] = 0;

	for (int i = 0; i < size; i++)
	{
		counter[arr[i]]++;
	}

	for (int i = 0; i < rangeOfSetValues; i++)
		for (int j = 0; j < counter[i]; j++)
		{
			arr[id] = i;
			id++;
		}
	delete[] counter;
}

template<typename T>
void BucketSort(T* arr, int n) {
	int max = arr[0];
	int min = arr[0];
	int id = 0;

	for (int i = 0; i < n; i++)
	{
		if (min > arr[i])
			min = arr[i];
		if (max < arr[i])
			max = arr[i];
	}

	int counters = max - min + 1;

	int* bucket = new int[counters];
	for (int i = 0; i < counters; i++)
	{
		bucket[i] = 0;
	}

	for (int i = 0; i < n; i++)
		bucket[arr[i] - min]++;


	for (int i = 0; i < counters; i++)
	{
		for (int j = 0; j < bucket[i]; j++)
		{
			arr[id] = i + 1;
			id++;
		}
	}
	delete[] bucket;
}


int main()
{
	srand(0);
	int n = 1000000;
	int rangeOfSetValues = 10000;
	int* tab = new int[n];
	int* tabBucket = new int[n];
	int* tabCounting = new int[n];
	int* tabHeap = new int[n];
	BH<int>* bh = new BH<int>(tabHeap, n);

	for (int i = 0; i < n; i++)
		tab[i] = ((rand() << 15) + rand()) % rangeOfSetValues;


	memcpy(tabBucket, tab, n * sizeof(int));
	memcpy(tabCounting, tab, n * sizeof(int));
	memcpy(tabHeap, tab, n * sizeof(int));



	//Bucket Sort

	cout << "\tSortowanie przez kubelkowanie\n\t";

	//for (int i = 0; i < n; i++)
	//	cout << tab[i] << " ";

	clock_t t1 = clock();
	BucketSort(tabBucket, n);
	clock_t t2 = clock();
	double bucketSortTime = double(t2 - t1) / CLOCKS_PER_SEC;
	cout << "\n\n\t";
	//for (int i = 0; i < n; i++)
	//{
	//	cout << tabBucket[i] << " ";
	//}

	// Counting Sort
	cout << "\n\n\tSortowanie przez zliczanie" << "\n\t";
	//for (int i = 0; i < n; i++)
	//	cout << tab[i] << " ";

	clock_t t1c = clock();
	CountingSort(tabCounting, n, rangeOfSetValues);
	clock_t t2c = clock();
	double countingSortTime = double(t2c - t1c) / CLOCKS_PER_SEC;


	cout << "\n\n\t";
	/*for (int i = 0; i < n; i++)
		cout << tabCounting[i] << " ";*/


		//Binary Heap
	cout << "\n\n\tSortowanie przez kopcowanie\n\n\t";
	//for (int i = 0; i < n; i++)
	//    cout << tab[i] << " ";

	cout << "\n\n\t";
	clock_t t1h = clock();
	bh->sort(tabHeap, n);
	clock_t t2h = clock();
	double heapSortTime = double(t2h - t1h) / CLOCKS_PER_SEC;
	//for (int i = 0; i < n; i++)
	//	cout << tabHeap[i] << " ";

	//O(n+b) b= wybrala liczba kubelkow
	cout << "\t\n\nCzas Bucket Sort'a: " << bucketSortTime << " s";

	//O(n+m)
	cout << "\t\n\nCzas Counting Sort'a: " << countingSortTime << " s";

	// O(n log n)
	cout << "\t\n\nCzas Heap Sort'a: " << heapSortTime << " s";

}


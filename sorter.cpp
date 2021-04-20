#include "sorter.h"

#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <array>

using namespace std;

Sorter::Sorter()
{
	int n = 1000;
	this->shuff = vector<int>(n);
	this->loToHi = vector<int>(n);
	this->hiToLo = vector<int>(n);
	generateRandomArray(n);
	generateOrdered(n);
	generateReversed(n);
}

Sorter::Sorter(int n)
{
	this->shuff = vector<int>(n);
	this->loToHi = vector<int>(n);
	this->hiToLo = vector<int>(n);
	generateRandomArray(n);
	generateOrdered(n);
	generateReversed(n);
}

Sorter::Sorter(const Sorter &c)
{
	this->shuff = c.getShuffled();
	this->hiToLo = c.getReversed();
	this->loToHi = c.getOrdered();
}

void Sorter::swap(vector<int>& arr, int index1, int index2)
{
	int temp = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = temp;
}

const vector<int> Sorter::getShuffled() const { return this->shuff; }

const vector<int> Sorter::getOrdered() const { return this->loToHi; }

const vector<int> Sorter::getReversed() const { return this->hiToLo; }

void Sorter::selectionHelper(vector<int>& arr)
{
	int min_index;
	for (int i = 0; i < arr.size() - 1; i++) 
	{
		min_index = i;
		for (int j = i+1; j < arr.size(); j++) 
		{
			if (arr[j] < arr[min_index])
			{
				min_index = j;
			}
		}
		Sorter::swap(arr, min_index, i);
	}
}

void Sorter::selectionSort(const char c)
{
	switch (c)
	{
	case 's' :
		selectionHelper(this->shuff);
		break;

	case 'r' :
		selectionHelper(this->hiToLo);
		break;

	case 'o' :
		selectionHelper(this->loToHi);
		break;
	}
}

void Sorter::bubbleHelper(vector<int>& arr)
{
	for (int i = 0; i < arr.size() - 1 ; i++)
	{
		int swapped = 0;

		for (int j = 0; j < arr.size() - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{

				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				swapped = 1;
			}
		}

		if (swapped == 0) 
		{
			break;
		}
	}
}

void Sorter::bubbleSort(const char c)
{
	switch (c)
	{
	case 's':
		bubbleHelper(this->shuff);
		break;

	case 'r':
		bubbleHelper(this->hiToLo);
		break;

	case 'o':
		bubbleHelper(this->loToHi);
		break;
	}
}

void Sorter::merge(vector<int>& arr, int low, int mid, int high)
{
	int n1 = mid - low + 1;
	int n2 = high - mid;

	vector<int> Left(n1), Right(n2);

	for (int i = 0; i < n1; i++)
		Left[i] = arr[low + i];

	for (int i = 0; i < n2; i++)
		Right[i] = arr[mid + 1 + i];

	int index1 = 0, index2 = 0, c = low;

	while (index1 < n1 && index2 < n2)
	{
		if (Left[index1] <= Right[index2])
		{
			arr[c] = Left[index1];
			index1++;
		}
		else
		{
			arr[c] = Right[index2];
			index2++;
		}
		c++;
	}

	while (index1 < n1)
	{
		arr[c] = Left[index1];
		index1++;
		c++;
	}
	while (index2 < n2)
	{
		arr[c] = Right[index2];
		index2++;
		c++;
	}
}

void Sorter::mergeHelper(vector<int>& arr, int left, int right)
{
	if (left >= right) return;
	int mid = left + (right - left) / 2;
	mergeHelper(arr, left, mid);
	mergeHelper(arr, mid + 1, right);
	merge(arr, left, mid, right);
}

void Sorter::mergeSort(const char c)
{
	switch (c)
	{
	case 's':
		mergeHelper(this->shuff, 0, this->shuff.size() - 1);
		break;

	case 'r':
		mergeHelper(this->hiToLo, 0, this->hiToLo.size() - 1);
		break;

	case 'o':
		mergeHelper(this->loToHi, 0, this->loToHi.size() - 1);
		break;
	}
}

int Sorter::partition(vector<int>& arr, int low, int high)
{
	int pivot = arr[high];
	int small = low - 1;

	for (int i = low; i <= high - 1; i++)
	{
		if (arr[i] <= pivot)
		{
			small++;
			Sorter::swap(arr, small, i);
		}
	}
	Sorter::swap(arr, small + 1, high);
	return (small + 1);
}

void Sorter::quickHelper(vector<int>& arr, int low, int high)
{
	if (low < high)
	{
		int partition_index = partition(arr, low, high);

		quickHelper(arr, low, partition_index - 1);
		quickHelper(arr, partition_index + 1, high);
	}
}
void Sorter::quickSort(const char c)
{
	switch (c)
	{
	case 's':
		quickHelper(this->shuff, 0, this->shuff.size() - 1);
		break;

	case 'r':
		quickHelper(this->hiToLo, 0, this->hiToLo.size() - 1);
		break;

	case 'o':
		quickHelper(this->loToHi, 0, this->loToHi.size() - 1);
		break;
	}
}

void Sorter::generateRandomArray(int n)
{
	for (int i = 0; i < this->shuff.size(); i++)
		this->shuff[i] = i;

	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	shuffle(this->shuff.begin(), this->shuff.end(), default_random_engine(seed));
}

void Sorter::generateOrdered(int n)
{
	for (int i = 0; i < this->loToHi.size(); i++)
		this->loToHi[i] = i;
}

void Sorter::generateReversed(int n)
{
	int index = 0;
	for (int i = this->hiToLo.size() - 1; i >= 0; i--)
		this->hiToLo[index++] = i;
}


void Sorter::printHelper(vector<int>& arr)
{
	cout << "{ ";
	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << ' ';
	cout << " }\n";
}
void Sorter::printArr(const char c)
{
	switch (c)
	{
	case 's': printHelper(this->shuff); break;
	case 'o': printHelper(this->loToHi); break;
	case 'r': printHelper(this->hiToLo); break;
	}
}
#pragma once

#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Sorter
{
private:
	std::vector<int> shuff;
	std::vector<int> loToHi;
	std::vector<int> hiToLo;

	void swap(vector<int>& arr, int index1, int index2);

	void generateRandomArray(int n);
	void generateOrdered(int n);
	void generateReversed(int n);

	void printHelper(vector<int>& arr);

	void bubbleHelper(vector<int>& arr);
	void selectionHelper(vector<int>& arr);

	void merge(vector<int>& arr, int low, int mid, int high);
	void mergeHelper(vector<int>& arr, int left, int right);

	int partition(vector<int>& arr, int low, int high);
	void quickHelper(vector<int>& arr, int low, int high);

public:
	Sorter();
	Sorter(int n);
	Sorter(const Sorter &c);

	void bubbleSort(const char c);
	void selectionSort(const char c);
	void mergeSort(const char c);
	void quickSort(const char c);

	const std::vector<int> getShuffled() const ;
	const std::vector<int> getOrdered() const ;
	const std::vector<int> getReversed() const;
	void printArr(const char c);
};


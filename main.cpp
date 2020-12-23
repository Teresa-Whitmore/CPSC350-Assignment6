//============================================================================
// Name   : main.cpp
// Author : Teresa Whitmore
// Date   : December 19th, 2020
// Description : CPSC350 - Assignment 6 - Sorting
//============================================================================

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>

using namespace std;


//STANDARD 'SWAP' FUNCTION
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

//QUICKSORT FUNCTION

//Creates a "partition" to put the elements into "low" and "high" parts.
int partition (int array[], int low, int high)
{
	//The pivot variable becomes the value of the middle element.
    int pivot = array[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (array[j] < pivot)
        {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return (i + 1);
}

void QuickSort (int array[], int low, int high)
{
	int p;

    if (low < high)
    {
        p = partition(array, low, high);
        QuickSort(array, low, p - 1);
        QuickSort(array, p + 1, high);
    }
}

//MERGE SORT FUNCTION

void merge (int array[], int left, int m, int right)
{
    int n1 = m - left + 1;
    int n2 = right - m;
    int L[n1]; //Temporary Left array.
	int R[n2]; //Temporary Right array.

    for (int i = 0; i < n1; i++)
    {
        L[i] = array[left + i];
    }
    for (int j = 0; j < n2; j++)
    {
        R[j] = array[m + 1 + j];
    }

    //Three index variables used to track the elements during each recursion call.
    int i = 0; //First element.
    int j = 0; //Divides the list into two halves.
    int k = left; //Last element.

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            array[k] = L[i];
            i++;
        }

        else
        {
            array[k] = R[j];
            j++;
        }

        k++;
    }

    while (i < n1)
    {
        array[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        array[k] = R[j];
        j++;
        k++;
    }
}

void MergeSort (int array[],int left,int right)
{
	int m;

    if (left >= right)
    {
        return;
    }

    m = (left + right - 1) / 2;
    MergeSort (array, left, m); //Recursion.
    MergeSort (array, m + 1, right); //Recursion.
    merge (array, left, m, right); //Call merge function.
}

//SELECTION SORT FUNCTION

void SelectionSort (int array[], int s)
{
    int i;
    int j;
    int index;

    //Finds index of smallest unsorted element.
    for (i = 0; i < s - 1; i++)
    {
        index = i;

        for (j = i + 1; j < s; j++)
        {
			if (array[j] < array[index])
			{
				index = j;
			}
        }
        swap (&array[index], &array[i]); // Call to Swap function.
    }
}

//INSERTION SORT FUNCTION

void InsertionSort (int array[], int s)
{
    int i;
    int j;
    int k; //Temporary variable for swap.

    for (i = 1; i < s; i++)
    {
        k = array[i];
        j = i - 1;

        while (j >= 0 && array[j] > k)
        {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = k;
    }
}

//BUBBLE SORT FUNCTIONS

void BubbleSort(int array[], int s)
{
    int i; //First element to swap.
    int j; //Second element to swap.

    for (i = 0; i < s - 1; i++)
    {
		for (j = 0; j < s - i - 1; j++)
		{
			if (array[j] > array[j+1])
			{
				swap(&array[j], &array[j+1]); //Call to Swap function.
			}
		}
    }
}

int main()
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	string input;
	string line;
	string numSort;

	int size = 0;
	int s;

	//Prompts user for file name.

	cout << "Enter file name: ";
	getline (cin, input);

	ifstream inputFile(input); //Opens file.

    //Iterates through lines in file to determine size of array.

	while(getline(inputFile, line))
	{
		++size;
	}

    int array1[size];

    int i = 0;

    //Populates the array from file content.

    while (i < size && (inputFile) >> array1[i])
    {
    	i++;
    }

    //cout << "Array size is: " << size << endl;

    inputFile.close(); //Closes input file.

    int arrayQS[size];
    int arrayMS[size];
    int arraySS[size];
    int arrayIS[size];
    int arrayBS[size];

    //Array copies.

    for(int i=0; i<10; ++i)
    {
            arrayQS[i] = array1[i];
            arrayMS[i] = array1[i];
            arraySS[i] = array1[i];
            arrayIS[i] = array1[i];
            arrayBS[i] = array1[i];
    }

    //QUICKSORT

    start = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(start);

    cout << "\nBeginning Quick Sort at: " << std::ctime(&start_time) << endl;
    s = sizeof(arrayQS) / sizeof(arrayQS[0]);
	QuickSort(arrayQS, 0, s - 1);
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> duration = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	cout << "Finished Quick Sort at: " << std::ctime(&end_time) << " - Duration: " << duration.count() <<" milliseconds" << endl;

	//MERGE SORT

	start = std::chrono::system_clock::now();
	start_time = std::chrono::system_clock::to_time_t(start);

	cout << "\nBeginning Merge Sort at: " << std::ctime(&start_time) << endl;
	s = sizeof(arrayMS) / sizeof(arrayMS[0]);
	MergeSort(arrayMS, 0, s - 1);
	end = std::chrono::system_clock::now();
	duration = end - start;
	end_time = std::chrono::system_clock::to_time_t(end);
	cout << "Finished Merge Sort at: " << std::ctime(&end_time) << " - Duration: " << duration.count() <<" milliseconds" << endl;

	//SELECTION SORT

	start = std::chrono::system_clock::now();
	start_time = std::chrono::system_clock::to_time_t(start);

	cout << "\nBeginning Selection Sort at: " << std::ctime(&start_time) << endl;
	s = sizeof(arraySS) / sizeof(arraySS[0]);
	SelectionSort(arraySS, s);
	end = std::chrono::system_clock::now();
	duration = end - start;
	end_time = std::chrono::system_clock::to_time_t(end);
	cout << "Finished Selection Sort at: " << std::ctime(&end_time) << " - Duration: " << duration.count() <<" milliseconds" << endl;

	//INSERTION SORT

	start = std::chrono::system_clock::now();
	start_time = std::chrono::system_clock::to_time_t(start);

	cout << "\nBeginning Insertion Sort at: " << std::ctime(&start_time) << endl;
	s = sizeof(arrayIS) / sizeof(arrayIS[0]);
	InsertionSort(arrayIS, s);
	end = std::chrono::system_clock::now();
	duration = end - start;
	end_time = std::chrono::system_clock::to_time_t(end);
	cout << "Finished Insertion Sort at: " << std::ctime(&end_time) << " - Duration: " << duration.count() <<" milliseconds" << endl;

	//BUBBLE SORT

	start = std::chrono::system_clock::now();
	start_time = std::chrono::system_clock::to_time_t(start);

	cout << "\nBeginning Bubble Sort at: " << std::ctime(&start_time) << endl;
	s = sizeof(arrayBS) / sizeof(arrayBS[0]);
	BubbleSort(arrayBS, s);
	end = std::chrono::system_clock::now();
	duration = end - start;
	end_time = std::chrono::system_clock::to_time_t(end);
	cout << "Finished Bubble Sort at: " << std::ctime(&end_time) << " - Duration: " << duration.count() <<" milliseconds" << endl;

    return 0; //ends program
}


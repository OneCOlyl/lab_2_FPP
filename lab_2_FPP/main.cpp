#include <iostream>
#include <omp.h>
#include <random>

using namespace std;

void merge(int array[], int const left, int const mid, int const right)
{
    int sizeArrL = mid - left + 1;
    int sizeArrR = right - mid;

    int* lArray = new int[sizeArrL], * rArray = new int[sizeArrR];

#pragma omp parallel for
    for (int i = 0; i < sizeArrL; i++)
        lArray[i] = array[left + i];

#pragma omp parallel for
    for (int j = 0; j < sizeArrR; j++)
        rArray[j] = array[mid + 1 + j];

    int indexArrL = 0, indexArrR = 0; 
    int indexMerge = left; 

#pragma omp parallel while
    while (indexArrL < sizeArrL && indexArrR < sizeArrR) {
        if (lArray[indexArrL] <= rArray[indexArrR]) {
            array[indexMerge] = lArray[indexArrL];
            indexArrL++;
        }
        else {
            array[indexMerge] = rArray[indexArrR];
            indexArrR++;
        }
        indexMerge++;
    }

#pragma omp parallel while
    while (indexArrL < sizeArrL) {
        array[indexMerge] = lArray[indexArrL];
        indexArrL++;
        indexMerge++;
    }

#pragma omp parallel while
    while (indexArrR < sizeArrR) {
        array[indexMerge] = lArray[indexArrR];
        indexArrR++;
        indexMerge++;
    }
}

void mergeSort(int array[], int begin, int end)
{
    if (begin >= end)
        return;

    int mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}

void printArray(int A[], int size)
{
#pragma omp parallel for
    for (int i = 0; i < size; i++)
        cout << A[i] << " ";
}

int main()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(-100, 100);

    int sizeArr;
    cin >> sizeArr;
    int* arr = new int[sizeArr];
#pragma omp parallel for
    for (size_t i = 0; i < sizeArr; i++)
    {
        arr[i] = dist(gen);
    }

    cout << "Do \n";
    printArray(arr, sizeArr);

    mergeSort(arr, 0, sizeArr - 1);

    cout << "\nPosle \n";
    printArray(arr, sizeArr);
    return 0;
}

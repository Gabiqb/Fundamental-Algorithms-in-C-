#include <iostream>
#include "Profiler.h"

Profiler p("quicksort");
using namespace std;


#define STEP_SIZE 100
#define MAX_SIZE 1000
#define NR_TEST 5
/*
   Penru cazul in care un sir este random ales cele 2 metode de sortare adica quicksort si heapsort sunt diferite in sensul ca
   mai rapida este quicksort avand o complexitate de O(n*lgn) in timp ce heapSort este mai lenta dar complexitatea este tot O(n*lgn) insa se executa mai putine
   operatii la quicksort.
   
   Problema apare la cazul nefavorabil pentru quicksort atunci cand un sir este sortat crescator sau descrescator, caz in care complexitatea algoritmului quicksort este de O(n^2)
   iar cea a heapsort-ului ramane tot O(n*lgn)

   Ambele metode sunt utile insa depinde de elementele tabloului de intrare, daca avem certitudinea ca sunt random alese sau nesortate atunci putem folosi
   quicksort, altfel heapsort-ul pare a ramane inca alegerea cea mai buna.
    
     
 */
int nstp;
void heapify(int arr[], int n, int i)
{
    Operation opcomp = p.createOperation("heapify-comp", nstp);
    Operation opatr = p.createOperation("heapify-attr", nstp);

    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    opcomp.count();
    if (l < n && arr[l] > arr[largest])
        largest = l;

    opcomp.count();
    if (r < n && arr[r] > arr[largest])
        largest = r;

    //opcomp.count();
    if (largest != i) {
        opatr.count(3);
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void buildHeap(int arr[], int n)
{

    int startIdx = (n / 2) - 1;

    for (int i = startIdx; i >= 0; i--) {
        heapify(arr, n, i);
    }


}
void HeapSort(int arr[], int n)
{
    Operation opatr = p.createOperation("heapsort-atr", nstp);
    buildHeap(arr, n);
    for (int i = n - 1; i > 0; i--)
    {
        opatr.count(3);
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int partition(int a[], int low, int high)
{
    Operation opc = p.createOperation("qsort-comp", nstp);
    Operation opat = p.createOperation("qsort-atr", nstp);
    opat.count();
    int pivot = a[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {

        opc.count();
        if (a[j] < pivot)
        {
            i++;    // increment index of smaller element 
            opat.count(3);
            swap(a[i], a[j]);
        }
    }
    opat.count(3);
    swap(a[i + 1], a[high]);
    return (i + 1);
}

void quickSort(int a[], int low, int high)
{
    if (low < high)
    {

        int pi = partition(a, low, high);
        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}


void printArray(int a[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << a[i] << " ";
    cout << endl;
}


int quickselect(int a[], int l, int r, int k)
{
    if (k > 0 && k <= r - l + 1) {


        int index = partition(a, l, r);

        if (index - l == k - 1)
            return a[index];

        if (index - l > k - 1)
            return quickselect(a, l, index - 1, k);


        return quickselect(a, index + 1, r,
            k - index + l - 1);
    }


    return INT_MAX;
}

void demo()
{
    //int a[] = { 9,12, 3,4, 1, 17,15,0,24,33 };
    int a[] = { 10, 23, 12, 24, 21, 3, 4, 19, 26, 14 };
    int n = sizeof(a) / sizeof(a[0]);
    quickSort(a, 0, n - 1);
    cout << "Sorted array: \n";
    printArray(a, n);

}

void demo2()
{
    int a[] = { 5, 11,25,36, 3, 44, 16 }; ///al 3 lea cel mai mic : 11
    int n = sizeof(a) / sizeof(a[0]);
    int k = 3;
    cout << "K-th smallest element is " << quickselect(a, 0, n - 1, k);


}

void perf(int order)
{
    int a[MAX_SIZE];
    int a1[MAX_SIZE];

    for (int i = 0; i < 5; i++)
    {
        for (nstp = STEP_SIZE; nstp <= MAX_SIZE; nstp += STEP_SIZE)
        {
            FillRandomArray(a, nstp, 10, 50000, false, order);
             for (int j = 0; j < nstp; j++)
                 a1[j] = a[j];
            quickSort(a, 0, nstp - 1);
            
        HeapSort(a1, nstp);
        }
    }


    p.divideValues("qsort-comp", NR_TEST);
    p.divideValues("qsort-atr", NR_TEST);
    p.divideValues("heapsort-atr", NR_TEST);
    p.divideValues("heapify-attr", NR_TEST);
    p.divideValues("heapify-comp", NR_TEST);
    p.addSeries("heapify", "heapify-attr", "heapify-comp");
    p.addSeries("heapsort total", "heapify", "heapsort-atr");
    p.addSeries("qsort_complex", "qsort-comp", "qsort-atr");
    p.createGroup("compare sort ", "heapsort total", "qsort_complex");
    p.showReport();


}

int main()
{

    //demo();
    // demo2();
    perf(UNSORTED);
    perf(ASCENDING);
    perf(DESCENDING);
    return 0;


}
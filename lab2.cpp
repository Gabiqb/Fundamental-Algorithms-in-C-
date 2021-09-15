#include <iostream>
using namespace std;
#include "Profiler.h"

Profiler p("lab2");

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TEST 5
#define INFM -1*1e20
int ns;
/*



   Cele 2 metode de build heap sunt incadrate in ordinul de complexitate O(nlgn)
   Build heap folosind metoda heapify este cea mai aproape de calculul n * lgn si se observa de pe analiza grafica unde pentru 10 000 de elemente ale unui sir alese aleator, metoda de build heap cu heapify executa 47 000 operatii 
   adica aproximativ 10 000 * log(10 000).

   In acelasi timp, build heap folosind heap_increase si insert executa 67 000 de operatii, undeva mai mult decat n * lgn

   In concluzie, pentru construirea unui heap, metoda mai eficienta este cea folosind Heapify sau "bottom-up" strategy
   
 */
void heapify(int arr[], int n, int i)
{
    Operation opcomp = p.createOperation("heapify-comp", n);
    Operation opatr = p.createOperation("heapify-attr", n);
    
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

void HeapSort(int arr[], int n)
{
    
   for (int i = n - 1; i > 0; i--)
    {
        
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
void buildHeap(int arr[], int n)
{

    int startIdx = (n / 2) - 1;

    for (int i = startIdx; i >= 0; i--) {
        heapify(arr, n, i);
    }
    

}
void heap_increase_key(int a[], int i, int key)
{
    Operation opatr2 = p.createOperation("heapincrease-attr",ns);
    Operation opcomp2 = p.createOperation("heapincrease-comp",ns);
    opcomp2.count();
    if (key < a[i])
        return;
   
    opatr2.count();
    a[i] = key;
    opcomp2.count();
    while (i > 1 and (a[(i - 1) / 2] < a[i]))
    {
        opatr2.count(3);
        swap(a[(i - 1) / 2], a[i]);
        i = (i - 1) / 2;
    }
}

void max_heap_insert(int a[], int key,int &asize)
{
    
    
    asize = asize + 1;
    a[asize] = INFM;
    heap_increase_key(a, asize, key);
    
}



void buildheap2(int a[],int &asize,int alength)
{
   asize = 1;
        
    for (int i = 2; i <= alength; i++)
    {
        max_heap_insert(a, a[i],asize);
    }
}


void printHeap(int arr[], int n)
{
    cout << "Array representation of Heap is:\n";

    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}
void performance()
{
    int a[MAX_SIZE];
    int a1[MAX_SIZE];
     
    int asize = 0;
   // int i;
    for (ns = STEP_SIZE; ns <= MAX_SIZE; ns += STEP_SIZE)
    {

        FillRandomArray(a, ns,10,50000,false,UNSORTED);
        for (int j = 0; j < ns; j++)
        {
            a1[j] = a[j];
        }
        buildHeap(a,ns);
        buildheap2(a1, asize, ns);
       

    }
   
    p.addSeries("heapbot", "heapify-comp", "heapify-attr");
    p.addSeries("heaptop", "heapincrease-attr", "heapincrease-comp");
    p.createGroup("COMPARE", "heapbot", "heaptop");
    
 
    
    p.showReport();
}
void demo()
{
     int v[] = { 2, 11, 6, 5, 14, 9, 35,22, 17 };
     int n = sizeof(v) / sizeof(int);
     buildHeap(v, n);
     HeapSort(v, n);
     printHeap(v, n);

 }
void demo2()
{
    int a[] = { 2, 11, 6, 5, 14, 9, 35,22, 17 };
 
    int alength = sizeof(a)/sizeof(int);
    int asize=0;
     buildheap2(a, asize, alength);
   // HeapSort(a, alength);
    printHeap(a,alength);
}
int main()
{
    //demo();  ///bot up
    //demo2();  //top down
    performance();
    return 0;
    
}
/*
* Bubblesort:
*  /////////////////////////////////// /////////////////////////////////// /////////////////////////////////// ///////////////////////////////////
*   nefavorabil
    pentru un vector cu numere ordonate descrescator de 10 000 de componente se executa 	199 975 518 operatii provenite din
    49 995 000  comparatii n*(n-1)/2
    149 980 518 atribuiri  
    Adica O(n^2)

    favorabil:
    pentru un vector cu numere ordonate descrescator de 10 000 de componente se executa 	49 995 000 operatii provenite din
    49 995 000  comparatii
    0 atribuiri
    Adica O(n^2)

    medium case(random):
    pentru un vector cu numere ordonate descrescator de 10 000 de componente se executa 	125 589 297 operatii provenite din
    49 995 000 comparatii n*(n-1)/2
    75 594 297 atribuiri
    Adica O(n^2)
     /////////////////////////////////// /////////////////////////////////// /////////////////////////////////// ///////////////////////////////////

  Insertionsort:
   
*   nefavorabil:
    pentru un vector cu numere ordonate descrescator de 10 000 de componente se executa 	50 023 503 operatii provenite din
    9 999 comparatii
    50 013 504  atribuiri n^2/2
    Adica O(n^2)

    favorabil:
    pentru un vector cu numere ordonate descrescator de 10 000 de componente se executa 	29 997 operatii provenite din
    9 999  comparatii
    19 998 atribuiri
    Adica O(n^2)

    medium case(random):
    pentru un vector cu numere ordonate descrescator de 10 000 de componente se executa 	25 228 096 operatii provenite din
    9 999comparatii
    25 218 097 atribuiri
    Adica O(n^2)
     /////////////////////////////////// /////////////////////////////////// /////////////////////////////////// ///////////////////////////////////

   Selectionsort:
     
*   nefavorabil:
    pentru un vector cu numere ordonate descrescator de 10 000 de componente se executa 	124 992 780 operatii provenite din
    49 995 000  comparatii n*(n-1)/2
    74 997 780 atribuiri
    Adica O(n^2)

    favorabil:
    pentru un vector cu numere ordonate descrescator de 10 000 de componente se executa 	49 995 000 operatii provenite din
    49 995 000  comparatii
    0 atribuiri
    Adica O(n^2)

    medium case(random):
    pentru un vector cu numere ordonate descrescator de 10 000 de componente se executa 	106 067 820 operatii provenite din
    49 995 000 comparatii n*(n-1)/2
    56 072 820 atribuiri
    Adica O(n^2) 


    Cea mai eficienta: Insertion sort
*/

#include <stdio.h> 

#include "Profiler.h"

Profiler p("sortt");

 
#define MAX_SIZE 10000
#define STEP_SIZE 100

void bubbleSort(int a[], int n)
{
    Operation opcomp = p.createOperation("bubble-comp", n);
    Operation opatr = p.createOperation("bubble-attr", n);
   
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
        {
            opcomp.count();
            if (a[j] > a[j + 1])
            {
                opatr.count(3);
                int aux;
                aux = a[j];
                a[j] = a[j + 1];
                a[j + 1] = aux;
            }

        }
    
   
}

void insertionSort(int a[], int n)
{
    Operation opComp = p.createOperation("insertion-comp", n);
    Operation opatr = p.createOperation("insertion-attr", n);
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        opatr.count();
        key = a[i];
        j = i - 1;
        opComp.count();
        while (j >= 0 && a[j] > key)
        {
            opatr.count();
            a[j + 1] = a[j];
            j = j - 1;
        }
        opatr.count();
        a[j + 1] = key;
    }
}


void selectionSort(int a[], int n)
{
    Operation opComp = p.createOperation("selection-comp", n);
    Operation opatr = p.createOperation("selection-attr", n);
    int i, j, min;
    for (i = 0; i < n - 1; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
        {
            opComp.count();
            if (a[j] < a[min])
            {
                opatr.count(3);
                int aux = a[j];
                a[j] = a[min];
                a[min] = aux;
            }
            min = j;
        }
    }
}

void perf(int order)
{
    int a[MAX_SIZE];
    int a1[MAX_SIZE];
    int a2[MAX_SIZE];
    int n;
    for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
    {

        FillRandomArray(a, n,10,50000,false,order);
        for (int i = 0; i < n; i++)
        {
            a1[i] = a[i];
            a2[i] = a[i];
        }
        bubbleSort(a, n);
        insertionSort(a1, n);
        selectionSort(a2, n);

    }
     
    p.addSeries("bubble", "bubble-comp", "bubble-attr");
    p.addSeries("insertion", "insertion-comp", "insertion-attr");
    p.addSeries("selection", "selection-comp", "selection-attr");
    
    p.createGroup("total", "bubble", "insertion", "selection");
    p.createGroup("total atribuiri", "insertion-attr", "bubble-attr", "selection-attr");
    p.createGroup("total comparatii", "insertion-comp", "bubble-comp", "selection-comp");
    
}
    

/* Function to print an array */
void printArray(int a[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", a[i]);
    printf("\n");
}
void demo()
{
    int a[] = { 124,34,10,2,1,0 };
    int n = sizeof(a) / sizeof(a[0]);
    bubbleSort(a, n);
    printf("Sorted array: \n");
    printArray(a, n);
}
// Driver program to test above functions 
int main()
{
  
    //demo();
    p.reset("nefavorabil");
    perf(DESCENDING);
    p.reset("favorabil");
    perf(ASCENDING);
    p.reset("random medium");
    perf(UNSORTED);
    p.showReport();
    return 0;
}
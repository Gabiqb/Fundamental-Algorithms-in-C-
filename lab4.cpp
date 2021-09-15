#include <iostream>
#include "Profiler.h"
using namespace std;

Profiler p("merge");
int ns; //step size pentru test1
int ns2; // step size pentru test2

#define MAX_SIZE 1000
#define NR_TESTS 5
#define STEP_SIZE 100
#define KMAX 1000
int k1;
int ex2;
struct Node
{
	int data;
	Node* next;
		
};
void Insert(Node** head, int key)
{
	Node* new_node = new Node();
	new_node->data = key;
	new_node->next = NULL;
	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{		 
		Node* temp = *head;
		while (temp->next != NULL)
			temp = temp->next;

		temp->next = new_node;
	}
	 
}
void printList(Node* node)
{
	while (node != nullptr)
	{
		cout << node->data << " -> ";
		node = node->next;
	}
	cout << "null"<<endl;
}
void heapify(Node* arr[], int n, int i)
{
	Operation opcomp = p.createOperation("opkvariabil[10..500]", k1);
	Operation opatr = p.createOperation("opkvariabil[10..500]", k1);

	int minimest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	opcomp.count();
	if (l < n && arr[l]->data < arr[minimest]->data)
		minimest = l;

	opcomp.count();
	if (r < n && arr[r]->data < arr[minimest]->data)
		minimest = r;

	if (minimest != i) {
		opatr.count(3);
		swap(arr[i], arr[minimest]);
		heapify(arr, n, minimest);
	}
}

void heapify5(Node* arr[], int n, int i)
{
	Operation opcomp = p.createOperation("opk5", ns);
	Operation opatr = p.createOperation("opk5", ns);

	int minimest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	opcomp.count();
	if (l < n && arr[l]->data < arr[minimest]->data)
		minimest = l;

	opcomp.count();
	if (r < n && arr[r]->data < arr[minimest]->data)
		minimest = r;

	if (minimest != i) {
		opatr.count(3);
		swap(arr[i], arr[minimest]);
		heapify5(arr, n, minimest);
	}
}

void heapify10(Node* arr[], int n, int i)
{
	Operation opcomp = p.createOperation("opk10", ns);
	Operation opatr = p.createOperation("opk10", ns);

	int minimest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	opcomp.count();
	if (l < n && arr[l]->data < arr[minimest]->data)
		minimest = l;

	opcomp.count();
	if (r < n && arr[r]->data < arr[minimest]->data)
		minimest = r;

	if (minimest != i) {
		opatr.count(3);
		swap(arr[i], arr[minimest]);
		heapify10(arr, n, minimest);
	}
}

void heapify100(Node* arr[], int n, int i)
{
	Operation opcomp = p.createOperation("opk100", ns);
	Operation opatr = p.createOperation("opk100", ns);

	int minimest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	opcomp.count();
	if (l < n && arr[l]->data < arr[minimest]->data)
		minimest = l;

	opcomp.count();
	if (r < n && arr[r]->data < arr[minimest]->data)
		minimest = r;

	if (minimest != i) {
		opatr.count(3);
		swap(arr[i], arr[minimest]);
		heapify100(arr, n, minimest);
	}
}

// Functie folosind min_heap cu un Array de Node*
// Primeste un array de k liste sortate si returneaza lista mare cu toate elementele celor k liste interclasate
Node* mergeKLists(Node* heap[], int heap_size)
{
	Operation opatrk = p.createOperation("opkvariabil[10..500]", k1);
	

	heapify(heap, heap_size, 0);

	Node* head = nullptr, * last = nullptr;

	while (heap_size != 0)
	{
		 
		// adauga in lista mare
		if (head == nullptr)
		{
			//opatrk.count();
			head = last = heap[0];
		}
		else
		{
			//opatrk.count();
			last->next = heap[0];
			last = heap[0];
		}
		//ia 'urmatorul' nod din lista 'curenta' ( cea care are e radacina in min heap)
		
		if (heap[0]->next != NULL)
		{
			opatrk.count();
			heap[0] = heap[0]->next;
			heapify(heap, heap_size, 0);
		}
		else
		{
			opatrk.count();
			heap[0] = heap[heap_size - 1];
			heap_size--;
			 
			heapify(heap, heap_size, 0);
		}

	}
	// 'capul' listei returnat
	return head;
}

Node* mergeKLists5(Node* heap[],int heap_size)
{
	Operation opatr = p.createOperation("opk5", ns);
 
		
	heapify5(heap, heap_size, 0);
		
	Node* head = nullptr, * last = nullptr;
	 	

	while (heap_size != 0)
	{
		 
		// adauga in lista mare
		if (head == nullptr)
		{
			//opatr.count(2);
			head = last = heap[0];
		}
		else
		{
			//opatr.count();
			last->next = heap[0];
			last = heap[0];
		}
		//ia 'urmatorul' nod din lista 'curenta' ( cea care are e radacina in min heap)
	 
		if (heap[0]->next != NULL)
		{
			opatr.count();
			heap[0] = heap[0]->next;
			heapify5(heap, heap_size, 0);
		}
		else
		{
			opatr.count();
			heap[0] = heap[heap_size - 1];
			heap_size--;
			heapify5(heap, heap_size, 0);
		}

	}
	// 'capul' listei returnat
	return head;
}

Node* mergeKLists10(Node* heap[], int heap_size)
{
	Operation opatr = p.createOperation("opk10", ns);
 

	heapify10(heap, heap_size, 0);

	Node* head = nullptr, * last = nullptr;

	while (heap_size != 0)
	{
		 
		// adauga in lista mare
		if (head == nullptr)
		{
			//opatr.count(2);
			head = last = heap[0];
		}
		else
		{
			//opatr.count();
			last->next = heap[0];
			last = heap[0];
		}
		//ia 'urmatorul' nod din lista 'curenta' ( cea care are e radacina in min heap)
		 
		if (heap[0]->next != NULL)
		{
			opatr.count();
			heap[0] = heap[0]->next;
			heapify10(heap, heap_size, 0);
		}
		else
		{
			opatr.count();
			heap[0] = heap[heap_size - 1];
			heap_size--;
			heapify10(heap, heap_size, 0);
		}

	}
	// 'capul' listei returnat
	return head;
}

Node* mergeKLists100(Node* heap[], int heap_size)
{
	Operation opatr = p.createOperation("opk100", ns);
 

	heapify100(heap, heap_size, 0);

	Node* head = nullptr, * last = nullptr;


	while (heap_size != 0)
	{
		 

		// adauga in lista mare
		if (head == nullptr)
		{
			 
			head = last = heap[0];
		}
		else
		{
			//opatr.count();
			last->next = heap[0];
			last = heap[0];
		}
		//ia 'urmatorul' nod din lista 'curenta' ( cea care are e radacina in min heap)
	 
		if (heap[0]->next != NULL)
		{
			opatr.count();
			heap[0] = heap[0]->next;
			heapify100(heap, heap_size, 0);
		}
		else
		{
			opatr.count();
			heap[0] = heap[heap_size - 1];
			heap_size--;
			heapify100(heap, heap_size, 0);
		}

	}
	// 'capul' listei returnat
	return head;
}

void demo()
{
	int k = 3; // Number of linked lists

	// An array to store the head nodes of the linked lists
	Node* list[3] = { NULL };
	Node* heap[3] = { NULL };
	Insert(&list[0], 1);

	Insert(&list[0], 5);

	Insert(&list[0], 7);

	Insert(&list[1], 2);

	Insert(&list[1], 3);

	Insert(&list[1], 6);

	Insert(&list[1], 9);

	Insert(&list[2], 4);

	Insert(&list[2], 8);

	Insert(&list[2], 10);

	for (int i = 0; i < 3; i++)
	{
		heap[i] = new Node;
		heap[i] = list[i];
	}
	// Merge all lists into one
	Node* head = mergeKLists(heap, 3);
	printList(head);

}
 
void test()
{
	Node* heap[KMAX] = { NULL };
	Node* list = NULL;
	Node* head1 = NULL;
	Node* head2 = NULL;
	Node* head3 = NULL;
	int a[MAX_SIZE];
	for (int i = 0; i < 5; i++)
	{
		for (ns = STEP_SIZE; ns <= MAX_SIZE; ns += STEP_SIZE)
		{

			for (int t = 0; t < 5; t++)
			{

				list = NULL;
				FillRandomArray(a, ns, 10, 10000, false, ASCENDING);
				Insert(&list, a[0]);
				heap[t] = new Node;
				heap[t] = list;
				for (int j = 1; j < ns; j++)
					Insert(&list, a[j]);
			}


			head1 = mergeKLists5(heap, 5);


		}

	}
	for (int i = 0; i < 5; i++)
	{
		for (ns = STEP_SIZE; ns <= MAX_SIZE; ns += STEP_SIZE)
		{

			for (int t = 0; t < 10; t++)
			{

				list = NULL;
				FillRandomArray(a, ns, 10, 10000, false, ASCENDING);
				Insert(&list, a[0]);
				heap[t] = new Node;
				heap[t] = list;
				for (int j = 1; j < ns; j++)
					Insert(&list, a[j]);
			}


			head2 = mergeKLists10(heap, 10);


		}

	}
	for (int i = 0; i < 5; i++)
	{
		for (ns = STEP_SIZE; ns <= MAX_SIZE; ns += STEP_SIZE)
		{

			for (int t = 0; t < 100; t++)
			{

				list = NULL;
				FillRandomArray(a, ns, 10, 10000, false, ASCENDING);
				Insert(&list, a[0]);
				heap[t] = new Node;
				heap[t] = list;
				for (int j = 1; j < ns; j++)
					Insert(&list, a[j]);
			}


			head3 = mergeKLists100(heap, 100);

		}

	}
	p.divideValues("opk5", NR_TESTS);
	p.divideValues("opk10", NR_TESTS);
	p.divideValues("opk100", NR_TESTS);
	p.createGroup("3 valori pentru k si n variabil", "opk5", "opk10", "opk100");

	 
}
 
void test2()
{
	Node* heap[KMAX] = { NULL };
	Node* list = NULL;
	Node* head;
	
	int a[MAX_SIZE];
		
		
		for (int i = 0; i < 5; i++)
		{
			k1 = 10;
			ns2 = 10000;
			ex2 = ns2 / k1;  ///nr de elemente pentru fiecare lista
			while (ex2 >= 20) /// cand ajunge 20 inseamna ca k=500
			{
				for (int t = 0; t < k1; t++)  ///se genereaza cele k liste
				{

					list = NULL;
					FillRandomArray(a, ex2, 10, 10000, false, ASCENDING);
					Insert(&list, a[0]);
					heap[t] = new Node;
					heap[t] = list;
					for (int j = 1; j < ex2; j++)
						Insert(&list, a[j]);
				}

				head = mergeKLists(heap, k1); ///merge k pentru k1

				k1 = k1 + 10;
				ex2 = ns2 / k1;

			}
		}
		p.divideValues("opkvariabil[10..500]", NR_TESTS);
 		
	
}
int main()
{
	//demo();
	p.reset("k variaza");
	test();
	p.reset("k variabil intre 10 si 500");
	test2();
	
	p.showReport();


	return 0;
}
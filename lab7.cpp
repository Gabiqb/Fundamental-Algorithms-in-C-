#include <iostream>
using namespace std;
#include "Profiler.h"
Profiler p("os");
#define STEP_SIZE 100
#define MAX_SIZE 10000
int ns;
//bool ok=false;
// Data structure to store a Binary Search Tree node
struct Node {
	int data;
	int size = 0;
	Node* left, * right;
};
Node* minValueNode(Node* node)
{
	Node* current = node;

	/* loop down to find the leftmost leaf */
	while (current && current->left != NULL)
		current = current->left;

	return current;
}

Node* newNode(int key)
{
	Operation opatr = p.createOperation("createtree", ns);
	Node* node = new Node;
	opatr.count();
	node->data = key;
	node->left = node->right = nullptr;

	return node;
}

Node* OS_DELETE(Node* root, int i, bool& ok)
{
	Operation opAttr = p.createOperation("osdelete", ns);

	if (root == NULL)
		return root;


	if (i < root->data)
	{
		opAttr.count();
		root->left = OS_DELETE(root->left, i, ok);
		if (ok == true)
			root->size--;
	}
	else if (i > root->data)
	{
		opAttr.count();
		root->right = OS_DELETE(root->right, i, ok);
		if (ok == true)
			root->size--;
	}

	else {
		ok = true;
		root->size--;

		if (root->left == NULL) {
			Node* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			Node* temp = root->left;
			free(root);
			return temp;
		}
		
		Node* temp = minValueNode(root->right);

		opAttr.count();
		root->data = temp->data;
	
		root->right = OS_DELETE(root->right, temp->data, ok);
	}
	return root;
}

Node* OS_select(Node* root, int poz)
{
	Operation opatr = p.createOperation("osselect", ns);
	int rang;
	
	if (root == NULL)  return NULL; 
	if (root->left != NULL)
		rang = root->left->size + 1;
	else
		rang = 1;
	
	if (poz < rang) {
		opatr.count();
		return OS_select(root->left, poz);
		 
    }
	else if (poz > rang)
	{
		opatr.count();
		return OS_select(root->right, poz - rang);
	}
	else
	{
		return root;
	}

}

void createtree(int keys[], int low, int high, Node*& root)
{
	if (low > high)
	{
		return;
	}

	int mid = (low + high) / 2;

	root= newNode(keys[mid]);
	root->size = 1;

	createtree(keys, low, mid - 1, root->left);
	createtree(keys, mid + 1, high, root->right);
	
	if (root->left != NULL)
	{
		root->size = root->size + root->left->size;
	}
	if (root->right != NULL)
	{
		root->size = root->size + root->right->size;
	}
}

Node* convert(int keys[], int n)
{
	Node* root = nullptr;
	createtree(keys, 0, n - 1, root);
	return root;
}

void prettyprint(Node* root, int space)
{
	if (root == NULL)
		return;
	space += 10;
	prettyprint(root->right, space);

	cout << endl;
	for (int i = 10; i < space; i++)
		cout << " ";
	cout << "| " << root->data << " |";
	prettyprint(root->left, space);
}

void inorder(Node* root)
{
	if (root == nullptr)
		return;

	inorder(root->left);
	cout << root->data << " ";
	inorder(root->right);
}

void demo()
{
	int keys[] = { 1, 2, 3, 4, 5, 6, 7,8,9,10};
	int n = sizeof(keys) / sizeof(keys[0]);

	Node* root = convert(keys, n);
    Node* k = OS_select(root, 10);

	cout << k->data << "\n";

	inorder(root);

	cout << endl;
	bool ok = false;

	root = OS_DELETE(root, 5, ok);
	inorder(root);
	cout << endl;
	cout << "Pretty print la arbore \n";
	prettyprint(root, 15);
	cout << "\n";

}
void test()
{
	int a[MAX_SIZE];
	Node* root = nullptr;
	for(int t=0;t<5;t++)
		for (ns = STEP_SIZE; ns <= MAX_SIZE; ns += STEP_SIZE)
		{
			for (int j = 0; j < ns; j++)
			 	a[j] = j + 1;
			createtree(a, 0, ns - 1, root);
			int pozz = ns;
			for (int j = 0; j < ns; j++)
		{
				Node* k = nullptr;
				int x = (int)rand() % pozz;
				pozz--;
				k=OS_select(root, x);
			 
				bool ok = false;
				k=OS_DELETE(root, a[x], ok);
		}
		 
		 
		}
	p.divideValues("createtree", 5);
	p.divideValues("osdelete", 5);
	p.divideValues("osselect", 5);
	p.createGroup("total teste", "createtree", "osdelete", "osselect");
	p.showReport();
}
int main()
{
	//demo();
	test();
	return 0;
}
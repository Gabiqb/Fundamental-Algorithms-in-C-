#include <iostream>
#include <cstdlib>
 
using namespace std;

#define VMAX 100

typedef struct Node{
	int key;
	int size = 0;
	Node* parent;
	Node* v[VMAX] = { NULL };
}Node;

typedef struct Ntree {
	int key;
	struct Ntree* left, * right;
}Ntree;

Ntree* newNode(int data)
{
	Ntree* temp = new Ntree;

	temp->key = data;
	temp->left = NULL;
	temp->right = NULL;

	return temp;
}


void insert(Ntree** root, int key)
{

	Ntree* newnode = newNode(key);

	Ntree* x = *root;

	Ntree* y = NULL;

	while (x != NULL) 
	{
		y = x;
		if (key < x->key)
			x = x->left;
		else
			x = x->right;
	}


	if (y == NULL)
		*root= newnode;

	else if (key < y->key)
		y->left = newnode;

	else
		y->right = newnode;

	
}

void Inorder(Ntree* root)
{
	if (root == NULL)
		return;
	else 
	{
		Inorder(root->left);
		cout << root->key << " ";
		Inorder(root->right);
	}
}
void insertbinaryfrom_multi(Node* root,Ntree** btree,int niv, int poz2, int poz)
{
	if (root == NULL) return;

	insert(btree, root->key);

	if (root->v[0])
	{
		insertbinaryfrom_multi(root->v[poz2++], btree,++niv, 0, 0);
		if (root->parent == NULL) return;
		root = root->parent->v[++poz];
		insertbinaryfrom_multi(root,btree, --niv, 0, poz);
	}
	else
	{
		root = root->parent->v[++poz];
		insertbinaryfrom_multi(root, btree,niv, poz2, poz);
	}
}
Node* newNode(int key,Node* created[])
{
	if (created[key]->key==-2) //nodul alocat dar nefolosit
	{
		Node* temp = new Node;
		temp->key = key;
		return (temp);
	}
	return created[key];
}
Node* createTree(int parent[], int n, Node* created[])
{
	// Create an array created[] to keep track 
	// of created nodes, initialize all entries 
	// as NULL 
	for (int i = 0; i < n; i++)
	{
		created[i] = new Node;
		created[i]->key = -2;  ///nod alocat dar nefolosit
	}
	Node* root = NULL;

 	for (int i = 0; i < n; i++)
	{
		Node* t = newNode(i,created);
		int parinte;
		int sizeparinte;
		int nodnou;
		if (parent[i] != -1)
		{
			parinte = parent[i];
			//pozitia fiului
		    nodnou= t->key;
			//size parinte - nr de fii ai parintelui
			sizeparinte = created[parinte]->size++;
			created[parinte]->key = parent[i];
			//fiul parintelui care are la randul lui fii sai
			created[nodnou] = t;
			created[nodnou]->parent = created[parinte];
			//mut referinta fiului parintelui pentru a se salva in pozitia radacinii toata structura arborelui
			//in caz ca de ex pe pozitia 5-radacina cu fii [1|3|5] iar noul nod creat este 6 care este fiul al lui 1
			//atunci el este pus pe pozitia created[1] insa aceasta trebuie actualizata in radacina, adica pe created[5]->v[1] = created[1], ce a fost modificat
		    created[parinte]->v[sizeparinte] = created[nodnou]; 
		}
		else
		{
			//radacina e pe pozitia i in vectorul de frecventa// o salvez in root si o returnez
			created[i]->key = i;
			created[i]->parent = NULL;
			root = created[i];		
		}

	}
	return root;
}
void printkey(int key, int niv)
{
	for (int i = 0; i < niv; i++)
		cout << "   ";
	cout << "|";
	cout << key;
	cout << "|";
	cout << endl;
}
void prettyprintStructure(Node* root, int niv,int poz2, int poz)
{
	if (root == NULL) return;

	printkey(root->key, niv);

	if (root->v[0])
	{
		prettyprintStructure(root->v[poz2++], ++niv,0, 0);
		if (root->parent == NULL) return;
		root = root->parent->v[++poz];
		prettyprintStructure(root, --niv, 0, poz);
	}
	else
	{ 	
	    root=root->parent->v[++poz];
		prettyprintStructure(root, niv, poz2, poz);
	}
}
	
void prettyPrintR1(int p[], int key, int n, int c){
		for (int i = 0; i < c; i++) {
			cout<<"   ";
		}
		cout<<"|"<< key<<"|"<< endl;
		c++;
		for (int i = 0; i < n; i++) 
			if(p[i]==key)
		   	   prettyPrintR1(p, i, n, c);
	
}
void prettyprintR3(Ntree* root, int space)
{
 
	if (root == NULL)
		return;
	space+=10;
	prettyprintR3(root->right, space);

	cout<<endl;
	for (int i = 10; i < space; i++)
		cout <<" ";
	cout <<"| " << root->key << " |";
	prettyprintR3(root->left, space);
}
		 

int main()
{
	Node* created[100] = { NULL };
	//int parent[] = { 1, 6, 4, 1,6,6,-1,4,1};
	//int parent[] = { -1, 0, 0, 1,1,2,2,3,4,5,6 };
	//int parent[] = { 1, 5, -1, 2,2,3,1,3,4 };
	int parent[] = { 11, 2, -1, 2,5,2,3,3,7,8,1,1 };
	int n = sizeof parent / sizeof parent[0];
	Node* root = createTree(parent, n,created);

	cout << "Pretty print of father array\n";
		
    prettyPrintR1(parent, root->key, n, 0);

	cout << "Pretty print of constructed tree\n";

	prettyprintStructure(root,0,0,0);
	
	Ntree* btree = NULL;

	insertbinaryfrom_multi(root, &btree, 0, 0, 0);

	cout << "Pretty print of constructed binary tree\n";
	prettyprintR3(btree, 0);


	return 0;

 }
#include <iostream>
using namespace std;
#include "Profiler.h"
#include <stack>
Profiler p("dfs");
enum {WHITE,GRAY,BLACK};

typedef struct Node{
    int id;
    int adjSize;
    Node** adj;
    int low;
    int color;
    int dist;
    int f;
    Node* parent;
}Node;

typedef struct {
    int nrNodes;
    Node** v;
}Graph;

void tarjan(Graph* g, int poz, stack <Node*>& mystack)
{
    static int time = 0;
    Node* u = g->v[poz];
    u->dist = u->low = time++;
    mystack.push(u);
    u->color = BLACK;
    for (int i = 0; i < u->adjSize; i++)
    {
        Node* v = u->adj[i];
        if (v->dist==-1)
        {
            tarjan(g, v->id, mystack);
            u->low = min(u->low, v->low);
        }
        else if (v->color==BLACK)
            u->low = min(u->low, v->dist);

     }
    if (u->low == u->dist)
    {
        cout << "O componenta puternic conexa: ";
        while (mystack.top() != u)
        {
             cout << mystack.top()->id << " ";
             g->v[mystack.top()->id]->color = WHITE;
             mystack.pop();
        }
        cout << mystack.top()->id<< "\n";
        g->v[mystack.top()->id]->color = WHITE;
        mystack.pop();
    }

}
void findSCC(Graph* g)
{
    for (int i = 0; i < g->nrNodes; i++)
    {
        g->v[i]->dist = -1;
 
    }
    stack <Node*> mystack;
    for (int i = 0; i < g->nrNodes; i++)
    {
        if (g->v[i]->dist == -1)
            tarjan(g, g->v[i]->id, mystack);
    }
}
void insert_list(Node* &head,Node* &last,Node* u)
{
    
    if(head == NULL)
     {
        head = last= u;
        head->parent = NULL;
     }
    else
    {
        head->parent = u;
        head = u;
        
        
    }
}
void topological(Graph* g, Node* u, int& time,Node* &head,Node* &last)
{
    time++;
    u->dist = time;
    u->color = GRAY;
    for (int i = 0; i < u->adjSize; i++)
    {

        Node* v = u->adj[i];
        if (v->color == WHITE)
        {
            v->parent = u;
            topological(g, v, time,head,last);
        }
    }
    insert_list(head,last, u);
    u->color = BLACK;
    time++;
    u->f = time;
}
Node* topological_sort(Graph* g)
{
    Node* head = NULL;
    Node* last = NULL;
    int time = 0;
    for (int i = 0; i < g->nrNodes; i++)
    {
        g->v[i]->color = WHITE;
        g->v[i]->parent = NULL;
    }
    for (int i = 0; i < g->nrNodes; i++)
        if (g->v[i]->color == WHITE)
        {
            topological(g, g->v[i], time,head,last);
        }
    return last;
}
void dfs_visit(Graph* g, Node* u, int& time,int n,Operation *op)
{
   
    time++;
    u->dist = time;
    u->color = GRAY;
    if (op != NULL) op->count();
    for (int i = 0; i < u->adjSize; i++)
    {
        if (op != NULL) op->count();
        Node* v = u->adj[i];
        if (v->color == WHITE)
        {
            if (op != NULL) op->count();
            v->parent = u;
            dfs_visit(g, v, time,n,op);
        }
    }

    u->color = BLACK;
    time++;
    u->f = time;
}
void dfs(Graph* g,int n,Operation *op)
{
    int time = 0;
    for (int i = 0; i < g->nrNodes; i++)
    {
        g->v[i]->color = WHITE;
        g->v[i]->parent = NULL;
    }
    for (int i = 0; i < g->nrNodes; i++)
        if (g->v[i]->color == WHITE)
        { 
            dfs_visit(g, g->v[i], time,n,op);
        }
}
void printdfs(Graph* g)
{
    for(int i = 0; i < g->nrNodes; i++)
    {
        if (g->v[i]->color == BLACK)
            cout << g->v[i]->id<<" cu timpul de descoperire "<<g->v[i]->dist <<endl ;
    }
     
}
void printlist(Node* l)
{
    if (l)
    {
        printlist(l->parent);
        cout <<"[id:"<< l-> id << " | "<<l->dist<<"/" <<l->f<<"] \n";
       
    }
}
void demo()
{
    Graph* g = new Graph;
    g->v = (Node**)malloc(10 * sizeof(Node*));
    g->nrNodes = 8;
    //initialize the nodes of the g
    g->v = (Node**)malloc(g->nrNodes * sizeof(Node*));
    for (int i = 0; i < g->nrNodes; ++i) {
        g->v[i] = (Node*)malloc(sizeof(Node));

        memset(g->v[i], 0, sizeof(Node));
        g->v[i]->adj = (Node**)malloc((g->nrNodes) * sizeof(Node*));
        for (int j = 0; j < g->nrNodes; j++)
        {
            g->v[i]->adj[j] = (Node*)malloc(sizeof(Node));

        }
        g->v[i]->id = i;
    }
    g->v[0]->adj[g->v[0]->adjSize] = g->v[1]; g->v[0]->adjSize++;
    g->v[1]->adj[g->v[1]->adjSize] = g->v[0]; g->v[1]->adjSize++;
    g->v[1]->adj[g->v[1]->adjSize] = g->v[5]; g->v[1]->adjSize++;
    g->v[5]->adj[g->v[5]->adjSize] = g->v[1]; g->v[5]->adjSize++;
    g->v[5]->adj[g->v[5]->adjSize] = g->v[6]; g->v[5]->adjSize++;
    g->v[6]->adj[g->v[6]->adjSize] = g->v[5]; g->v[6]->adjSize++;
    g->v[6]->adj[g->v[6]->adjSize] = g->v[7]; g->v[6]->adjSize++;
    g->v[7]->adj[g->v[7]->adjSize] = g->v[6]; g->v[7]->adjSize++;
    g->v[7]->adj[g->v[7]->adjSize] = g->v[3]; g->v[7]->adjSize++;
    g->v[3]->adj[g->v[3]->adjSize] = g->v[7]; g->v[3]->adjSize++;
    g->v[3]->adj[g->v[3]->adjSize] = g->v[2]; g->v[3]->adjSize++;
    g->v[2]->adj[g->v[2]->adjSize] = g->v[3]; g->v[2]->adjSize++;
    g->v[3]->adj[g->v[3]->adjSize] = g->v[4]; g->v[3]->adjSize++;
    g->v[4]->adj[g->v[4]->adjSize] = g->v[3]; g->v[4]->adjSize++;
   
    dfs(g,0,NULL);
    printdfs(g);
   
}
void demo2()
{
    Graph* g = new Graph;
    g->v = (Node**)malloc(10 * sizeof(Node*));
    g->nrNodes = 7;
    //initialize the nodes of the g
    g->v = (Node**)malloc(g->nrNodes * sizeof(Node*));
    for (int i = 0; i < g->nrNodes; ++i) {
        g->v[i] = (Node*)malloc(sizeof(Node));

        memset(g->v[i], 0, sizeof(Node));
        g->v[i]->adj = (Node**)malloc((g->nrNodes) * sizeof(Node*));
        for (int j = 0; j < g->nrNodes; j++)
        {
            g->v[i]->adj[j] = (Node*)malloc(sizeof(Node));

        }
        g->v[i]->id = i;
    }
    g->v[0]->adj[g->v[0]->adjSize] = g->v[1]; g->v[0]->adjSize++;
    g->v[1]->adj[g->v[1]->adjSize] = g->v[2]; g->v[1]->adjSize++;
    g->v[2]->adj[g->v[2]->adjSize] = g->v[0]; g->v[2]->adjSize++;
    g->v[1]->adj[g->v[1]->adjSize] = g->v[3]; g->v[1]->adjSize++;
    g->v[1]->adj[g->v[1]->adjSize] = g->v[4]; g->v[1]->adjSize++;
    g->v[1]->adj[g->v[1]->adjSize] = g->v[6]; g->v[1]->adjSize++;
    g->v[3]->adj[g->v[3]->adjSize] = g->v[5]; g->v[3]->adjSize++;
    g->v[4]->adj[g->v[4]->adjSize] = g->v[5]; g->v[4]->adjSize++;
    findSCC(g);
    
}
void demo3()
{
    Graph* g = new Graph;
    g->v = (Node**)malloc(10 * sizeof(Node*));
    g->nrNodes = 7;
    //initialize the nodes of the g
    g->v = (Node**)malloc(g->nrNodes * sizeof(Node*));
    for (int i = 0; i < g->nrNodes; ++i) {
        g->v[i] = (Node*)malloc(sizeof(Node));

        memset(g->v[i], 0, sizeof(Node));
        g->v[i]->adj = (Node**)malloc((g->nrNodes) * sizeof(Node*));
        for (int j = 0; j < g->nrNodes; j++)
        {
            g->v[i]->adj[j] = (Node*)malloc(sizeof(Node));

        }
        g->v[i]->id = i;
    }
    
    g->v[1]->adj[g->v[1]->adjSize] = g->v[2]; g->v[1]->adjSize++;
    g->v[1]->adj[g->v[1]->adjSize] = g->v[5]; g->v[1]->adjSize++;
    g->v[0]->adj[g->v[0]->adjSize] = g->v[1]; g->v[0]->adjSize++;
    g->v[5]->adj[g->v[5]->adjSize] = g->v[3]; g->v[5]->adjSize++;
    g->v[5]->adj[g->v[5]->adjSize] = g->v[4]; g->v[5]->adjSize++;
    g->v[0]->adj[g->v[0]->adjSize] = g->v[2]; g->v[0]->adjSize++;
    g->v[2]->adj[g->v[2]->adjSize] = g->v[3]; g->v[2]->adjSize++;
    g->v[6]->adj[g->v[6]->adjSize] = g->v[1]; g->v[6]->adjSize++;
    g->v[6]->adj[g->v[6]->adjSize] = g->v[5]; g->v[6]->adjSize++;
    Node* list = topological_sort(g);
    printlist(list);
}
void test()
{   
    int i, n = 0;
    for (n = 1000; n <= 4500; n += 100) {
        Operation op = p.createOperation("dfs_nr_muchii_variat", n);
        Graph graph;
        graph.nrNodes = 100;
        //initialize the nodes of the graph
        graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
        for (i = 0; i < graph.nrNodes; ++i) {
            graph.v[i] = (Node*)malloc(sizeof(Node));
            memset(graph.v[i], 0, sizeof(Node));
            graph.v[i]->adj = (Node**)malloc(graph.nrNodes * sizeof(Node*));
            for (int j = 0; j < graph.nrNodes; j++)
                graph.v[i]->adj[j] = (Node*)malloc(sizeof(Node));
        }
        for (int i = 0; i < graph.nrNodes - 1; i++)
        {
            graph.v[i]->adj[graph.v[i]->adjSize] = graph.v[i + 1];
            graph.v[i + 1]->adj[graph.v[i + 1]->adjSize] = graph.v[i];
            graph.v[i + 1]->adjSize++;
            graph.v[i]->adjSize++;
        }
        for (int i = 100; i < n; i++)
        {
            int a1 = 0, a2 = 0;
        exists:
            a1 = (int)rand() % 100;
            a2 = (int)rand() % 100;
            for (int i = 0; i < graph.v[a1]->adjSize; i++)
                if (graph.v[a1]->adj[i] == graph.v[a2])
                    goto exists;
            graph.v[a1]->adj[graph.v[a1]->adjSize] = graph.v[a2];
            graph.v[a2]->adj[graph.v[a2]->adjSize] = graph.v[a1];
            graph.v[a1]->adjSize++;
            graph.v[a2]->adjSize++;
        }
        dfs(&graph, n,&op);
       
    }
   
    for (n = 100; n <= 200; n += 10) {
        Operation op = p.createOperation("dfs_nr_noduri_variat", n);
        Graph graph;
        graph.nrNodes = n;
        //initialize the nodes of the graph
        graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
        for (i = 0; i < graph.nrNodes; ++i) {
            graph.v[i] = (Node*)malloc(sizeof(Node));
            memset(graph.v[i], 0, sizeof(Node));
            graph.v[i]->adj = (Node**)malloc(graph.nrNodes * sizeof(Node*));
            for (int j = 0; j < graph.nrNodes; j++)
                graph.v[i]->adj[j] = (Node*)malloc(sizeof(Node));
        }
        for (int i = 0; i < n - 1; i++)
        {
            graph.v[i]->adj[graph.v[i]->adjSize] = graph.v[i + 1];
            graph.v[i + 1]->adj[graph.v[i + 1]->adjSize] = graph.v[i];
            graph.v[i + 1]->adjSize++;
            graph.v[i]->adjSize++;
        }
        for (int i = n; i < 4500; i++)
        {
            int a1 = 0, a2 = 0;
        exists2:
            a1 = (int)rand() % n;
            a2 = (int)rand() % n;
            for (int i = 0; i < graph.v[a1]->adjSize; i++)
                if (graph.v[a1]->adj[i] == graph.v[a2])
                    goto exists2;
            graph.v[a1]->adj[graph.v[a1]->adjSize] = graph.v[a2];
            graph.v[a2]->adj[graph.v[a2]->adjSize] = graph.v[a1];
            graph.v[a1]->adjSize++;
            graph.v[a2]->adjSize++;
        }

        dfs(&graph, n, &op);

    }
    p.showReport();

}
 
int main()
{
   test();
    
	return 0;
}
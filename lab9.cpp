#include <stdlib.h>
#include <string.h>
#include "bfs.h"
#include <list>
#include <queue>
using namespace std;

int get_neighbors(const Grid *grid, Point p, Point neighb[])
{
    // TODO: fill the array neighb with the neighbors of the point p and return the number of neighbors
    // the point p will have at most 4 neighbors (up, down, left, right)
    // avoid the neighbors that are outside the grid limits or fall into a wall
    // note: the size of the array neighb is guaranteed to be at least 4
    int size = 0;
    if (p.col - 1 < grid->cols)
    {
        if (grid->mat[p.row][p.col - 1] != 1)
        {
            neighb[size].row = p.row;
            neighb[size].col = p.col - 1;
            size++;
        }
    }
    if (p.col + 1 > 0)
    {
        if (grid->mat[p.row][p.col + 1] != 1)
        {
            neighb[size].row = p.row;
            neighb[size].col = p.col + 1;
            size++;
        }
    }
    if (p.row - 1 > 0)
    {
        if (grid->mat[p.row - 1][p.col] != 1)
        {
            neighb[size].row = p.row - 1;
            neighb[size].col = p.col;
            size++;
        }
    }
    if (p.row + 1 < grid->rows)
    {
        if (grid->mat[p.row + 1][p.col] != 1)
        {
            neighb[size].row = p.row + 1;
            neighb[size].col = p.col;
            size++;
        }
    }



    return size;
}

void grid_to_graph(const Grid *grid, Graph *graph)
{
    //we need to keep the nodes in a matrix, so we can easily refer to a position in the grid
    Node *nodes[MAX_ROWS][MAX_COLS];
    int i, j, k;
    Point neighb[4];

    //compute how many nodes we have and allocate each node
    graph->nrNodes = 0;
    for(i=0; i<grid->rows; ++i){
        for(j=0; j<grid->cols; ++j){
            if(grid->mat[i][j] == 0){
                nodes[i][j] = (Node*)malloc(sizeof(Node));
                memset(nodes[i][j], 0, sizeof(Node)); //initialize all fields with 0/NULL
                nodes[i][j]->position.row = i;
                nodes[i][j]->position.col = j;
                ++graph->nrNodes;
            }else{
                nodes[i][j] = NULL;
            }
        }
    }
    graph->v = (Node**)malloc(graph->nrNodes * sizeof(Node*));
    k = 0;
    for(i=0; i<grid->rows; ++i){
        for(j=0; j<grid->cols; ++j){
            if(nodes[i][j] != NULL){
                graph->v[k++] = nodes[i][j];
            }
        }
    }

    //compute the adjacency list for each node
    for(i=0; i<graph->nrNodes; ++i){
        graph->v[i]->adjSize = get_neighbors(grid, graph->v[i]->position, neighb);
        if(graph->v[i]->adjSize != 0){
            graph->v[i]->adj = (Node**)malloc(graph->v[i]->adjSize * sizeof(Node*));
            k = 0;
            for(j=0; j<graph->v[i]->adjSize; ++j){
                if( neighb[j].row >= 0 && neighb[j].row < grid->rows &&
                    neighb[j].col >= 0 && neighb[j].col < grid->cols &&
                    grid->mat[neighb[j].row][neighb[j].col] == 0){
                        graph->v[i]->adj[k++] = nodes[neighb[j].row][neighb[j].col];
                }
            }
            if(k < graph->v[i]->adjSize){
                //get_neighbors returned some invalid neighbors
                graph->v[i]->adjSize = k;
                graph->v[i]->adj = (Node**)realloc(graph->v[i]->adj, k * sizeof(Node*));
            }
        }
    }
}

void free_graph(Graph *graph)
{
    if(graph->v != NULL){
        for(int i=0; i<graph->nrNodes; ++i){
            if(graph->v[i] != NULL){
                if(graph->v[i]->adj != NULL){
                    free(graph->v[i]->adj);
                    graph->v[i]->adj = NULL;
                }
                graph->v[i]->adjSize = 0;
                free(graph->v[i]);
                graph->v[i] = NULL;
            }
        }
        free(graph->v);
        graph->v = NULL;
    }
    graph->nrNodes = 0;
}

void bfs(Graph *graph, Node *s, Operation *op)
{
   
    for (int i = 0; i < graph->nrNodes; i++)
    {
        graph->v[i]->color = COLOR_WHITE;
        graph->v[i]->dist = INT_MAX;
        graph->v[i]->parent = NULL;
    }
    queue<Node*> q;

    s->color = COLOR_GRAY;
    s->dist = 0;
    s->parent = NULL;
    q.push(s);
    
    while (!q.empty())
    {
        if (op != NULL) op->count();
       Node* u = q.front();
        q.pop();
        int j = 0;
        int adjs = u->adjSize;
        for (j=0;j<adjs;j++)
        {
            Node* v = u->adj[j];
            
            if (v->color == COLOR_WHITE)
            {
                
                v->color == COLOR_GRAY;
                v->dist = u->dist + 1;
                v->parent = u;
                q.push(v);
            }
          
        }
        u->color = COLOR_BLACK;

    }
}
void printpair(Node* root)
{
    for (int i = 0; i < root->dist; i++)
        printf("   ");
    printf("(%d,%d)\n", root->position.row, root->position.col);

}
void prettyprintStructure(Node* root)
{

    if (root->color != COLOR_WHITE)
    {
        printpair(root);
        root->color = COLOR_WHITE;
        for (int i = 0; i < root->adjSize; i++)
            prettyprintStructure(root->adj[i]);
    }


}
void print_bfs_tree(Graph *graph)
{
    //first, we will represent the BFS tree as a parent array
    int n = 0; //the number of nodes
    int *p = NULL; //the parent array
    Point *repr = NULL; //the representation for each element in p

    //some of the nodes in graph->v may not have been reached by BFS
    //p and repr will contain only the reachable nodes
    int *transf = (int*)malloc(graph->nrNodes * sizeof(int));
    for(int i=0; i<graph->nrNodes; ++i){
        if(graph->v[i]->color == COLOR_BLACK){
            transf[i] = n;
            ++n;
        }else{
            transf[i] = -1;
        }
    }
    if(n == 0){
        //no BFS tree
        free(transf);
        return;
    }

    int err = 0;
    p = (int*)malloc(n * sizeof(int));
    repr = (Point*)malloc(n * sizeof(Node));
    for(int i=0; i<graph->nrNodes && !err; ++i){
        if(graph->v[i]->color == COLOR_BLACK){
            if(transf[i] < 0 || transf[i] >= n){
                err = 1;
            }else{
                repr[transf[i]] = graph->v[i]->position;
                if(graph->v[i]->parent == NULL){
                    p[transf[i]] = -1;
                }else{
                    err = 1;
                    for(int j=0; j<graph->nrNodes; ++j){
                        if(graph->v[i]->parent == graph->v[j]){
                            if(transf[j] >= 0 && transf[j] < n){
                                p[transf[i]] = transf[j];
                                err = 0;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    free(transf);
    transf = NULL;

    if (!err) {

        int rad = 0;
        for (int j = 0; j < n; j++)
            if (p[j] == -1)
            {
                rad = j;
                j = n;
            }
        for (int i = 0; i < graph->nrNodes; i++)
        {
            if (graph->v[i]->position.row == repr[rad].row && graph->v[i]->position.col == repr[rad].col)
            {
                prettyprintStructure(graph->v[i]);
                break;
            }
        }
    }
    if(p != NULL){
        free(p);
        p = NULL;
    }
    if(repr != NULL){
        free(repr);
        repr = NULL;
    }
}
int pozinadj(Graph* graph,Node* u)
{
    for (int i = 0; i < graph->nrNodes; i++)
        if (graph->v[i] == u)
            return i;
    return 0;
}
int shortest_path(Graph *graph, Node *start, Node *end, Node *path[])
{
    int parent[100] = { 0 };
    for (int i = 0; i < graph->nrNodes; i++)
    {
        parent[i] = -1;
        graph->v[i]->color = COLOR_WHITE;
        graph->v[i]->dist = 0;
 
    }
    list<Node*> queue;
    int startpos, endpos;
    startpos = pozinadj(graph, start);
    endpos = pozinadj(graph, end);
    int size = 0;
    queue.push_back(start);
    while (!queue.empty())
    {
        start = queue.front();
        int u = pozinadj(graph, start);
        queue.pop_front();
        int j = 0;
        int adjs = start->adjSize;
        for (j=0; j < adjs; j++)
        {
            int v = pozinadj(graph, start->adj[j]);
            if (start->adj[j]->dist==0)
            {   
                parent[v] = u;
                start->adj[j]->dist = start->dist + 1;
                queue.push_back(graph->v[v]);
                if (v == endpos)
                {
                    path[size++] = graph->v[endpos];
                    while (parent[endpos] != -1)
                    {
                        path[size++] = graph->v[parent[endpos]];
                        endpos = parent[endpos];
                        if (endpos == startpos)
                            return size;
                        
                    } 
                }
            }   
        }
    }
    return -1;
}


void performance()
{
    int n, i;
    Profiler p("bfs");

    // vary the number of edges
    for(n=1000; n<=4500; n+=100){
        Operation op = p.createOperation("bfs-edges", n);
        Graph graph;
        graph.nrNodes = 100;
        //initialize the nodes of the graph
        graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
        for(i=0; i<graph.nrNodes; ++i){
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
            int a1=0, a2 = 0;
        exists:
            a1 = (int)rand() % 99;
            a2 = (int)rand() % 99;
            for (int j = 0; j < graph.v[a1]->adjSize; j++)
                if (graph.v[a1]->adj[j] == graph.v[a2])
                    goto exists;
            graph.v[a1]->adj[graph.v[a1]->adjSize] = graph.v[a2];
            graph.v[a2]->adj[graph.v[a2]->adjSize] = graph.v[a1];
            graph.v[a1]->adjSize++;
            graph.v[a2]->adjSize++;
        }
        bfs(&graph, graph.v[0], &op);
        free_graph(&graph);
    }
    
    // vary the number of vertices
    for(n=100; n<=200; n+=10){
        Operation op = p.createOperation("bfs-vertices", n);
        Graph graph;
        graph.nrNodes = n;
        //initialize the nodes of the graph
        graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
        for(i=0; i<graph.nrNodes; ++i){
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
            a1 = (int)rand() % 99;
            a2 = (int)rand() % 99;
            for (int j = 0; j < graph.v[a1]->adjSize; j++)
                if (graph.v[a1]->adj[j] == graph.v[a2])
                    goto exists2;
            graph.v[a1]->adj[graph.v[a1]->adjSize] = graph.v[a2];
            graph.v[a2]->adj[graph.v[a2]->adjSize] = graph.v[a1];
            graph.v[a1]->adjSize++;
            graph.v[a2]->adjSize++;
        }

        bfs(&graph, graph.v[0], &op);
        free_graph(&graph);
    }
    
    p.showReport();
}

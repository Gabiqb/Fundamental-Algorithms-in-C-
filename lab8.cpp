#include <iostream>
#include <algorithm>
#include <vector> 
#include "Profiler.h"

Profiler p("setskruskal");

using namespace std;
#define MAXINTT 1e9

#define MAXSIZE 10000
#define STEPSIZE 100

int ns;
typedef struct Dset {
	int *rank, *parent, n;
}Dset;

typedef  pair<int, int> edgepair;
typedef struct graf{
	int V, E;
	vector< pair < int, edgepair > >arce;
	void addedge(int w, int s, int d)
	{
		arce.push_back({ w,{s,d} });
	}
}Graf;
void make_set(Dset* x, int key)
{
	x->parent[key] = key;
	x->rank[key] = 0;
}
int find(Dset* x, int key)
{
	Operation opatr = p.createOperation("kruskal-atr", ns);
	Operation opcomp = p.createOperation("kruskal-comp", ns);

	opcomp.count();
	if (x->parent[key] != key)
	{
		opatr.count();
		x->parent[key] = find(x, x->parent[key]);
		return x->parent[key];
	}
	else
		return key;

}

void link(Dset* d, int x, int y)
{
	Operation opatr = p.createOperation("kruskal-atr", ns);
	
	if (d->rank[x] < d->rank[y])
	{
		opatr.count();
		d->parent[x] = y;	
	}
	else 
	{
		opatr.count();
		d->parent[y] = x;
		if (d->rank[x] == d->rank[y])
			d->rank[x] = d->rank[x] + 1;
	}
	
}
void UNION(Dset* d,int x, int y)
{
	 
	int xset = find(d, x);
	int yset = find(d, y);
	if (xset == yset)
	{
		return;
	}
	link(d,xset,yset);
	UNION(d, x, y);
}
Dset* createnullset(Dset* x, int n)
{
	x = (Dset*)malloc(sizeof(Dset));
	x->rank = (int*)malloc((n + 1)*sizeof(int));
	x->parent = (int*)malloc((n + 1 )*sizeof(int));
	for (int i = 0; i <= n; i++)
	{
		x->parent[i] = MAXINTT;
		x->rank[i] = 0;
	}
	x->n = n;
	return x;
}
Dset* createsetforgraph(Dset* x, int n)
{
	x = (Dset*)malloc(sizeof(Dset));
	x->rank = (int*)malloc((n+1) * sizeof(int));
	x->parent = (int*)malloc((n+1)* sizeof(int));
	for (int i = 0; i <= n; i++)
	{
		x->parent[i] = i;
		x->rank[i] = 0;
	}
	x->n = n;
	return x;
}
Dset* kruskal(Graf* g)
{
	Dset* d = new Dset;
	d = createsetforgraph(d, g->V);
	int mst_p = 0;
	sort(g->arce.begin(), g->arce.end());
	 
	vector< pair<int, edgepair> >::iterator i;
	for (i = g->arce.begin(); i != g->arce.end(); i++)
	{	
		int sursa = i->second.first;
		int dest = i->second.second;
		int set_sursa = find(d, sursa);
		int set_dest = find(d, dest);
		
		if (set_sursa != set_dest)
		{
			cout << sursa << " - " << dest << endl;

			mst_p += i->first;
			UNION(d, sursa, dest);
		}
	}
	cout << "Costul total al arborelui este: " << mst_p<<endl;
	return d;
}
Dset* kruskaltest(Graf* g)
{
	Operation opatr = p.createOperation("kruskal-atr", ns);
	Operation opcomp = p.createOperation("kruskal-comp", ns);
	Dset* d = new Dset;
	d = createsetforgraph(d, g->V);
	int mst_p = 0;
	sort(g->arce.begin(), g->arce.end());

	vector< pair<int, edgepair> >::iterator i;
	for (i = g->arce.begin(); i != g->arce.end(); i++)
	{
		opatr.count(2);
		int sursa = i->second.first;
		int dest = i->second.second;
		int set_sursa = find(d, sursa);
		int set_dest = find(d, dest);
		opcomp.count();
		if (set_sursa != set_dest)
		{
			
			opatr.count();
			mst_p += i->first;
			UNION(d, sursa, dest);
		}
	}

	return d;
}
void printdset(Dset* d)
{
	bool ok = 0;
	for (int i = 0; i <= d->n; i++)
	{
		ok = 0;
		for (int j = 0; j <= d->n; j++)
		{
			if (i == d->parent[j] && d->parent[j]!=MAXINTT)
			{
				cout << j << " ";
				ok = 1;
			}
		}
		if (ok == 1)
			cout << endl;
	}
}
void demo()
{
	Dset* x = NULL;
	x = createnullset(x, 9);
	make_set(x, 2);
	make_set(x, 0);
	make_set(x, 3);
	make_set(x, 4);
	make_set(x, 6);
	make_set(x, 5);
	make_set(x, 1);
	make_set(x, 9);
	make_set(x, 8);
	make_set(x, 7);
	UNION(x, 0, 2);
	UNION(x, 2, 3);
	UNION(x, 4, 5);
	UNION(x, 0, 5);
	UNION(x, 6, 8);
	UNION(x, 0, 3);
	printdset(x);
}

void demo2()
{
	cout << "Muchiile arborelui de cost minim sunt: \n";
	Graf* g = new Graf;
	g->V = 9;
	g->E = 6;

	g->addedge(1, 0, 2);
	g->addedge(5, 2, 3);
	g->addedge(9, 3, 8);
	g->addedge(2, 0, 1);
	g->addedge(7, 4, 2);
	g->addedge(5, 1, 4);

	Dset* d = kruskal(g);
	 
}

void test()
{
	int a1[4 * MAXSIZE];
	int a2[4 * MAXSIZE];
	int a3[4 * MAXSIZE];
	
	for (int t = 0; t < 5; t++)
	{
		
		for (ns = STEPSIZE; ns <= MAXSIZE; ns += STEPSIZE)
		{
			Graf* g = new Graf;
			FillRandomArray(a1, 4*ns, 1, ns, false, UNSORTED);
			FillRandomArray(a2, 4*ns, 1, ns, false, UNSORTED);
			FillRandomArray(a3, 4*ns, 1, ns, false, UNSORTED);
			for (int i = 0; i < 4 * ns; i++)
				g->addedge(a1[i], a2[i], a3[i]);
			g->V = ns;
			g->E = 4 * ns;
			Dset* d = kruskaltest(g);
		}
	}
	p.divideValues("kruskal-atr", 5);
	p.divideValues("kruskal-comp", 5);
	p.addSeries("KruskalAlg", "kruskal-atr", "kruskal-comp");
	p.showReport();
}
int main()
{

   /*demo();
	cout << endl;
	demo2();
	*/
	test();

	return 0;


}
#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"
Profiler p("hash");

#define M 25 //dimensiunea tabelei de dispersie
#define N 9997 

typedef struct cell {
    int val;
    int status;
  
}Cell;
enum { FREE, OCCUPIED };

void set_table_free(Cell* T, int m)
{
    //initializam tabela
    int i;
    for (i = 0; i < m; i++) {
        T[i].status = FREE;
    }

}
//verificam daca toata tabela e ocupata
int hash_table_occupied(Cell* T, int m) {
    int i;
    for (i = 0; i < m; i++) {
        if (T[i].status == FREE) return 0;
    }
    return 1;
}
int h_prime(int k, int m) {
    return k % m;
}

//returneaza pozitia la care se va verifica tabela de dispersie folosind verificarea liniara


int quadratic_probing(int k, int m, int i)
{
    int c1, c2 = c1 = 1;
    int val = (h_prime(k, m) + c1 * i + c2 * i * i) % m;
    return val;
}
void insert_quadratic_probing(int k, Cell* T, int m)
{
    int i = 0;
 
    if (hash_table_occupied(T, m) == 1) {
        printf("Nu se mai poate insera cheia %d, tabela este plina \n", k);
        return;
    }

    int collision = 1;
    int h = 0;
    do {
        h = quadratic_probing(k, m, i);
        if (T[h].status == FREE)
            collision = 0;
        else
        {
            
            i++;
        }
    } while (collision || i == N);
    T[h].status = OCCUPIED;
    T[h].val = k;

}
void insert_quadratic_probing80(int k, Cell* T, int m)
{
    int i = 0;
    Operation incerc = p.createOperation("incercari factor de umplere 0.8", N);
    if (hash_table_occupied(T, m)==1) {
        printf("Nu se mai poate insera cheia %d, tabela este plina \n", k);
        return;
    }
    
    int collision = 1;
    int h = 0;
    do {
        h = quadratic_probing(k, m, i);
        if (T[h].status == FREE)
            collision = 0;
        else
        {
            incerc.count();
            i++;
        }
    } while (collision || i==N);
    T[h].status = OCCUPIED;
    T[h].val = k;
   
}

void insert_quadratic_probing85(int k, Cell* T, int m)
{
    int i = 0;
    Operation incerc = p.createOperation("incercari factor de umplere 0.85", N);
    if (hash_table_occupied(T, m) == 1) {
        printf("Nu se mai poate insera cheia %d, tabela este plina \n", k);
        return;
    }

    int collision = 1;
    int h = 0;
    do {
        h = quadratic_probing(k, m, i);
        if (T[h].status == FREE)
            collision = 0;
        else
        {
            incerc.count();
            i++;
        }
    } while (collision || i == N);
    T[h].status = OCCUPIED;
    T[h].val = k;

}
void insert_quadratic_probing90(int k, Cell* T, int m)
{
    int i = 0;
    Operation incerc = p.createOperation("incercari factor de umplere 0.9", N);
    if (hash_table_occupied(T, m) == 1) {
        printf("Nu se mai poate insera cheia %d, tabela este plina \n", k);
        return;
    }

    int collision = 1;
    int h = 0;
    do {
        h = quadratic_probing(k, m, i);
        if (T[h].status == FREE)
            collision = 0;
        else
        {
            incerc.count();
            i++;
        }
    } while (collision || i == N);
    T[h].status = OCCUPIED;
    T[h].val = k;

}
void insert_quadratic_probing95(int k, Cell* T, int m)
{
    int i = 0;
    Operation incerc = p.createOperation("incercari factor de umplere 0.95", N);
    if (hash_table_occupied(T, m) == 1) {
        printf("Nu se mai poate insera cheia %d, tabela este plina \n", k);
        return;
    }

    int collision = 1;
    int h = 0;
    do {
        h = quadratic_probing(k, m, i);
        if (T[h].status == FREE)
            collision = 0;
        else
        {
            incerc.count();
            i++;
        }
    } while (collision || i == N);
    T[h].status = OCCUPIED;
    T[h].val = k;

}
void insert_quadratic_probing99(int k, Cell* T, int m)
{
    int i = 0;
    Operation incerc = p.createOperation("incercari factor de umplere 0.99", N);
    if (hash_table_occupied(T, m) == 1) {
        printf("Nu se mai poate insera cheia %d, tabela este plina \n", k);
        return;
    }

    int collision = 1;
    int h = 0;
    do {
        h = quadratic_probing(k, m, i);
        if (T[h].status == FREE)
            collision = 0;
        else
        {
            incerc.count();
            i++;
        }
    } while (collision || i == N);
    T[h].status = OCCUPIED;
    T[h].val = k;

}
Cell* search_quadratic(Cell* hTable, int key,int n)
{
    
    int i = 0;
    Cell* t = (hTable + quadratic_probing(key, M, i));
    while (i <= n && t->status!=FREE)
   {
        if (t->val == key)
            return t;
        else
        {
            i++;
        }
       t = (hTable + quadratic_probing(key, M, i));
    }
   return NULL;
   
}
Cell* search_quadratic80(Cell* hTable, int key, int n)
{
    Operation efort = p.createOperation("efort pentru 0.8", 80);

    int i = 0;
    Cell* t = (hTable + quadratic_probing(key, n, i));
    while (i <= n && t->status != FREE)
    {
        if (t->val == key)
            return t;
        else
        {
            efort.count();
            i++;
        }
        t = (hTable + quadratic_probing(key, n, i));
    }
    return NULL;

}
Cell* search_quadratic80n(Cell* hTable, int key, int n)
{
    Operation efort = p.createOperation("efort pentru 0.8 negasite", 80);

    int i = 0;
    Cell* t = (hTable + quadratic_probing(key, n, i));
    while (i <= n && t->status != FREE)
    {
        if (t->val == key)
            return t;
        else
        {
            efort.count();
            i++;
        }
        t = (hTable + quadratic_probing(key, n, i));
    }
    return NULL;

}
Cell* search_quadratic85(Cell* hTable, int key, int n)
{
    Operation efort = p.createOperation("efort pentru 0.85", 85);

    int i = 0;
    Cell* t = (hTable + quadratic_probing(key, n, i));
    while (i <= n && t->status != FREE)
    {
        if (t->val == key)
            return t;
        else
        {
            efort.count();
            i++;
        }
        t = (hTable + quadratic_probing(key, n, i));
    }
    return NULL;

}
Cell* search_quadratic85n(Cell* hTable, int key, int n)
{
    Operation efort = p.createOperation("efort pentru 0.85 negasite", 85);

    int i = 0;
    Cell* t = (hTable + quadratic_probing(key, n, i));
    while (i <= n && t->status != FREE)
    {
        if (t->val == key)
            return t;
        else
        {
            efort.count();
            i++;
        }
        t = (hTable + quadratic_probing(key, n, i));
    }
    return NULL;

}
Cell* search_quadratic90(Cell* hTable, int key, int n)
{
    Operation efort = p.createOperation("efort pentru 0.9", 90);
   
    int i = 0;
    Cell* t = (hTable + quadratic_probing(key, n, i));
    while (i <= n && t->status != FREE)
    {
        if (t->val == key)
            return t;
        else
        {
            efort.count();
            i++;
        }
        t = (hTable + quadratic_probing(key, n, i));
    }
   
    return NULL;

}
Cell* search_quadratic90n(Cell* hTable, int key, int n)
{
    Operation efort = p.createOperation("efort pentru 0.9 negasite", 90);

    int i = 0;
    Cell* t = (hTable + quadratic_probing(key, n, i));
    while (i <= n && t->status != FREE)
    {
        if (t->val == key)
            return t;
        else
        {
            efort.count();
            i++;
        }
        t = (hTable + quadratic_probing(key, n, i));
    }

    return NULL;

}
Cell* search_quadratic95(Cell* hTable, int key, int n)
{
    Operation efort = p.createOperation("efort pentru 0.95", 95);

    int i = 0;
    Cell* t = (hTable + quadratic_probing(key, n, i));
    while (i <= n && t->status != FREE)
    {
        if (t->val == key)
            return t;
        else
        {
            efort.count();
            i++;
        }
        t = (hTable + quadratic_probing(key, n, i));
    }
    return NULL;

}
Cell* search_quadratic95n(Cell* hTable, int key, int n)
{
    Operation efort = p.createOperation("efort pentru 0.95 negasite", 95);

    int i = 0;
    Cell* t = (hTable + quadratic_probing(key, n, i));
    while (i <= n && t->status != FREE)
    {
        if (t->val == key)
            return t;
        else
        {
            efort.count();
            i++;
        }
        t = (hTable + quadratic_probing(key, n, i));
    }
    return NULL;

}
Cell* search_quadratic99(Cell* hTable, int key, int n)
{
    Operation efort = p.createOperation("efort pentru 0.99", 99);

    int i = 0;
    Cell* t = (hTable + quadratic_probing(key, n, i));
    while (i <= n && t->status != FREE)
    {
        if (t->val == key)
            return t;
        else
        {
            efort.count();
            i++;
        }
        t = (hTable + quadratic_probing(key, n, i));
    }
    return NULL;

}
Cell* search_quadratic99n(Cell* hTable, int key, int n)
{
    Operation efort = p.createOperation("efort pentru 0.99 negasite", 99);

    int i = 0;
    Cell* t = (hTable + quadratic_probing(key, n, i));
    while (i <= n && t->status != FREE)
    {
        if (t->val == key)
            return t;
        else
        {
            efort.count();
            i++;
        }
        t = (hTable + quadratic_probing(key, n, i));
    }
    return NULL;

}
void afisare(Cell* T, int m) {
    int i;
    printf("\nTabela de dispersie este \n");
    for (i = 0; i < m; i++) {
        if (T[i].status == OCCUPIED)
            printf("T[%d]= %d \n", i, T[i].val);
        else
            printf("T[%d]= --\n", i);

    }
}


void demo()
{
    // tabela de dispersie
    Cell* hTable=(Cell*)malloc(M*sizeof(Cell));
     
    int i, n, x;
    //initializam tabelul nostru de dispersie
    set_table_free(hTable, M);
   
    for (int i = 0; i < M; i++)
    {
        int x = rand() % 50 +1;
        insert_quadratic_probing(x,hTable, M);
    }
    afisare(hTable, M);
   
     //afisam toate elementele din tabel din nou 
   
    Cell* f = search_quadratic(hTable, 26,M);
    if (f != NULL)
        printf("elementul %d este gasit ",f->val);
    else
        printf("nu s-a gasit elementul");
    
}
void test80()
{
    Cell* T = (Cell*)malloc(N * sizeof(Cell));

    set_table_free(T, N);
    double alfa = 0.8;
    int v[N];
    int nrel = (int)(alfa * N);
    FillRandomArray(v, nrel, 10, 15000, true, UNSORTED);
    for (int i = 0; i < nrel; i++)
        insert_quadratic_probing80(v[i], T, N);
  //  afisare(T, N);
    ///1500 de elemente puse in sir se cauta
    
    for (int i = 0; i < 1500; i++)
       search_quadratic80(T, v[i],N);
   
    ///1500 de elemente care nu se afla in sir
  
    FillRandomArray(v, 1500, 20000, 30000, true, UNSORTED);
    for(int i=0;i< 1500;i++)
        search_quadratic80n(T, v[i],N);


}
void test85()
{
    Cell* T = (Cell*)malloc(N * sizeof(Cell));

    set_table_free(T, N);
    double alfa = 0.85;
    int v[N];
    int nrel = (int)(alfa * N);
    FillRandomArray(v, nrel, 10, 15000, true, UNSORTED);
    for (int i = 0; i < nrel; i++)
        insert_quadratic_probing85(v[i], T, N);

    for (int i = 0; i < 1500; i++)
        search_quadratic85(T, v[i],N);

    /// 1500 de elemente care nu se afla in sir

    FillRandomArray(v, 1500, 20000, 30000, true, UNSORTED);
    for (int i = 0; i < 1500; i++)
        search_quadratic85n(T, v[i],N);
}
void test90()
{
    Cell* T = (Cell*)malloc(N * sizeof(Cell));

    set_table_free(T, N);
    double alfa = 0.9;
    int v[N];
    int nrel = (int)(alfa * N);
    FillRandomArray(v, nrel, 10, 15000, true, UNSORTED);
    for (int i = 0; i < nrel; i++)
        insert_quadratic_probing90(v[i], T, N);

    for (int i = 0; i < 1500; i++)
        search_quadratic90(T, v[i],N);

    /// 1500 de elemente care nu se afla in sir

    FillRandomArray(v, 1500, 20000, 30000, true, UNSORTED);
    for (int i = 0; i < 1500; i++)
        search_quadratic90n(T, v[i],N);
}
void test95()
{
    Cell* T = (Cell*)malloc(N * sizeof(Cell));

    set_table_free(T, N);
    double alfa = 0.95;
    int v[N];
    int nrel = (int)(alfa * N);
    FillRandomArray(v, nrel, 10, 15000, true, UNSORTED);
    for (int i = 0; i < nrel; i++)
        insert_quadratic_probing95(v[i], T, N);

    for (int i = 0; i < 1500; i++)
        search_quadratic95(T, v[i],N);

    /// 1500 de elemente care nu se afla in sir

    FillRandomArray(v, 1500, 20000, 30000, true, UNSORTED);
    for (int i = 0; i < 1500; i++)
        search_quadratic95n(T, v[i],N);
}
void test99()
{
    Cell* T = (Cell*)malloc(N * sizeof(Cell));

    set_table_free(T, N);
    double alfa = 0.99;
    int v[N];
    int nrel = (int)(alfa * N);
    FillRandomArray(v, nrel, 10, 15000, true, UNSORTED);
    for (int i = 0; i < nrel; i++)
        insert_quadratic_probing99(v[i], T, N);

    for (int i = 0; i < 1500; i++)
        search_quadratic99(T, v[i],N);

    /// 1500 de elemente care nu se afla in sir

    FillRandomArray(v, 1500, 20000, 30000, true, UNSORTED);
    for (int i = 0; i < 1500; i++)
        search_quadratic99n(T, v[i],N);
    
}
void test1()
{
    test80();
    test85();
    test90();
    test95();
    test99();
    p.createGroup("nr incercari pentru fiecare factor de umplere", "incercari factor de umplere 0.8", "incercari factor de umplere 0.85", "incercari factor de umplere 0.9", "incercari factor de umplere 0.95", "incercari factor de umplere 0.99");
    p.createGroup("efort ", "efort pentru 0.8","efort pentru 0.8 negasite", "efort pentru 0.85", "efort pentru 0.85 negasite", "efort pentru 0.9", "efort pentru 0.9 negasite", "efort pentru 0.95", "efort pentru 0.95 negasite", "efort pentru 0.99", "efort pentru 0.99 negasite");
    p.showReport();
     
}
int main()
{
    test1();
    return 0;
}

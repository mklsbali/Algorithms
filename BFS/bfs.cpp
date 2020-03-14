/*Miklos Balazs
Grupa 30224*/

/*
Observatii finale:
Graficonii arata ca:
- pentru un graf neorientat complexitatea lui BFS este O(V+2*E)
- pentru un graf neorientat complexitatea lui BFS este O(V+E)*/
#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"
Profiler p("BFS");
//Structura unei muchie
typedef struct node
{
	int init, fin;
	struct  node *next;
}NodeG;
//structura grafului
typedef struct
{
	int V, E;
	NodeG **nodes;
}Graf;
//structura coadei
typedef struct
{
	int first, last;
	int size, CAPACITY;
	int *vect;
}Coada;
//initializam coada
void initializare(Coada *Q,Graf G)
{
//	Q = (Coada*)malloc(sizeof(Coada));
	Q->first = 0;
	Q->last = G.V-1;
	Q->size = 0;
	Q->CAPACITY = G.V;
	Q->vect = (int*)malloc(G.V*G.V*sizeof(int));
}
//functia care pune un element la coada
void enqueue(Coada *Q, int key)
{
	if (Q->size == Q->CAPACITY)
		return;
	Q->size++;
	Q->last = (Q->last + 1) % Q->CAPACITY;
	Q->vect[Q->last] = key;
}
//functia care verifica daca coada e gol
int isempty(Coada Q)
{
	return (Q.size == 0);
}
//functia care returneaza elementul sters
int dequeue(Coada *Q)
{
	if (!isempty(*Q))
	{
		int x = Q->vect[Q->first];
		Q->size--;
		Q->first = (Q->first + 1) % Q->CAPACITY;
		return x;
	}
	
}
//insert first
void insert(Graf *G, int init, int fin)
{
	NodeG *neww = (NodeG*)malloc(sizeof(NodeG));
	neww->init = init;
	neww->fin = fin;
	neww->next = NULL;
	if (G->nodes[init] == NULL)
	{
		G->nodes[init] = neww;
	}
	else
	{
		neww->next = G->nodes[init];
		G->nodes[init] = neww;
	}
}
//Functia care aloca memorie pentru un graf cu V varv, E muchie
Graf * makeGraf(int V, int E)
{
	Graf *G = (Graf*)malloc(sizeof(Graf));
	G->E = E;
	G->V = V;
	G->nodes = (NodeG**)malloc(G->V*sizeof(NodeG*));
	for (int i = 0; i < G->V; i++)
	{
		G->nodes[i] = (NodeG*)malloc(sizeof(NodeG));
		G->nodes[i] = NULL;
	}
	return G;
}
//Functia care printeaza un graf
void printGraf(Graf  G)
{
	printf("Graful arata in felul urmator:\n");
	for (int i = 0; i < G.V; i++)
	{
		printf("%d ", G.nodes[i]->init);
		NodeG *current = G.nodes[i];
		while (current!= NULL)
		{
			printf("-->%d ",current->fin);
			current = current->next;
		}
		printf("\n");
	}
	printf("\n");
}
//functia care verifica daca doua varfuri sunt adiacente
int isAdiacent(Graf G,int a,int b)
{
	NodeG *current = G.nodes[a];
	while (current!=NULL)
	{
		if (current->fin == b)
			return 1;
		current = current->next;
	}
	return 0;
}
//functia care genereaza graf random
Graf* createGraf(int V, int E)
{
	Graf *G = makeGraf(V, E);
	int i = 0;
	while (i < E)
	{
		int r1 = rand() % V;
		int r2 = rand() % V;
		if (r1 != r2)
		{
			if (!isAdiacent(*G, r1, r2))
			{
				insert(G, r1, r2);
				//insert(G, r2, r1);
				i++;
			}
		}
	}
	return G;

}
//Functia BFS pentru o componenta conexa
int * BFS(Graf G, int ndstart, int *vizitate,Operation op)
{
	Coada Q;
	initializare(&Q, G);
	int i, v;
	vizitate[ndstart] = 1;
//	op.count();
	enqueue(&Q, ndstart);
	int k = 0;
	while (!isempty(Q))
	{
		//op.count();
		v = dequeue(&Q);
		//printf("%d ", v);
		for (NodeG *aux = G.nodes[v]; aux != NULL;aux=aux->next)
		{
			op.count();
			if (vizitate[aux->fin] == 0)
			{
				vizitate[aux->fin] = 1;
			//	op.count();
				enqueue(&Q, aux->fin);
			}
		}
	}
	return vizitate;
}
//BFS pentru toate componente conexta
void BFSall(Graf G, int ndstart,Operation op)
{
	int *vizitate = (int*)malloc(G.V*sizeof(int));
	for (int i = 0; i < G.V; i++)
	{
		vizitate[i] = 0;
	}
	BFS(G, ndstart, vizitate,op);
	for (int i = 0; i < G.V; i++)
	{
		if (vizitate[i] == 0)
			BFS(G, i, vizitate,op);
	}
}
//Functia  demo care arata corectitudinea algoritmului
void demo()
{
	Graf *G = makeGraf(7, 7);
	insert(G, 0, 1);
	insert(G, 1, 0);

	insert(G, 0, 2);
	insert(G, 2, 0);

	insert(G, 1, 2);
	insert(G, 2, 1);

	insert(G, 1, 4);
	insert(G, 4, 1);

	insert(G, 2, 3);
	insert(G, 3, 2);

	insert(G, 3, 4);
	insert(G, 4, 3);

	insert(G, 5, 6);
	insert(G, 6, 5);
	Operation op = p.createOperation("operatii",10);
	printGraf(*G);
	BFSall(*G,0,op);

}
//functia perform unde V e constant 100
void performE()
{
	
	int n;
	for (n = 1000; n <= 4500; n += 100)
	{
		Operation op = p.createOperation("V constant", n);
		Graf *G = createGraf( 100, n);
		BFSall(*G, 0,op);
	}
	p.showReport();
}
//fuctia unde nr muciilor e 4500 si V varieaza
void performV()
{

	int n;
	for (n = 100; n <= 200; n += 10)
	{
		Operation op = p.createOperation("E constant", n);
		Graf *G = createGraf(n, 4500);
		BFSall(*G, 0, op);
	}
	p.showReport();
}

int main()
{
//	demo();
	//performE();
	performV();
	return 0;
}
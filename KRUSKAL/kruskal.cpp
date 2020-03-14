#include <stdlib.h>
#include <stdio.h>
#include "Profiler.h"
#include <time.h>
typedef struct
{
	int parent;
	int rang;
}Element;

typedef struct
{
	int init, fin, weight;
}Edge;


typedef struct
{

	int V, E;

	Edge* edge;
}Graf;
Element make_set(Element elements[], int x)
{
	elements[x].parent = x;
	elements[x].rang = 0;
	return elements[x];
}
int search(Element elements[], int x)
{
	if (elements[x].parent != x)
		elements[x].parent=search(elements, elements[x].parent);
	return elements[x].parent;
}
void uneste(Element elements[], int x, int y)
{
	if (elements[x].rang > elements[y].rang)
		elements[y].parent = x;
	else
	{
		elements[x].parent = y;
		if (elements[x].rang == elements[y].rang)
			elements[y].rang++;
	}
}
void reuneste(Element elements[], int x, int y)
{
	int rootx = search(elements, x);
	int rooty = search(elements, y);
	uneste(elements, x, y);
}
int Comp(const void* a, const void* b)
{
	Edge* a1 = (Edge*)a;
	Edge* b1 = (Edge*)b;
	return a1->weight > b1->weight;
}
Graf* makeGraf(int V, int E)
{
	Graf* G = (Graf*)malloc(sizeof(Graf));
	G->V = V;
	G->E = E;

	G->edge = (Edge*)malloc(E*sizeof(Edge));

	return G;
}
Edge * Kruskal(Graf *G)
{
	Edge *rezult = (Edge*)malloc(G->V*sizeof(Edge));
	int e, i;
	qsort(G->edge, G->E, sizeof(G->edge[0]), Comp);
	Element *elements = (Element*)malloc(G->V*sizeof(Element));
	for (int i = 0; i < G->V; i++)
	{
		elements[i] = make_set(elements,i);
	}
	e = 0, i = 0;
	
	while (e < G->V -1)
	{
		Edge current = G->edge[i++];
		int x = search(elements, current.init);
		int y = search(elements, current.fin);
		if (x != y)
		{
			rezult[e++] = current;
			reuneste(elements, x, y);
		}
	}
	printf("Arborele cu cost minim:\n");
	for (i = 0; i < e; ++i)
	{
		printf("%d %d %d\n", rezult[i].init, rezult[i].fin, rezult[i].weight);
	}
	return rezult;
}
void demo()
{


	Graf *G = makeGraf(6, 7);

	G->edge[0].init = 0;
	G->edge[0].fin = 1;
	G->edge[0].weight = 3;


	G->edge[1].init = 1;
	G->edge[1].fin = 2;
	G->edge[1].weight = 5;


	G->edge[2].init = 1;
	G->edge[2].fin = 3;
	G->edge[2].weight = 4;


	G->edge[3].init = 2;
	G->edge[3].fin = 3;
	G->edge[3].weight = 2;

	G->edge[4].init = 3;
	G->edge[4].fin = 4;
	G->edge[4].weight = 7;

	G->edge[5].init = 3;
	G->edge[5].fin = 5;
	G->edge[5].weight = 1;

	G->edge[6].init = 4;
	G->edge[6].fin = 5;
	G->edge[6].weight = 8;


	/*
	
	0
	|
	|
	|3
	|
	|  5
	1----2
	|	/
   4|  /2
   	| /
	|/
	3
	|\
   7| \ 
	|  \1
	|	\ 
	4----5
	  8
	*/
	Edge *rezult=Kruskal(G);
	
		

}
void perform()
{
	int n;
	for (n = 100; n <= 10000; n += 100)
	{
		srand(time(NULL));
		Graf *G = makeGraf(n, 4*n);
		for (int i = 0; i < 4*n; i++)
		{
			G->edge[i].init = 1 + rand() % n;
			G->edge[i].fin = 1 + rand() % n;
			G->edge[i].weight = rand() % 10000+1;
		}
		Kruskal(G);
	}

}
int main()
{
	/*Element e[7];
	make_set(e, 5);
	make_set(e, 6);
	reuneste(e,5, 6);
	//printf("%d", e[6].rang);
	int p = search(e, 7);
	printf("%d", p);*/
	demo();
//	perform();
	return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int key;
	int rang;
	struct node *parent;
}Element;
typedef struct
{
	int init;
	int weight;
	int fin;
}Edge;
typedef struct
{
	int V;
	int E;
	Edge * edges;

}Graf;

Element * make_set(int x)
{
	Element *el = (Element*)malloc(sizeof(Element));
	el->key = x;
	el->parent = el;
	el->rang = 0;
	return el;
}
Element * search(Element * x)
{
	if (x->key != x->parent->key)
		x->parent = search(x->parent);
	return x->parent;
}
void uneste(Element *x, Element *y)
{
	if (x->rang > y->rang)
	{
		y->parent = x;
	}
	else
	{
		if (x->rang == y->rang)
			y->rang++;
		x->parent = y;
	}	
}
void reuneste(Element *x, Element *y)
{
	uneste(search(x), search(y));
}
int cmpfunc(const void * a, const void * b) {
	return (*(int*)a - *(int*)b);
}
int comp(const void* a, const void* b)
{
	 Edge* a1 =  (Edge*)a;
	 Edge* b1 = (Edge*)b;
	return a1->weight > b1->weight;
}
Graf * makeGraf(int V,int E)
{
	Graf *G = (Graf*)malloc(sizeof(Graf));
	G->V=V;
	G->E = E;
	G->edges = new Edge[E];
	return G;
}
void  Kruskal(Graf *G)
{	
	int e,i;
	

	Edge *rezult = (Edge*)malloc(G->E*sizeof(Edge));

	Element **elements = (Element**)malloc(G->V*sizeof(Element*));
	for (int i = 0; i < G->V; i++)
	{
		elements[i] = make_set(G->edges[i].init);
	}
	qsort(G->edges, G->E, sizeof(G->edges[0]), comp);
	int k = -1;
	for (i = 0; i < G->V-1; i++)
	{
		int j = i + 1;
		Element *x = search(elements[i]);
		Element *y = search(elements[j]);
		if (x != y)
		{
			rezult[++k] = G->edges[i];
			uneste(elements[i], elements[j]);
		}
	}
	for (i = 0; i < G->V-1; i++)
	{
		printf("\n%d %d %d", rezult[i].init, rezult[i].fin, rezult[i].weight);
	}
	
}
void demo()
{
	Element *e1 = make_set(1);
	Element *e2 = make_set(2);
	Element *e3 = make_set(3);
	Element *e4 = make_set(4);
	reuneste(e1, e2);
	reuneste(e3, e4);
	reuneste(e3, e2);
	printf("Dupa reuniunea multimelor:\n");
	printf("Parintele elementului %d este %d\n",e3->key, e3->parent->key);
	printf("Parintele elementului %d este %d\n", e3->parent->key,e3->parent->parent->key);
	printf("Parintele elementului %d este %d\n",e1->key, e1->parent->key);
	if (search(make_set(555)) != NULL)
		printf("Elementul a fost gasit");
	else
		printf("Nu a fost gasit");
	Graf *G = makeGraf(6, 7);
	G->edges[0].init = 0;
	G->edges[0].fin =1;
	G->edges[0].weight = 3;
	G->edges[1].init =1;
	G->edges[1].fin =2;
	G->edges[1].weight = 5;
	G->edges[2].init =1;
	G->edges[2].fin = 3;
	G->edges[2].weight = 4;
	G->edges[3].init = 2;
	G->edges[3].fin = 3;
	G->edges[3].weight = 2;
	G->edges[4].init = 3;
	G->edges[4].fin = 4;
	G->edges[4].weight = 7;
	G->edges[5].init =3;
	G->edges[5].fin = 5;
	G->edges[5].weight = 1;
	G->edges[6].init = 4;
	G->edges[6].fin = 5;
	G->edges[6].weight = 8;
	
	Kruskal(G);
	

	

	


}
int main()
{
	demo();
	return 0;
}
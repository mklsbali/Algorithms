#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"
Profiler p("DFS");
/*Miklos Balazs
Grupa 30224*/

/*Observatii finale:
-timpul de descoperire ale ului nod e intotdeauna mai mic decat timpul de finalizare
-eficienta lui DFS este lineara dupa graficoane
*/
//structura unei muchie
typedef struct node
{
	int init, fin;

	struct node *next;

}NodeG;
//Enumerarea culorii
enum{White,Gray,Black};
//Sructura grafului
typedef struct
{
	int V, E;
	int *decoperit;
	int *terminat;
	NodeG **nodes;
}Graf;
typedef struct nodeL
{
	int key;
	struct nodeL *next;
}List;
//Functia care faace insert first muchiile grafului la o lista de adiacenta
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
//Functia pentru a aloca memorie grafului
Graf * makeGraf(int V, int E)
{
	Graf *G = (Graf*)malloc(sizeof(Graf));
	G->E = E;
	G->V = V;
	G->nodes = (NodeG**)malloc(G->V*sizeof(NodeG*));
	for (int i = 0; i < G->V; i++)
	{
		G->nodes[i] = (NodeG*)malloc(sizeof(NodeG));
		G->nodes[i]->init = i;
		G->nodes[i]->fin = -1;
		G->nodes[i]->next = NULL;

	}
	G->decoperit = (int*)calloc(G->V,sizeof(int));
	G->terminat = (int*)calloc(G->V,sizeof(int));
	return G;
}
//Functia cautare in adancime penntru o componenta conexa
void dfs(int nod, Graf *G, int *vizitate, int *parinte, Operation op, int *time)
{
	
	op.count();
	(*time)++;
	G->decoperit[nod] = *time;
	printf(" %d", nod);
	vizitate[nod] = Gray;
	NodeG *aux;
	for (aux = G->nodes[nod]; aux != NULL;aux=aux->next)
	{
		op.count();
		if (vizitate[aux->fin]==White)
		{
			parinte[aux->fin] = nod;
			dfs(aux->fin, G,vizitate,parinte,op,time);
		}
	}
	vizitate[nod] = Black;
	(*time)++;
	G->terminat[nod] = *time;


}

void dfs_all(Graf *G, int * vizitate,int *parinte,Operation op)
{
	int i, time = 0;
	for (int i = 0; i < G->V; i++)
	{
		vizitate[i] = White;
		parinte[i] = -1;

	}
	for (i = 0; i < G->V; i++)
	{
		if (vizitate[i] == White)
			dfs(i,G, vizitate,parinte,op,&time);
	}
}

void printGraf(Graf  G)
{
	printf("Graful arata in felul urmator:\n");
	for (int i = 0; i < G.V; i++)
	{
		if (G.nodes[i] != NULL)
		{
			printf("%d ", G.nodes[i]->init);
			NodeG *current = G.nodes[i];
			while (current->fin != -1)
			{
				printf("-->%d ", current->fin);
				current = current->next;
			}
			printf("\n");
		}
	
	}
	printf("\n");
}
//functia care verifica daca doua varfuri sunt adiacente
int isAdiacent(Graf G, int a, int b)
{
	NodeG *current = G.nodes[a];
	while (current != NULL)
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
				i++;
			}
		}
	}
	return G;

}
void insert_first(List **list, int key)
{
	List *neww = (List*)malloc(sizeof(List));
	neww->key = key;
	neww->next = NULL;
	if (*list == NULL)
		*list = neww;
	else
	{
		neww->next = *list;
		*list = neww;
	}
}
void dfs_topologic_sort(int nod, Graf *G, int *vizitate, int *time, List **list)
{

	(*time)++;
	G->decoperit[nod] = *time;
	//printf(" %d", nod);
	vizitate[nod] = Gray;
	NodeG *aux;
	for (aux = G->nodes[nod]; aux != NULL; aux = aux->next)
	{
		if (vizitate[aux->fin] == White)
		{
			dfs_topologic_sort(aux->fin, G, vizitate, time, list);
		}
	}
	vizitate[nod] = Black;
	insert_first(list, nod);
	(*time)++;
	G->terminat[nod] = *time;


}

void dfs_all_topologic_sort(Graf *G, int * vizitate, List**list)
{
	int i, time = 0;
	for (i = 0; i < G->V; i++)
	{
		if (vizitate[i] == White)
			dfs_topologic_sort(i, G, vizitate, &time, list);
	}
}
//Functia topologic sosrt
List* topologicalSort(Graf* G)
{
	List* list = NULL;
	int *vizitate = (int*)calloc(G->V, sizeof(int));
	dfs_all_topologic_sort(G, vizitate, &list);
	return list;
}
void demo()
{
	Graf *G = makeGraf(7, 7);
	insert(G, 0, 1);
	insert(G, 0, 2);
	insert(G, 1, 2);
	insert(G, 1, 4);
	insert(G, 2, 3);
	insert(G, 3, 4);
	insert(G, 5, 6);

	Operation op = p.createOperation("operatii", 10);
	printGraf(*G);
	printf("\n");
	int*vizitate = (int*)malloc(G->V*sizeof(int));
	int*parinte = (int*)malloc(G->V*sizeof(int));
	printf("Ordinea nodurilor dupa DFS:\n");
	dfs_all(G,vizitate,parinte,op);
	printf("\nVectorul de parinte:"); int i;
	printf("\n");
	for (i = 0; i < G->V; i++)
	{
		printf("%d ", parinte[i]);

	}
	printf("\nTimpii de descoperire:\n");
	for (i = 0; i < G->V; i++)
	{

		printf("%d ", G->decoperit[i]);

	}
	printf("\nTimpii de finalizare:\n");
	for (i = 0; i < G->V; i++)
	{
	
	printf("%d ", G->terminat[i]);
	}
	List *sorted = topologicalSort(G);
	printf("\nDupa inserarea nodurilor intr-o lista cu sortare topologica:\n");
	while (sorted != NULL)
	{
		printf("%d ", sorted->key);
		sorted = sorted->next;
	}

}
//functia unde nr muchiilor varieaza
void performE()
{

	int n;
	for (n = 1000; n <= 4500; n += 100)
	{
		Operation op = p.createOperation("V constant", n);
		Graf *G = createGraf(100, n);
		int vizitate[100];
		int parinte[100];
		dfs_all(G,vizitate,parinte,op);
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
		int *vizitate = (int*)malloc(n*sizeof(int));
		int *parinte = (int*)malloc(n*sizeof(int));
		dfs_all(G, vizitate, parinte, op);
	}
	p.showReport();
}

int main()
{
	//demo();
	performE();
	//performV();
	
	return 0;
}
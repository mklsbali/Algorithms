#include <stdio.h>
#include "stdafx.h"
#include <string.h>
#include "Profiler.h"
#include <stdlib.h>
#include <time.h>
Profiler p("lab5");
typedef struct node
{
	int key;
	struct node *next;
}NodeT;
int dim;
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
// functia care returneaza ca unde este parintele elementului pe pozitia i si returneaza 
int parinte(int i)
{
	return i / 2;
}
// functia care returneaza ca unde este copilul stang elementului pe pozitia i 
int stanga(int i)
{
	return 2 * i;
}
// functia care returneaza ca unde este copilul drept elementului pe pozitia i  
int dreapta(int i)
{
	return 2 * i + 1;
}
void init_heap()
{
	dim = 0;
}
void reconst_heap(int v[], int i, int n)
{
	Operation op1 = p.createOperation("Bottom_up_comp", n);
	Operation op2 = p.createOperation("Bottom_up_assign", n);
	int max;
	int l = stanga(i);
	int r = dreapta(i);
	if (l <n)
	{
		op1.count();
		if (v[l] > v[i])
		{
			max = l;
		}
		else
		{
			max = i;
		}
	}
	else{
		max = i;
	}
	if (r < n)
	{
		op1.count();
		if (v[r] > v[max])
		{
			max = r;
		}
	}
	if (max != i)
	{
		op2.count(3);
		swap(&v[i], &v[max]);
		reconst_heap(v, max, n);
	}
}

void Hpush(int v[], int key, int k)
{
	Operation op1 = p.createOperation("Top_down_comp", k);
	Operation op2 = p.createOperation("Top_down_assign", k);
	dim++;
	int i = dim;
	op1.count();
	while (i > 0 && v[parinte(i)] < key)
	{
		op1.count();
		op2.count(1);
		v[i] = v[parinte(i)];
		i = parinte(i);
	}
	op2.count();
	v[i] = key;
}
int Hpop(int v[],int k)
{
	int x = v[0];
	v[0] = v[dim];
	dim--;
	reconst_heap(v, 0, k);
	return x;

}
//functia care construieste un heap dintrun vector dat


void insert_ordered(NodeT **head, int key)
{

	NodeT *neww = (NodeT*)malloc(sizeof(NodeT));
	neww->key = key;
	neww->next = NULL;
	if (*head == NULL)
	{
		*head = neww;
	}
	else if (key <=(*head)->key)
	{
		neww->next = *head;
		*head = neww;

	}
	else
	{
		NodeT *current = *head;
		NodeT *prev = NULL;
		if (current->next == NULL)
		{
			current->next = neww;
			return;
		}
		while (key > current->key)
		{
			if (current->next == NULL)
				break;
			prev = current;
			current = current->next;
		}
		if (current->next == NULL && key>=current->key)
			current->next = neww;
		else
		{
			prev->next = neww;
			neww->next = current;
		}
			
	}
}
NodeT  * readL(NodeT *list)
{
	NodeT *current = list;
	if (current != NULL)
	{
		list = list->next;
		return current;
	}
}
void print_lists(NodeT *head[],int k)
{
	for (int i = 0; i < k; i++)
	{
		NodeT *current = head[i];
		while (current!= NULL)
		{
			printf(" %d", current->key);
			current = current->next;
		}
		printf("\n");
	}
	
} //2 3 4

void interclasare_k_liste(NodeT *Lists[], NodeT *output, int k, int n)
{
	dim = 0;
	NodeT *p;
	int i;
	int v[3];
	for (i = 0; i < k; i++)
	{
		v[i] = Lists[i]->key;
		
	}
	for (i = 0; i < k; i++)
	{
		p = readL(Lists[i]);
		if (p != NULL)
		{
			Hpush(v, p->key, k);
		}
			
	}
	
	while (dim > 0)
	{
		p->key = Hpop(v, k);
		insert_ordered(&output, p->key);
			p = readL(Lists[i]);
			if (p != NULL)
			{
				Hpush(v, p->key, k);
			}

		}

}

void demo()
{
	NodeT *head[3];
	NodeT *output = NULL;
	int i,j;
	for ( i = 0; i < 3; i++)
		head[i] = NULL;
	int n = 9;
	int k = 3;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < n / 3; j++)
			insert_ordered(&head[i], rand() % 5000 + 1);
	}

	print_lists(head, 3);
	
	//interclasare_k_liste(head, output, k, n);



		


}
int main()
{
	
	demo();
	return 0;
}
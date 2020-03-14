/*Miklós Balázs
Grupa 30224

Observatia finala:
Metoda bottom up e mai eficient decat top down in teorie. Dar la mine graficonul arata ca eficienta e invers in cazul avg.
In cazul worst top down e mai eficient, top  down face aproape de doua ori mai multe operatii decat bottom up.


*/



#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include "Profiler.h"
#include <string.h>
Profiler p("lab2");
//initial setez dimensiunea heapului la 0
int dim;
// functia care insterschimba intre ele doua elemente
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
// functia care returneaza ca unde este copilul stang elementului pe pozitia i si returneaza 
int stanga(int i)
{
	return 2 * i;
}
// functia care returneaza ca unde este copilul drept elementului pe pozitia i si returneaza 
int dreapta(int i)
{
	return 2 * i + 1;
}
//functia care afiseaza elementele a unui vector de n elemente 
void print(int v[], int n)
{
	for (int i = 0; i < n; i++)
	{
		printf(" %d", v[i]);
	}
	printf("\n");
}
//functia care reconstruieste un heap ca aceasta sa pastreze structura heapului
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
//functia care construieste un heap dintrun vector dat
void const_heap_bottom_up(int v[], int n)
{
	for (int i = n / 2; i >= 0; i--)
	{
		reconst_heap(v, i, n);
	}
}
//functia care insereaza in heap in mod top-down astfel ca si pastreze constructia heapului
void insert_heap(int v[], int key, int n)
{
	Operation op1 = p.createOperation("Top_down_comp", n);
	Operation op2 = p.createOperation("Top_down_assign", n);
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
//functia care insereaza reface un vector la un heap
void constt_heap_top_down(int v[], int n)
{
	dim = 0;
	for (int i = 1; i < n; i++)
	{
		insert_heap(v, v[i], n);
	}
}
//functia heapsort care sorteaza elementele a unui vector
void heapsort(int v[], int n)
{
	const_heap_bottom_up(v, n);
	for (int i = n-1; i >= 1; i--)
	{
		swap(&v[0], &v[i]);
		n = n - 1;
		reconst_heap(v, 0, n);
	}

}

//functia demo care arata corectitudinea algoritmilor 
void demo()
{
	int v[] = { 1,2,3,4,5,6,7,8,9,10};

	int u[100], heap[100];
	memcpy(u, v, sizeof(v));
	int n = sizeof(v) / sizeof(v[0]);
	print(v, n);
	const_heap_bottom_up(u, n);
	printf("Heapul MAX construit cu bottom up metod arata asa:\n");
	print(u, n);
	heapsort(u, n);
	printf("Vecrotul sortat cu heapsort:\n");
	print(u, n);
	memcpy(u, v, sizeof(v));
	constt_heap_top_down(u, n);
	printf("Heapul MIN construit cu top down metod arata asa:\n");
	print(u, n);

}
/* Functia avg compara in cazul mediu statistic numarul de operatii dintre top down si bottom up metods avand in vedere numarul
operatiilor facut de ele*/ 
void avg()
{
	int v[10001], u[10001], n;
	for (n = 100; n <= 10000; n += 100)
	{
		FillRandomArray(v, n);
		memcpy(u, v, n*sizeof(v[0]));
		const_heap_bottom_up(u, n );
		memcpy(u, v, n*sizeof(v[0]));
		constt_heap_top_down(u, n);
	}
	p.addSeries("Bottom_up", "Bottom_up_comp", "Bottom_up_assign");
	p.addSeries("Top_down", "Top_down_comp", "Top_down_assign");

	p.createGroup("Comparatii", "Bottom_up_comp", "Top_down_comp");
	p.createGroup("Assignari", "Bottom_up_assign", "Top_down_assign");
	p.createGroup("Total", "Bottom_up", "Top_down");

	p.showReport();
}
//Cazul ce mai rau unde vectorul original e sortat crescator in cazul in care construim max heap, descrescator in min heap
void worst()
{
	int v[10001], u[10001], n;
	for (n = 100; n <= 10000; n += 100)
	{
		FillRandomArray(v, n, 10, 50000, false, 1);
		memcpy(u, v, n*sizeof(v[0]));
		const_heap_bottom_up(u, n);
		memcpy(u, v, n*sizeof(v[0]));
		constt_heap_top_down(u, n);
	}
	p.addSeries("Bottom_up", "Bottom_up_comp", "Bottom_up_assign");
	p.addSeries("Top_down", "Top_down_comp", "Top_down_assign");

	p.createGroup("Comparatii", "Bottom_up_comp", "Top_down_comp");
	p.createGroup("Assignari", "Bottom_up_assign", "Top_down_assign");
	p.createGroup("Total", "Bottom_up", "Top_down");

	p.showReport();
}
//In main putem alegem in ce optiune vrem sa vedem rezultatul
int main()
{
	//demo();
	//avg();
	worst();
	return 0;

}
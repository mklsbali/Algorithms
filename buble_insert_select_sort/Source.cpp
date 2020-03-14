/*Miklós Balázs
Grupa 30224
Analiza sortarilor bubble, insertion si selection*/


/*Observatiile finale:
	Cazul avg: 
	-Buble sort face cele mai multe asignare, dupa ce urmeaza insertion sort, selection sort este ultimul
	-Numarul comparatiilor este acelasi la bubble si la selection sort dupa ce urmeaza insertion sort
	-In total cele mai multe operatii face buble sort, selection si insertion sort face aproape acelasi numar de operatii, dar
	insertion e un pic mai eficient
	Cazul worst:
	-Cel mai eficient e selection sort privind numarul asignarilor, dupa ce insertion respectiv bubble sort
	-Numarul comparatiilor este aproape acelasi la cele trei sortari
	-In total cel mai eficient este selection sort, dupa ce urmeaza insertion sort si in final bubble sort
	Cazul best:
	-Bubble sort nu face nici-o asignare, insertion sort face putin dar selection sort face mult
	-Bubble si selection sort fac acelasi numar de comparatii, cele mai putine comparatii face insertion sort care exact face n-1 comparatii,
	unde n e dimensiunea vectorului
	-In cazul aceasta insertion sort e ceal mai eficient, iar bubble sort e un pic mai eficient decat selection sort
	
*/


#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include "Profiler.h"
Profiler p("lab1");
//Functia swap care interschimba intre ele doua elemente
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
//Soartare cu bile
void bubble_sort(int v[], int n)
{
	Operation op1 = p.createOperation("buble_comp", n);
	Operation op2 = p.createOperation("buble_assign", n);
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = n - 1; j >= i + 1; j--)
		{
			op1.count();
			if (v[j] < v[j - 1])
			{
				op2.count(3);
				swap(&v[j], &v[j - 1]);
			}
		}
	}
}
//Sortare prin inserare
void insert_sort(int v[], int n)
{
	Operation op1 = p.createOperation("insert_comp", n);
	Operation op2 = p.createOperation("insert_assign", n);
	int i, j;
	for (i = 1; i <n; i++)
	{
		op2.count(1);
		int key = v[i];
		
		j = i - 1;
		op1.count(1);

		while (j >= 0 && v[j] > key)
		{
			op1.count(1);
			op2.count(1);
			v[j + 1] = v[j];
			j = j - 1;
		}
		op2.count(1);
		v[j + 1] = key;
	}
}
//Sortare prin selectie
void selection_sort(int v[], int n)
{
	Operation op1 = p.createOperation("select_comp", n);
	Operation op2 = p.createOperation("select_assign", n);
	int i, j, min;
	for (i = 0; i < n - 1; i++)
	{
		min = i;
		for (j = i + 1; j < n; j++)
		{
			op1.count();
			if (v[j] < v[min])
			{
				min = j;
			}
			
		}
		op2.count(3);
		swap(&v[min], &v[i]);
	}

}
//Functia care afiseaza un vector de n elemente de la primul pana la ultimul element
void print(int v[], int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", v[i]);
	}
	printf("\n");
}
//Functia demo care arata corectitudinea algoritmilor de sortare
void demo()
{
	int v[] = { 7, 2, 5, 3, 9, 8, 1 };
	int n = sizeof(v) / sizeof(v[0]);
	int p[100];
	memcpy(p, v, sizeof(v));
	bubble_sort(p, n);
	print(p, n);
	memcpy(p, v, sizeof(v));
	insert_sort(p, n);
	print(p, n);
	memcpy(p, v, sizeof(v));
	selection_sort(p, n);
	print(p, n);

}
//Functia care face graficonul daca vectorul este sortat aleator, "avarage case"
void avg()
{
	int v[10000], u[10000], n;
	for (n = 100; n <= 10000; n += 100)
	{
		FillRandomArray(v, n);
		memcpy(u, v, n*sizeof(v[0]));
		bubble_sort(u, n);
		memcpy(u, v, n*sizeof(v[0]));
		insert_sort(u, n);
		memcpy(u, v, n*sizeof(v[0]));
		selection_sort(u, n);
		
	}


	p.addSeries("buble", "buble_comp", "buble_assign");
	p.addSeries("insert", "insert_comp", "insert_assign");
	p.addSeries("select", "select_comp", "select_assign");

	p.createGroup("Comparatii", "buble_comp", "insert_comp", "select_comp");
	p.createGroup("Asignari", "buble_assign", "insert_assign", "select_assign");
	p.createGroup("In total", "buble", "insert", "select");

	p.showReport();
	
	
}
//Functia care arata graficonul in cazul in care vectorul e sortat crescator cu elemente aleatoare, adica in cazul "best caze"
void best() {
	int v[10000], u[10000];
	int n;
	for (n = 100; n <= 10000; n += 100)
	{
		FillRandomArray(v, n, 10, 50000, false, 1);
		memcpy(u, v, n * sizeof(v[0]));
		bubble_sort(u, n);
		memcpy(u, v, n * sizeof(v[0]));
		insert_sort(u, n);
		memcpy(u, v, n * sizeof(v[0]));
		selection_sort(u, n);

	}
	p.addSeries("buble", "buble_comp", "buble_assign");
	p.addSeries("insert", "insert_comp", "insert_assign");
	p.addSeries("select", "select_comp", "select_assign");

	p.createGroup("Comparatii", "buble_comp", "insert_comp", "select_comp");
	p.createGroup("Asignari", "buble_assign", "insert_assign", "select_assign");
	p.createGroup("In total", "buble", "insert", "select");

	p.showReport();
}
//Functia care arata graficonul unde vectorul e sortat descrescator cu elemente aleatoare, cazul "worst case"
void worst() {
	int v[10000], u[10000];
	int n;
	for (n = 100; n <= 10000; n += 100)
	{
		FillRandomArray(v, n, 10, 50000, false, 2);
		memcpy(u, v, n * sizeof(v[0]));
		bubble_sort(u, n);
		memcpy(u, v, n * sizeof(v[0]));
		insert_sort(u, n);
		memcpy(u, v, n * sizeof(v[0]));
		selection_sort(u, n);

	}
	p.addSeries("buble", "buble_comp", "buble_assign");
	p.addSeries("insert", "insert_comp", "insert_assign");
	p.addSeries("select", "select_comp", "select_assign");

	p.createGroup("Comparatii", "buble_comp", "insert_comp", "select_comp");
	p.createGroup("Asignari", "buble_assign", "insert_assign", "select_assign");
	p.createGroup("In total", "buble", "insert", "select");

	p.showReport();
}
//In functia main putem alegem in ce optiune vrem sa vedem rezultatul sortarilor 
int main()
{
	//demo();
	//avg();
	//worst();
	best();
	return 0;
}

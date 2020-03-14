/*Miklós Balázs, grupa 30214
Observatiile finale:
-nr total de operatii in cazul avg la heapsort:657903
-nr total de operatii in cazul avg la quicksort:448491
-Deci in cazul avg quicksort este mai eficient
-Numarul operatiilor la quicksort in cele 5 graficoane in cazul avg difera mai mult la quicksort decat la heapsort
-In cazurile best si avg cazuri quicksort e mai eficient decat heapsort, in cazul worst invers.
-In cazul worst quicksort e foarte ineficient pentru vector de lungime 10000 face mai mult decat 100000000 operatii deci eficienta e un 
pic mai mare decan O(n patrat).
-In cazul best si avg quicksort face aproape acelasi numar de operatii
*/
#include <stdio.h>
#include "stdafx.h"
#include <string.h>
#include "Profiler.h"
#include <stdlib.h>
#include <time.h>
Profiler p("lab3");
int dim;
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
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

//functia care reconstruieste un heap ca aceasta sa pastreze structura heapului
void reconst_heap(int v[], int i, int n)
{
	Operation op1 = p.createOperation("Heapsort_comp", dim);
	Operation op2 = p.createOperation("Heapsort_assign", dim);
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
	dim = n;
	for (int i = n / 2; i >= 0; i--)
	{
		reconst_heap(v, i, n);
	}
}
//functia heapsort care sorteaza elementele a unui vector
void heapsort(int v[], int n)
{
	Operation op2 = p.createOperation("Heapsort_assign", n);
	const_heap_bottom_up(v, n);
	for (int i = n - 1; i >= 1; i--)
	{
		op2.count(3);
		swap(&v[0], &v[i]);
		
		reconst_heap(v, 0,i);
	}

}
//Functia care printeaza fiecare element a unui vector
void print(int v[], int n)
{
	for (int i = 0; i < n; i++)
	{
		printf(" %d", v[i]);
	}
	printf("\n");
}


//Partitionare cand pivotul e ultimul element
int partition(int v[], int low, int high)
{
	Operation op1 = p.createOperation("Quick_comp", dim);
	Operation op2 = p.createOperation("Quick_assign", dim);

	op2.count();
	int pivot = v[high];
	int i = low - 1;
	for (int j = low; j < high; j++)
	{
		op1.count();
		if (v[j] <= pivot)
		{
			i++;
			op2.count(3);
			swap(&v[j], &v[i]);
		}
	}
	op2.count(3);
	swap(&v[i + 1], &v[high]);
	return i + 1;

}
//Functia quicksort cand pivotul e ultimul element
void quicksort(int v[], int low, int high)
{
	if (low < high)
	{
		int q = partition(v, low, high);
		quicksort(v, low, q - 1);
		quicksort(v, q + 1, high);
	}
}
//Fanctiile de sortare in care pivotul e un element random in array
int randomized_partition(int v[],int low,int high)
{
	Operation op2 = p.createOperation("Quick_assign", dim);
	int i = low+rand() % (high - low + 1);
	op2.count(3);
	swap(&v[high], &v[i]);
	return partition(v, low, high);
}
void randomized_quicksort(int v[], int low, int high)
{
	if (low < high)
	{
		int q = randomized_partition(v, low, high);
		randomized_quicksort(v, low, q - 1);
		randomized_quicksort(v, q + 1, high);
	}
}
//Functia care cauta al i-lea cel mai mic sau cel mai mare element in vectorul
int  randomized_select(int v[],int low,int high,int i)
{
	if (low == high)
		return v[low];
	int q = randomized_partition(v, low, high);
	int k = q - low + 1;
	if (i == k)
		return v[q];
	else if (i < k)
		return randomized_select(v, low, q - 1, i);
	else
		return randomized_select(v, q + 1,high, i-k);
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
		heapsort(u, n);
		memcpy(u, v, n*sizeof(v[0]));
		quicksort(u, 0, n - 1);
	}
	p.addSeries("Heapsort", "Heapsort_comp", "Heapsort_assign");
	p.addSeries("Quicksort", "Quick_comp", "Quick_assign");
	p.createGroup("Comparatii", "Quick_comp", "Heapsort_comp");
	p.createGroup("Asignari", "Quick_assign", "Heapsort_assign");
	p.createGroup("In total", "Quicksort", "Heapsort");
	p.showReport();
}
//Testarea sortarilor in cazul in care vectorul mare este sortat descrescator
void worst()
{
	int v[10001], u[10001], n;
	for (n = 100; n <= 10000; n += 100)
	{
		FillRandomArray(v, n, 10, 50000, false, 2);
		memcpy(u, v, n*sizeof(v[0]));
		heapsort(u, n);
		memcpy(u, v, n*sizeof(v[0]));
		quicksort(u, 0, n - 1);
	}
	p.addSeries("Heapsort", "Heapsort_comp", "Heapsort_assign");
	p.addSeries("Quicksort", "Quick_comp", "Quick_assign");
	p.createGroup("Comparatii", "Quick_comp", "Heapsort_comp");
	p.createGroup("Asignari", "Quick_assign", "Heapsort_assign");
	p.createGroup("In total", "Quicksort", "Heapsort");
	p.showReport();
}
//Testarea sortarilor in cazul in care vectorul mare este sortat crescator
void best()
{
	int v[10001], u[10001], n;
	for (n = 100; n <= 10000; n += 100)
	{
		FillRandomArray(v, n, 10, 50000, false, 1);
		memcpy(u, v, n*sizeof(v[0]));
		heapsort(u, n);
		memcpy(u, v, n*sizeof(v[0]));
		randomized_quicksort(u, 0, n - 1);
	}
	p.addSeries("Heapsort", "Heapsort_comp", "Heapsort_assign");
	p.addSeries("Quicksort", "Quick_comp", "Quick_assign");
	p.createGroup("Comparatii", "Quick_comp", "Heapsort_comp");
	p.createGroup("Asignari", "Quick_assign", "Heapsort_assign");
	p.createGroup("In total", "Quicksort", "Heapsort");
	p.showReport();
}
//Functia demo care arata corectitudinea algoritmilor
void demo()
{
	int v[] = {77,4,8,5,66,2,554,3,49}, u[100];
	memcpy(u, v, sizeof(v));
	int n = sizeof(v) / sizeof(v[0]);
	printf("Vectorul original:\n");
	print(v, n);
	heapsort(u, n);
	printf("Vecrotul sortat cu heapsort:\n");
	print(u, n);
	memcpy(u, v, sizeof(v));
	quicksort(u, 0, n-1);
	printf("Vectorul sortat cu quicksort:\n");
	print(u, n);
	memcpy(u, v, sizeof(v));
	randomized_quicksort(u, 0, n - 1);
	printf("Vectorul sortat cu randomized_quicksort:\n");
	print(u, n);
	printf("\Vectorul sortat  cu qucik_select:\n");
	for (int i = 1; i <= n;i++)
		printf( " %d", randomized_select(v, 0, n - 1, i));
	

}
//In main pot sa aleg ce optiune vreau sa testez
int main()
{
//	demo();
	//avg();
	worst();
///	best();
	return 0;
	
}
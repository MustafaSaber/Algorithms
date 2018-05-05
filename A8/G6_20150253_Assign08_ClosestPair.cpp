// G6_20150253_Assign08_ClosestPair.cpp : Defines the entry point for the console application.
//

// GROUP:   X
// ID:      20150253
// Assign:  08
// Assign:  ClosetsPair
// UVA:     10245
// Name1:   Mostafa Saber
// Name2:   XX SECOND STUDENT FULL NAME
// UVA Username: yasou

#include "stdafx.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>     // please use the built-in sqrt() function
using namespace std;

#define INF 10000

template <class value>
struct Array
{
	int n, size;
	value* arr;
	void Initialize() { size = 1, n = 0, arr = new value[size]; }
	void Destroy() { delete[] arr; }
	void AddLast(value v)
	{
		if (n == size)
		{
			size *= 2;
			value* new_arr = new value[size];
			for (int i = 0; i < n; i++)
				new_arr[i] = arr[i];
			delete[] arr;
			arr = new_arr;
		}
		arr[n++] = v;
	}
	void RemoveLast() { n--; }
	value& operator[] (int i) { return arr[i]; }
	void Print()
	{
		for (int i = 0; i < n; i++)
			cout << arr[i] << " ";
		cout << endl;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
void Merge(Type* a, int n, bool(*IsBefore)(Type& a, Type& b))
{
	int mid = n / 2;
	int i = 0, j = mid;
	Type* t = new Type[n];

	for (int k = 0; k < n; k++)
	{
		if (j == n || (i < mid && IsBefore(a[i], a[j])))
			t[k] = a[i++];
		else t[k] = a[j++];
	}
	for (i = 0; i < n; i++) a[i] = t[i];
	delete[] t;
}

template<class Type>
void MergeSort(Type* a, int n, bool(*IsBefore)(Type& a, Type& b)) 
{
	int mid = n / 2;
	if (n <= 1) return;
	MergeSort(a, mid, IsBefore);
	MergeSort(a + mid, n - mid, IsBefore);
	Merge(a, n, IsBefore);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Point
{
	double x, y;
};

bool IsBeforeX(Point& a, Point& b) { return a.x < b.x; }
bool IsBeforeY(Point& a, Point& b) { return a.y < b.y; }

double dist(Point& a, Point& b)
{
	return sqrt(((a.x-b.x)*(a.x - b.x)) + ((a.y-b.y)*(a.y-b.y)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////


Point arr[10001];


double bruteforce(Point* p, int n , double mindist)
{
	for(int i = 0 ; i < n; i++)
		for (int j = i+1 ; j < n; j++)
		{
			double m = dist(p[i], p[j]);
			if (m < mindist)
				mindist = m;
		}

	return mindist;
}


// Sort the points p according to x before calling this function
double ClosestPair(Point* p, int n)
{
	Array<Point> f;
	f.Initialize();
	int mid = n / 2;
	if (n <= 3)
	{
		Merge(p, n, IsBeforeY);
		for (int i = 0; i < n; i++) f.AddLast(p[i]);
		return bruteforce(f.arr, f.n, INF);
	}
	double a = ClosestPair(p, mid);
	double b = ClosestPair(p + mid, n - mid);

	double m; m = (a <= b) ? a : b;

	Merge(p, n, IsBeforeY);

	double axis = (p[mid-1].x + p[mid].x) / 2;
	
	for (int i = 0; i < n; i++) if (p[i].x>axis - m && p[i].x<axis + m) f.AddLast(p[i]);

	double InBet = bruteforce(f.arr, f.n , m );
	f.Destroy();
	return (InBet <= m) ? InBet : m;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n;
	while (cin >> n && n)
	{
		for (int i = 0; i < n; i++) cin >> arr[i].x >> arr[i].y;
		MergeSort(arr, n, IsBeforeX);
		double ans = ClosestPair(arr, n);
		if(ans < INF) printf("%.4lf\n", ans);
		else puts("INFINITY");
	}
	return 0;
}

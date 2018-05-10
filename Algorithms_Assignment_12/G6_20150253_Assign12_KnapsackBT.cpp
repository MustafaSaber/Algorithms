// G6_20150253_Assign12_KnapsackBT.cpp : Defines the entry point for the console application.
//

// GROUP:   6
// ID:      20150253
// Assign:  12
// Assign:  KnapsackBT
// UVA:     10130
// Name:    Mostafa Saber
// UVA Username: yasou

#include "stdafx.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

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
		else { t[k] = a[j++]; }
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

struct Obj
{
	int v;
	int w;
};

int n;       // number of objects (input)
Obj a[1000]; // objects (input)
int T, P, W, G, GW;
////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBefore(Obj& a, Obj& b) // return true if unit value of a is greater than unit value of b
{
	return ( ((double)a.v / (double)a.w ) > ((double)b.v / b.w) );
}
							   ////////////////////////////////////////////////////////////////////////////////////////////////////////////

int best_val; // the best total value found until now

int Bound(int i, int w) // upper bound on the total value of items [i..n-1] that can fit in w
{
	int tempw = 0;
	int optimalAns = 0;
	for (int j = i; j < n; j++)
	{
		if (tempw + a[j].w <= w)
		{
			tempw += a[j].w;
			optimalAns += a[j].v;
		}
		else
		{
			optimalAns +=  ((double)a[j].v / (double)a[j].w) * (w - tempw);
			return optimalAns;
		}
	}
	return optimalAns;
}
void BackTrack(int i, int w, int cur_val) // starting from item i, remaining weight w, cur_value of objects[0..i-1]
{
	if (i == n)
	{
		if (cur_val > best_val)
			best_val = cur_val;
		return;
	}

	int b = Bound(i, w);

	if (cur_val + b <= best_val) return;

	if (a[i].w <= w)
		BackTrack(i + 1, w - a[i].w, cur_val + a[i].v);

	BackTrack(i + 1, w, cur_val);

}
int ComputeKnapsack(int N, int W) // solve knapsack of N objects and W weight
{
	best_val = 0;
	BackTrack(0, W , 0);
	return best_val;
}
void Compute()
{
	int total;
	cin >> T;
	while (T--)
	{
		total = 0;
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cin >> P >> W;
			a[i].v = P, a[i].w = W;
		}
		MergeSort(a, n, IsBefore);
		cin >> G;
		for (int i = 0; i < G; i++)
		{
			cin >> GW;
			total += ComputeKnapsack(n, GW);
		}
		cout << total << endl;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	freopen("input_assign12_10130.txt", "r", stdin);
	freopen("ouput_assign12_10130.txt", "w", stdout);
	Compute();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

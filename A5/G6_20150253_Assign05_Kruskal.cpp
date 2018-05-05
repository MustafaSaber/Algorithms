// G6_20150253_Assign05_Kruskal.cpp : Defines the entry point for the console application.
//
// GROUP:   6
// ID:      20150253
// Assign:  05
// Assign:  Kruskal
// UVA:     11631
// Name:    Mostafa Saber
// UVA UserName: yasou


#include "stdafx.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DisjointSet
{
	int n;
	int* parent;
	int* num_nodes;

	void Initialize(int _n)
	{
		n = _n;
		parent = new int[_n]; num_nodes = new int[_n];

		for (int i = 0; i < n; i++) parent[i] = -1, num_nodes[i] = 1;
	}

	void Destroy() { delete[] parent; delete[] num_nodes; }

	int Find(int i)
	{
		if (parent[i] == -1) return i;
		Find(parent[i]);
	}

	bool Union(int i, int j)
	{
		int first = Find(i);
		int second = Find(j);
		if (first == second) return false;
		n--;
		if (num_nodes[first] >= num_nodes[second]) { parent[second] = first, num_nodes[first] += num_nodes[second]; }

		else { parent[first] = second; num_nodes[second] += num_nodes[first]; }
		return true;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
	int u, v;
	int w;
};

bool IsBeforeEdge(Edge& a, Edge& b)
{
	return a.w<b.w;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
void Merge(Type* a, int n, bool(*IsBefore)(Type& a, Type& b))
{
	int mid = n / 2;
	int i = 0, j = mid;
	Edge* t = new Edge[n];

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


int solve(int m, int n)
{
	int totalsum = 0;
	DisjointSet myset;
	myset.Initialize(m);
	Edge *alledges = new Edge[n];
	for (int i = 0; i < n; i++)
		cin >> alledges[i].u >> alledges[i].v >> alledges[i].w, totalsum += alledges[i].w;

	MergeSort(alledges, n, IsBeforeEdge);

	int cursum = 0;
	for (int i = 0; i < n; i++)
	{
		if (myset.Union(alledges[i].u, alledges[i].v))
			cursum += alledges[i].w;
	}
	myset.Destroy();
	return totalsum - cursum;
}


int main()
{
	freopen("input.txt", "r", stdin);
	int n, m;
	while (cin >> m >> n && n && m)
	{
		cout << solve(m, n) << endl;
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

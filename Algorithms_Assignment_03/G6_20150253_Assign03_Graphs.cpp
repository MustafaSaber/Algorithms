// G6_20150253_Assign03_Graphs.cpp : Defines the entry point for the console application.
//

// GROUP:		 6
// ID:			 20150253
// Assign:		 03
// Assign:		 Graphs
// UVA:			 924
// UVA username: yasou
// Name:		 Mostafa Saber

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Value>
struct Array
{
	int n, size;
	Value* arr;
	void Initialize() { size = 1, n = 0, arr = new Value[size]; }
	void Destroy() { delete[] arr; }
	void AddLast(Value v)
	{
		if (n == size)
		{
			size *= 2;
			Value* new_arr = new Value[size];
			for (int i = 0; i < n; i++)
				new_arr[i] = arr[i];
			delete[] arr;
			arr = new_arr;
		}
		arr[n++] = v;
	}
	void RemoveLast() { n--; }
	Value& operator[] (int i) { return arr[i]; }
	void Print()
	{
		for (int i = 0; i < n; i++)
			cout << arr[i] << " ";
		cout << endl;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Node
{
	Array<int> adj;

	void Initialize() { adj.Initialize(); }
	void Destroy() { adj.Destroy(); }
};

struct Graph
{
	int n;
	Node* nodes;

	void Initialize(int _n) 
	{
		n = _n , nodes = new Node[n]; 
		for (int i = 0; i < n; i++) nodes[i].Initialize();
	}

	void Destroy() { for (int i = 0; i < n; i++) nodes[i].Destroy(); delete[] nodes; }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Type>
struct Queue
{
	int f, n;
	Type* elems;

	void Initialize(int size)
	{
		n = f = 0;
		elems = new int[size];
	}
	void Destroy()	{ delete[] elems; }
	
	void Add(Type t) { elems[n++] = t; }
	Type Pop() 
	{
		Type t = elems[f];
		f++;  return t;
	}
	Type Peek() { return elems[f]; }
	int Num() { return n - f; }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////


Graph em;
bool vis[2500];

void bfs(int src)
{
	Queue<int> q;
	q.Initialize(2501);
	q.Add(src);
	if (!em.nodes[src].adj.n == 1) { cout << 0 << endl; return; }
	int m = 0, d = 0, coun = 0;

	while (q.Num())
	{
		coun++;
		int tempsize = q.Num();
		while (tempsize--)
		{
			int cur = q.Peek();
			q.Pop();
			if (!vis[cur]) vis[cur] = true;
			for (int i = 0; i < em.nodes[cur].adj.n; i++)
				if (!vis[em.nodes[cur].adj[i]]) { q.Add(em.nodes[cur].adj[i]); vis[em.nodes[cur].adj[i]] = true; }
		}
		if (m < q.Num()) { m = q.Num();  d = coun; }
	}
	cout << m << " " << d << endl;
	q.Destroy();
}


int main()
{
	int e;
	cin >> e;
	em.Initialize(e);
	for (int i = 0; i < e; i++)
	{
		int f;  cin >> f;
		for (int j = 0; j < f; j++)
		{
			int t; cin >> t;
			em.nodes[i].adj.AddLast(t);
		}
	}
	int cases;
	cin >> cases;
	while (cases--)
	{
		memset(vis, 0, sizeof vis);
		int src;
		cin >> src;
		bfs(src);
	}
	em.Destroy();
	return 0;
}


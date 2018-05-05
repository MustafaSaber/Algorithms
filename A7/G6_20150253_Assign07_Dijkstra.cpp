// G6_20150253_Assign07_Dijkstra.cpp : Defines the entry point for the console application.
//

// GROUP:   6
// ID:      20150253
// Assign:  07
// Assign:  Dijkstra
// UVA:     10986
// Name1:   Mostafa Saber
// Name2:   Mohamed Samy
// UVA Username: yasou


#include "stdafx.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include<algorithm>
using namespace std;

#define INF (1<<30)

////////////////////////////////////////////////////////////////////////////////////////////////////////////

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


struct Edge
{
	int		v;
	int		w;
};


template<class Elem>
struct Heap
{
	Array<Elem> a;

	bool(*IsBefore)(Elem& a, Elem& b);

	void Initialize(bool(*_IsBefore)(Elem& a, Elem& b))
	{
		a.Initialize();
		IsBefore = _IsBefore;
	}

	void Destory() { a.Destroy(); }

	int Child(int i) { return 2 * i + 1; }

	int Parent(int i) { return (i - 1) / 2; }

	Elem GetFirst() { return a[0]; }

	Elem RetrieveFirst()
	{
		Edge t;
		t.v = -1, t.w = -1;
		if (a.n == 0) return t;
		Elem toReturn = a[0];
		swap(a[0], a[a.n - 1]);
		a.RemoveLast();
		MoveDown(0);
		return toReturn;
	}

	void Add(Elem e)
	{
		a.AddLast(e);
		MoveUp(a.n - 1);
	}

	void MoveUp(int ind)
	{
		if (ind <= 0) return;
		int p = Parent(ind);
		if (!IsBefore(a[p], a[ind]))
		{
			swap(a[p], a[ind]);
			MoveUp(p);
		}
	}

	void MoveDown(int ind)
	{
		int B_ind = ind;
		int l = Child(ind);
		int r = Child(ind) + 1;
		if (l < a.n && IsBefore(a[l], a[B_ind]))
			B_ind = l;
		if (r < a.n && IsBefore(a[r], a[B_ind]))
			B_ind = r;
		if (B_ind != ind)
		{
			swap(a[ind], a[B_ind]);
			MoveDown(B_ind);
		}
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////


struct Node
{
	Array<Edge> adj;

	void Initialize() { adj.Initialize(); }
	void Destroy() { adj.Destroy(); }
};

struct Graph
{
	int n;
	Node* nodes;

	void Initialize(int _n)
	{
		n = _n, nodes = new Node[n];
		for (int i = 0; i < n; i++) nodes[i].Initialize();
	}
	void Destroy() { for (int i = 0; i < n; i++) nodes[i].Destroy(); delete[] nodes; }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBefore(Edge& a, Edge& b)
{
	return a.w<b.w;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////



Graph g;

Heap<Edge> h;

int n, p[20001], vis[20001];
int d[20001];

Edge temp;

void Dijkstra(int start, int end)
{
	h.Initialize(IsBefore);
	temp.w = 0;
	temp.v = start;
	h.Add(temp);
	d[start] = 0;
	double minVal = INF;
	int index = start;
	while (h.a.n)
	{
		temp = h.RetrieveFirst();
		int toGO = temp.v;
		int val = temp.w;
		if (vis[toGO]) continue;
		vis[toGO] = true;
		for (int i = 0; i < g.nodes[toGO].adj.n; i++)
		{
			if (!vis[g.nodes[toGO].adj[i].v] && ((g.nodes[toGO].adj[i].w + d[toGO]) < d[g.nodes[toGO].adj[i].v]))
			{
				d[g.nodes[toGO].adj[i].v] = g.nodes[toGO].adj[i].w + d[toGO], p[g.nodes[toGO].adj[i].v] = index;
				temp.v = g.nodes[toGO].adj[i].v;
				temp.w = d[g.nodes[toGO].adj[i].v];
				h.Add(temp);
			}
		}
	}
	h.Destory();
}

int main()
{
	freopen("input.txt", "r", stdin);
	int N;
	cin >> N;
	int sc = 1;
	while (N--)
	{
		int m, S, T;
		cin >> n >> m >> S >> T;
		g.Initialize(n);
		for (int i = 0; i < m; i++)
		{
			int sn, en, wei;
			cin >> sn >> en >> wei;
			Edge temp;
			temp.v = en; temp.w = wei;
			g.nodes[sn].adj.AddLast(temp);
			temp.v = sn; temp.w = wei;
			g.nodes[en].adj.AddLast(temp);
		}
		memset(p, -1, sizeof(p));
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < n; i++) d[i] = INF;
		Dijkstra(S, T);
		if (d[T] == INF) cout << "Case #" << sc << ": " << "unreachable" << endl; 
		else cout << "Case #" << sc << ": " << d[T] << endl;
		sc++;
		g.Destroy();
	}
	return 0;
}


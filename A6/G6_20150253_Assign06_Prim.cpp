// G6_20150253_IDIDIDID_Assign06_Prim.cpp.cpp : Defines the entry point for the console application.
//

// GROUP:   6
// ID:      20150253
// Assign:  06
// Assign:  Prim
// UVA:     534
// Name1:   Mostafa Saber
// Name2:   Mohamed Samy
// UVA Username: yasou

#include "stdafx.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;

#define INF 1000000

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
	int		v;  // id of the adjacent node
	double	w;  // edge weight = distance between the two nodes
};

struct Node
{
	int x, y; // x and y coordinates of the node
	Array<Edge> adj;

	void Initialize() { adj.Initialize(); }
	void Destroy() { adj.Destroy();  }
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

// Find the square root of "v" in "n" iterations
double Sqrt(double v, int n = 100)
{
	double start = 0, end = v, mid = 0;
	while (n--)
	{
		mid = (start + end) / 2;
		if (mid*mid == v) { return mid; }
		else if (mid*mid > v) end = mid;
		else start = mid;
	}
	return mid;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int n , p[201] , vis[201];
double d[201];
Graph g;

int getMin()
{
	int toReturn = 0;
	double Minval = INF;
	for (int i = 0; i < n; i++)
		if (!vis[i] && d[i] < Minval)
			Minval = d[i], toReturn = i;
	return toReturn;
}

double solve(int start = 0 , int end = 1)
{
	vis[start] = true;
	d[start] = 0;
	double minVal = INF;
	int minIn = 202;
	double ans = 0;
	int index = start;
	while(index!=1)
	{
		for (int i = 0; i < g.nodes[index].adj.n; i++)
		{
			if (!vis[g.nodes[index].adj[i].v] && g.nodes[index].adj[i].w < d[g.nodes[index].adj[i].v])
			{
				d[g.nodes[index].adj[i].v] = g.nodes[index].adj[i].w, p[g.nodes[index].adj[i].v] = i;
			}
		}
		minIn = getMin();
		vis[minIn] = true, ans = max(ans, d[minIn]), index = minIn;
	}
	return ans;
}


int main()
{
	freopen("input.txt", "r", stdin);
	int sc = 1;
	while (cin >> n && n)
	{
		g.Initialize(n);
		for (int i = 0; i < n; i++)
		{
			int x, y; cin >> x >> y;
			g.nodes[i].x = x, g.nodes[i].y = y;
			for (int j = i - 1; j >= 0; j--)
			{
				Edge ed; ed.v = i; 
				ed.w = Sqrt((double)(g.nodes[i].x - g.nodes[j].x)*(g.nodes[i].x - g.nodes[j].x)
					+ (g.nodes[i].y - g.nodes[j].y)*(g.nodes[i].y - g.nodes[j].y));
				g.nodes[j].adj.AddLast(ed);
				ed.v = j;
				g.nodes[i].adj.AddLast(ed);
			}
		}
		memset(p, -1, sizeof(p));
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < n; i++) d[i] = INF;
		cout << "Scenario #" << sc << endl << "Frog Distance = " << fixed << setprecision(3) << solve() << endl << endl;
		sc++;
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////


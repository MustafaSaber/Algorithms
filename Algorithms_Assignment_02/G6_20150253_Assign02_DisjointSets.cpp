// G6_20150253_Assign02_DisjointSets.cpp : Defines the entry point for the console application.
//
// GROUP:		  6
// ID:			  20150253
// Assign:		  02
// Assign:	      DisjointSets
// UVA:			  10608
// UVA username:  yasou  
// Name:		  Mostafa Saber Talaat

#include "stdafx.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DisjointSets
{
	int n;
	int* parent;
	int* num_nodes;

	void Initialize(int _n) 
	{
		n = _n;
		parent = new int[_n]; num_nodes = new int[_n];

		for (int i = 0; i < n; i++) parent[i] = -1 , num_nodes[i] = 1;
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

		else { parent[first] = second; num_nodes[second] += num_nodes[first]; 	}
		return true;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	DisjointSets x;
	int cases;
	cin >> cases;
	while(cases--)
	{
		int n, m;
		cin >> n >> m;
		x.Initialize(n);
		for(int i = 0; i < m; i++) { int a, b; cin >> a >> b; x.Union(a-1, b-1); }
		int ans = x.num_nodes[0];
		for (int i = 1; i < n; i++)
			ans = max(ans, x.num_nodes[i]);
		cout << ans << endl;
		x.Destroy();
	}
    return 0;
}


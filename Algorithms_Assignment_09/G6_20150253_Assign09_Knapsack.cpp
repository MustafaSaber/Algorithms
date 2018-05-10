// G6_20150253_Assign09_Knapsack.cpp : Defines the entry point for the console application.
//

// GROUP:   6
// ID:      20150253
// Assign:  09
// Assign:  Knapsack
// UVA:     10130
// Name:    Mostafa Saber
// UVA Username: yasou

#include "stdafx.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Obj
{
	int v; // value (price) of object
	int w; // weight of object
};

Obj a[1000];

int T , N , P , W , G , GW;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T1[1001][31];
int Knapsack1(int n, int w)
{
	if (n == 0) return 0;
	if (T1[n][w] != -1) return T1[n][w];
	T1[n][w] = Knapsack1(n - 1, w);
	int cv = a[n - 1].v, cw = a[n - 1].w;

	if (cw <= w) 
		T1[n][w] = max(T1[n][w], Knapsack1(n - 1, w - cw) + cv);

	return T1[n][w];
}

int ComputeKnapsack1(int N, int W) // Recursive - memoization - initialize T then call Knapsack1(N,W);
{
	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= W; j++) T1[i][j] = -1;
	return Knapsack1(N, W);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T2[1001][31];
int ComputeKnapsack2(int N, int W) // Bottom-up, do not save space
{
	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= W; j++) T2[i][j] = -1;

	for(int n = 0 ; n <= N ; n++)
		for (int w = 0; w <= W; w++)
		{
			if (!n) { T2[n][w] = 0; continue; }
			int ret = T2[n - 1][w];
			int cv = a[n - 1].v, cw = a[n - 1].w;
			if (cw <= w)
				ret = max(ret , T2[n-1][w - cw] + cv);
			T2[n][w] = ret;
		}
	return T2[N][W];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T3[2][31];
int ComputeKnapsack3(int N, int W) // Bottom-up, use two rows only
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j <= W; j++) T3[i][j] = -1;

	int cur = 0;
	for (int n = 0; n <= N; n++)
	{
		for (int w = 0; w <= W; w++)
		{
			if (!n) { T3[cur][w] = 0; continue; }
			T3[cur][w] = T3[1 - cur][w];
			int cv = a[n - 1].v, cw = a[n - 1].w;
			if (cw <= w)
				T3[cur][w] = max(T3[cur][w], T3[1 - cur][w - cw] + cv);
		}
		cur = 1 - cur;
	}
	return T3[1 - cur][W];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T4[31];
int ComputeKnapsack4(int N, int W) // Bottom-up, save maximum space
{
	for (int j = 0; j <= W; j++) T4[j] = -1;

	int cur = 0;
	for (int n = 0; n <= N; n++)
		for (int w = W; w >= 0; w--)
		{
			if (!n) { T4[w] = 0; continue; }
			int cv = a[n - 1].v, cw = a[n - 1].w;
			if (cw <= w)
				T4[w] = max(T4[w], T4[w - cw] + cv);
		}
	return T4[W];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ComputeKnapsack(int N, int W) // Here we can choose the method
{
	//return ComputeKnapsack1(N,W);
	//return ComputeKnapsack2(N,W);
	//return ComputeKnapsack3(N,W);
	return ComputeKnapsack4(N, W);
}

void Compute() // Get input and call ComputeKnapsack() whenever needed
{
	int total;
	cin >> T;
	while(T--)
	{
		total = 0;
		cin >> N;
		for (int i = 0; i < N; i++)
		{
			cin >> P >> W;
			a[i].v = P, a[i].w = W;
		}
		cin >> G;
		for (int i = 0; i < G; i++)
		{
			cin >> GW;
			total += ComputeKnapsack(N , GW);
		}
		cout << total << endl;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	//freopen("input_assign09_10130.txt", "r", stdin);
	Compute();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

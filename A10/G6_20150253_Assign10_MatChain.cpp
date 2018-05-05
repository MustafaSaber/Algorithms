// G6_20150253_Assign10_MatChain.cpp.cpp : Defines the entry point for the console application.
//

// GROUP:   6
// ID:      20150253
// Assign:  10
// Assign:  MatChain
// UVA:     348
// Name1:   Mostafa Saber
// Name2:   XX SECOND STUDENT FULL NAME
// UVA Username: yasou

#include "stdafx.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

#define INF 100000000

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int N;
int p[11]; // the dimensions of matrices

int T[11][11]; // T[a][b]=the optimal number of multiplication of p[a]...p[b]
int D[11][11]; // D[a][b]=the decision (value of k) that gets T[a][b]

// Top down version
int MatChain(int a, int b)// Recursive
{
	int val;
	if (a + 1 == b) { T[a][b] = 0;  return 0; }

	if (T[a][b] >= 0) return T[a][b];

	T[a][b] = INF;

	for (int i = a + 1; i < b; ++i)
	{
		val = MatChain(a, i) + MatChain(i, b) + (p[a] * p[i] * p[b]);
		if (val < T[a][b]) { T[a][b] = val; D[a][b] = i; }
	}

	return T[a][b];

}

void MatChainTopDown(int n) // Initialize T then call MatChain(0,n)
{
	for (int i = 0; i < 11; i++)
		for (int j = 0; j < 11; j++) 
			T[i][j] = -1;

	MatChain(0, n);
}

// BottomUp version
void MatChainBottomUp(int n)
{
	for (int s = 1; s <= N; s++)
		for (int i = 0; i + s <= N; i++)
		{
			int j = i + s , val;
			if (i + 1 == j) { T[i][j] = 0; continue; }
			T[i][j] = INF;
			for (int k = i + 1; k < j; k++)
			{
				val = T[i][k] + T[k][j] + p[i] * p[k] * p[j];
				if (val < T[i][j]) { T[i][j] = val; D[i][j] = k; }
			}
		}

}

// Recursive to output the solution for both versions
void MatChainSol(int a, int b)
{
	if (a + 1 == b) { cout << "A" << b; return; }
	int k = D[a][b];
	cout << "(";
	MatChainSol(a, k);
	cout << " x ";
	MatChainSol(k, b);
	cout << ")";
}

void Compute()
{
	int coun = 1;
	while(true)
	{
		cin >> N;
		if (!N) break;
		for (int i = 0; i < N; i++) cin >> p[i] >> p[i + 1];

		MatChainTopDown(N);
		//MatChainBottomUp(N);
		cout << "Case " << coun << ": ";
		MatChainSol(0, N);
		puts("");
		coun++;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	//freopen("input_assign10_00348.txt", "r", stdin);
	Compute();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// G6_20150253_Assign11_EditDist.cpp : Defines the entry point for the console application.
//

// GROUP:   6
// ID:      20150253
// Assign:  11
// Assign:  EditDist
// UVA:     526
// Name:    Mostafa Saber
// UVA Username: yasou

#include "stdafx.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 1 -- insert
// 2 -- delete
// 3 -- replace


char a[82];
char b[82];

int D[81][81]; // D[][] is the same for all versions (no memory reduction)
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int equal(int i, int j)
{
	return !(a[i-1] == b[j-1]);
}

int T1[81][81];
int EditDist1(int n, int m)
{
	if (n == 0 && m == 0) { T1[n][m] = 0; return 0; }

	if (T1[n][m] >= 0) return T1[n][m];

	T1[n][m] = 100000000;

	if (m > 0)
	{
		int insert = 1 + EditDist1(n, m - 1);
		if (T1[n][m] > insert) { T1[n][m] = insert; D[n][m] = 1; }
	}
	if (n > 0)
	{
		int Delete = 1 + EditDist1(n - 1, m);
		if (T1[n][m] > Delete) { T1[n][m] = Delete; D[n][m] = 2; }
	}
	if (n > 0 && m > 0)
	{
		int temp = equal(n, m);
		int replace = equal(n, m) + EditDist1(n - 1, m - 1);
		if (T1[n][m] > replace) 
		{
			T1[n][m] = replace;
			if(!temp) D[n][m] = 4;
			else D[n][m] = 3;
		}
	}

	return T1[n][m];
}

int ComputeEditDist1(int N, int M) // Recursive - memoization - initialize T then call EditDist1(N,M);
{
	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= M; j++)
			T1[i][j] = -1;
	return EditDist1(N, M);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T2[81][81];
int ComputeEditDist2(int N, int M) // Bottom-up, do not save space
{
	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= M; j++)
			T2[i][j] = -1;

	for (int i = 1; i <= N; i++)
	{
		T2[i][0] = i;
		D[i][0] = 2; //I will delet from n till it reach m
	}

	for (int i = 1; i <= M; i++)
	{
		T2[0][i] = i;
		D[0][i] = 1; //I will insert in n till it reach m
	}

	T2[0][0] = 0;
	for (int n = 1; n <= N; n++)
	{
		for (int m = 1; m <= M; m++)
		{
			T2[n][m] = 10000000;
			int temp = equal(n, m);
			int insert = 1 + T2[n][m - 1];
			int Delete = 1 + T2[n - 1][m];
			int replace = temp + T2[n - 1][m - 1];
			if (T2[n][m] > insert) { T2[n][m] = insert; D[n][m] = 1; }
			if (T2[n][m] > Delete) { T2[n][m] = Delete; D[n][m] = 2; }
			if (T2[n][m] > replace)
			{
				T2[n][m] = replace;
				if (!temp) D[n][m] = 4;
				else D[n][m] = 3;
			}
		}
	}
	return T2[N][M];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T3[2][81];
int ComputeEditDist3(int N, int M) // Bottom-up, use two rows only
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j <= M; j++)
			T3[i][j] = -1;

	T3[0][0] = 0;
	D[0][0] = 0;
	int cur = 1;
	for (int n = 0; n <= N; n++)
	{
		for (int m = 0; m <= M; m++)
		{
			if (n == 0 && m > 0)
			{
				T3[cur][m] = m;
				D[n][m] = 1;
				continue;
			}
			if (n > 0 && m == 0)
			{
				T3[cur][m] = n;
				D[n][m] = 2;
				continue;
			}
			T3[cur][m] = 10000000;
			int temp = equal(n, m);
			int insert = 1 + T3[cur][m - 1];
			int Delete = 1 + T3[1 - cur][m];
			int replace = temp + T3[1 - cur][m - 1];
			if (T3[cur][m] > insert) { T3[cur][m] = insert; D[n][m] = 1; }
			if (T3[cur][m] > Delete) { T3[cur][m] = Delete; D[n][m] = 2; }
			if (T3[cur][m] > replace)
			{
				T3[cur][m] = replace;
				if (!temp) D[n][m] = 4;
				else D[n][m] = 3;
			}
		}
		cur = 1 - cur;
	}
	return T3[1 - cur][M];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T4[81];
int ComputeEditDist4(int N, int M) // Bottom-up, save maximum space
{
	for (int i = 0; i < 81; i++) T4[i] = -1;

	// x , y
	// z , f
	// f =  x || y || z;
	// I need x and y and z
	// If I calc on the same place then 
	// z, y val of x will be lost
	for (int n = 0; n <= N; n++)
	{
		int temp2 = 0;
		for (int m = 0; m <= M; m++)
		{
			if (!n && !m)
			{
				T4[m] = 0;
				D[n][m] = 0;
				continue;
			}
			if (n == 0 && m > 0)
			{
				temp2 = T4[m];
				T4[m] = m;
				D[n][m] = 1;
				continue;
			}
			if (n > 0 && m == 0)
			{
				temp2 = T4[m];
				T4[m] = n;
				D[n][m] = 2;
				continue;
			}
			int temp = equal(n, m);
			int insert = 1 + T4[m - 1]; //T4[m - 1] is z
			int Delete = 1 + T4[m]; // T4[m] is y
			int replace = temp + temp2;
			temp2 = T4[m]; // temp2 will be x
			T4[m] = 10000000;
			if (T4[m] > insert) { T4[m] = insert; D[n][m] = 1; }
			if (T4[m] > Delete) { T4[m] = Delete; D[n][m] = 2; }
			if (T4[m] > replace) 
			{
				T4[m] = replace;
				if (!temp) D[n][m] = 4;
				else D[n][m] = 3;
			}
		}
	}
	return T4[M];

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Oper
{
	int n, m;
	int oper;
};

Oper opers[81];

int steps = 0;

void EditDistSol(int N, int M)// Print the solution using D[][]
{
	if (N == 0 && M == 0) return;
	if (D[N][M] != 4)
	{
		opers[steps].n = N;
		opers[steps].m = M;
		opers[steps++].oper = D[N][M];
	}
	if (D[N][M] == 1) EditDistSol(N, M - 1);
	else if (D[N][M] == 2) EditDistSol(N - 1, M);
	else if (D[N][M] == 3 || D[N][M] == 4) EditDistSol(N - 1, M - 1);
}

void Print()
{
	int coun = 1;
	int resize = 0;
	for (int i = steps - 1; i >= 0; i--)
	{
		if(opers[i].oper == 1)
		{
			resize--;
			printf("%d Insert %d,%c\n", coun, opers[i].n - resize, b[opers[i].m - 1]);
		}
		else if (opers[i].oper == 2)
		{
			printf("%d Delete %d\n", coun, opers[i].n -  resize);
			resize++;
		}
		else if (opers[i].oper == 3)
		{
			printf("%d Replace %d,%c\n", coun, opers[i].n - resize, b[opers[i].m - 1]);
		}
		coun++;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ComputeEditDist(int N, int M) // Here we can choose the method
{
	//return ComputeEditDist1(N,M);
	//return ComputeEditDist2(N,M);
	//return ComputeEditDist3(N,M);
	return ComputeEditDist4(N, M);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This function does not need any modification:
void Compute() // Get input and call ComputeEditDist() whenever needed
{
	int cas = 0;
	while (true)
	{
		a[0] = 0; b[0] = 0;
		steps = 0;
		if (!fgets(a, 82, stdin)) break; fgets(b, 82, stdin);
		a[strlen(a) - 1] = 0;
		b[strlen(b) - 1] = 0;
		if (cas) cout << endl; // print an empty line between test cases
		int N = strlen(a), M = strlen(b);
		cout << ComputeEditDist(N, M) << endl;
		EditDistSol(N, M);
		Print();
		cas++;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	freopen("input_assign11_00526.txt", "r", stdin);
	freopen("output_assign11_00526.txt", "w", stdout);
	Compute();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////


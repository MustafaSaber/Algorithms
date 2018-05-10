// G6_20150253_Assign14_eigthQueens.cpp : Defines the entry point for the console application.
//


// GROUP:   6
// ID:      20150253
// Assign:  14
// Assign:  n-Queens
// UVA:     11195
// Name:    Mostafa Saber
// UVA Username: yasou

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

#define MAX_NUM 16

int n , ans;
string Grid[MAX_NUM];
bool fdiag[2 * MAX_NUM], bdiag[2 * MAX_NUM];

int Cur_Sol[MAX_NUM];
int F[MAX_NUM + 1]; // head=F[0], elements are indexed from 1 to n, F[n]=0
int B[MAX_NUM + 1]; // B[0]=n, B[1]=0
void Remove(int i) { F[B[i]] = F[i]; B[F[i]] = B[i]; }
void Restore(int i) { B[F[i]] = i; F[B[i]] = i; }
void InitDancingLinks(int n)
{
	int i;
	for (i = 0; i<n; i++) F[i] = i + 1; F[n] = 0;
	for (i = n; i>0; i--) B[i] = i - 1; B[0] = n;
}

/*void CheckValid()
{
	for (int i = n - 1; i > 0; i--)
			for (int j = i - 1; j >= 0; j--)
				if ( abs(i - j) == abs(Cur_Sol[i] - Cur_Sol[j]))
					return;
	ans += 1;
}*/

void BackTrack(int i)
{
	if (i == n) {
		//CheckValid();
		ans++;
		return;
	}

	for (int j = F[0]; j != 0; j = F[j])
	{
		if (!fdiag[i - j + (n-1)] && !bdiag[i + j] && Grid[i][j-1]!='*')
		{
			fdiag[i - j + (n - 1)] = bdiag[i + j] = true;
			Cur_Sol[i] = j - 1;
			Remove(j);
			BackTrack(i + 1);
			Restore(j);
			fdiag[i - j + (n - 1)] = bdiag[i + j] = false;
		}
	}
}

void Compute0()
{
	InitDancingLinks(n);
	BackTrack(0);
}

void ComputeCore()
{
	ans = 0;
	Compute0();
}


void Compute()
{
	int Case = 1;
	while (true)
	{
		ans = 0;
		cin >> n;
		if (!n) return;
		for (int i = 0; i < n; i++)
				cin >> Grid[i];

		ComputeCore();
		printf("Case %d: %d\n", Case, ans);
		Case++;
	}
}

int main()
{
	freopen("input_assign14_11195.txt", "r", stdin);
	freopen("ouput_assign14_11195.txt", "w", stdout);
	Compute();
    return 0;
}


// G6_20150253_Assign04_CountInv.cpp : Defines the entry point for the console application.
//
// GROUP:		 6
// ID:			 20150253
// Assign:		 04
// Assign:		 CountInv
// UVA:			 10810
// UVA username: yasou
// Name:		 Mostafa Saber

#include "stdafx.h"

#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool cmp(long long a, long long b) { return a <= b; }

long long CountInvMerge(long long* a, int n , bool (*isBef)(long long a , long long b) )
{
	long long count = 0;
	int mid = n / 2;
	int i = 0, j = mid;
	int* t = new int[n];

	for (int k = 0; k < n; k++)
	{
		if (j == n || (i < mid && isBef(a[i] , a[j])))
			t[k] = a[i++];
		else { count += (mid - i); t[k] = a[j++]; }
	}
	for (i = 0; i < n; i++) a[i] = t[i];
	delete[] t;
	return count;
}

long long CountInv(long long* a, int n , bool(*isBef)(long long a, long long b))
{
	int mid = n / 2;
	if (n <= 1) return 0;
	long long num1 = CountInv(a, mid , isBef);
	long long num2 = CountInv(a + mid, n - mid , isBef);
	return num1 + num2 + CountInvMerge(a, n , isBef);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	//freopen("input.txt", "r", stdin);
	int n;
	long long arr[49999];
	// the size of 500000 in the problem make a stack over flow
	while (cin >> n && n)
	{
		for (int i = 0; i < n; i++)	cin >> arr[i];
		cout << CountInv(arr, n , cmp) << endl;
	}
	return 0;
}

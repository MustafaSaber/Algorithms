// GROUP:   6
// ID:      20150253
// Assign:  01
// Assign:  ArrayHeap
// UVA:     10954
// Name:    Mostafa Saber Talaat

#include "stdafx.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Value>
struct Array
{
	int n, sz;
	Value* arr;
	
	void Initialize() { sz = 1, n = 0, arr = new Value[sz]; }
	
	void Destroy() { delete[] arr; }
	
	void AddLast(Value v)
	{
		if (n == sz)
		{
			sz *= 2;
			Value* new_arr = new Value[sz];
			for (int i = 0; i < n; i++)
				new_arr[i] = arr[i];
			delete[] arr;
			arr = new_arr;
		}
		arr[n++] = v;
	}
	void RemoveLast() { (n > 0) ? n-- : n; }
	
	Value& operator[] (int i) { return arr[i]; }
	
	void Print()
	{
		for (int i = 0; i < n; i++)
			cout << arr[i] << " ";
		cout << endl;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
		if (a.n == 0) return -1;
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

bool IsBeforeInt(int& a, int& b) { return a<b; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	int n;
	while (cin >> n && n != 0)
	{
		long long tc = 0;
		Heap<int> h;
		h.Initialize(IsBeforeInt);
		for (int i = 0; i < n; i++)
		{
			int temp;
			cin >> temp; h.Add(temp);
		}
		int num1 = 0, num2 = 0;
		while (h.a.n > 1)
		{
			num1 = h.RetrieveFirst();
			num2 = h.RetrieveFirst();
			tc += (num1 + num2);	
			h.Add(num1 + num2);
		}
		h.Destory();
		cout << tc << endl;
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

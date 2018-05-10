#include "stdafx.h"
#include<iostream>
#include"Matrix.h"
using namespace std;


int main()
{
	Matrix<int> f, n, c;
	try
	{
		int r1, r2, c1, c2;
		cout << "Enter the no of rows of the first matrix: ";
		cin >> r1; f.setr(r1);
		cout << "Enter the no of columes of the first matrix: ";
		cin >> c1; f.setc(c1); f.setm(r1, c1);
		cout << "Enter the no of rows of the second matrix: ";
		cin >> r2; n.setr(r2);
		cout << "Enter the no of columes of the second matrix: ";
		cin >> c2; n.setc(c2); n.setm(r2, c2);
		cin >> f >> n;
		c = f * n;  cout << c << endl;
		c = c * 2;  cout << c << endl;
	}
	catch(Matrix<int> f) { cout << f.DiffDimensions() << endl; }
	return 0;
}

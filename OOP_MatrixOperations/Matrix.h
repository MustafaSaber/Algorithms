#ifndef MATRIX_H
#define MATRIX_H

#include"stdafx.h"
#include <iostream>
using namespace std;

template <class T>
class Matrix
{
public:
	Matrix(int a, int b);
	Matrix();
	const char* DiffDimensions() const throw() { return "You can't do this mathmatical operation."; }
	Matrix(const Matrix<T> & d); // A copy constructor you must have one if u are using a 2D dynamic array I will explain why in body of the function.
	~Matrix() { for (int i = 0; i < row; i++) { delete[] mat[i]; } delete[] mat; } // Destructor
	friend ostream& operator<< <>(ostream& out,const Matrix<T>& temp);
	friend istream& operator >> <>(istream& in, Matrix<T>& temp);
	int getrow() { return row; } // row getter
	int getcol() { return colu; } // colume getter
	void setr(int r) { row = r; } // row setter
	void setc(int c) { colu = c; } // colu setter
	void setm(int a, int b); // Matrix setter , it must be their if we used  setr & setc just to resize the matrix
	T** getMat() { return mat; } // Matrix getter
	Matrix<T> operator +(Matrix<T> anotherMat); // add two matrices
	Matrix<T> operator -(Matrix<T> anotherMat); // subtract two matrices
	Matrix<T> operator *(Matrix<T> anotherMat); // multiply two matrices
	Matrix<T> operator *(int x); // to scale the matrix, in form((integer)value * MATRIX_OBJECT)
	// to scale the matrix  , in form (MATRIX_OBJECT * (integer)value)
	friend Matrix<T> operator *(int Left, Matrix<T> Right) { Matrix<T> temp; temp = Right*Left; return temp; }
	Matrix<T> & operator =(Matrix<T>& d);
	Matrix<T> transpose();
private:
	int row, colu;
	T **mat;
};



template <class T>
void Matrix<T>::setm(int a, int b)
{
	row = a;
	colu = b;
	mat = new T*[a];
	for (int i = 0; i < a; i++)
		mat[i] = new T[b];
	for (int i = 0; i < a; i++)
		for (int j = 0; j < b; j++)
			mat[i][j] = 0;
}

template <class T>
Matrix<T>::Matrix(int a, int b)
{
	row = a;
	colu = b;
	mat = new T*[a];
	for (int i = 0; i < a; i++)
		mat[i] = new T[b];
	for (int i = 0; i < a; i++)
		for (int j = 0; j < b; j++)
			mat[i][j] = 0;
}

template <class T>
Matrix<T>::Matrix()
{
	row = 0; colu = 0;
	mat = new T*[row];
	for (int i = 0; i < row; i++)
		mat[i] = new T[colu];
}

template <class T>
Matrix<T>::Matrix(const Matrix<T> & d)
{
	row = d.row;
	colu = d.colu;
	mat = new T *[d.row];
	for (int i = 0; i < row; i++) {
		mat[i] = new T[d.colu];
	}

	for (int i = 0; i < d.row; i++) {
		for (int j = 0; j < d.colu; j++) {
			mat[i][j] = d.mat[i][j];
		}
	}
}

template <class T>
Matrix<T> Matrix<T>::operator+(Matrix<T> anotherMat)
{
	if (row == anotherMat.row && colu == anotherMat.colu)
	{
		Matrix<T> temp(row, colu);
		for (int i = 0; i < row; i++)
			for (int j = 0; j < colu; j++)
				temp.mat[i][j] = mat[i][j] + anotherMat.mat[i][j];
		return temp;
	}
	else throw Matrix<T>();
}
template <class T>
Matrix<T> Matrix<T>::operator-(Matrix<T> anotherMat)
{
	if (row == anotherMat.getrow() && colu == anotherMat.getcol())
	{
		Matrix<T> temp(row, colu);
		for (int i = 0; i < row; i++)
			for (int j = 0; j < colu; j++)
				temp.mat[i][j] = mat[i][j] - anotherMat.getMat()[i][j];
		return temp;
	}
	else throw Matrix<T>();
}

template <class T>
Matrix<T> Matrix<T>::operator*(Matrix<T> anotherMat)
{
	if (colu == anotherMat.getrow())
	{
		Matrix<T> temp(row, anotherMat.getcol());
		for (int i = 0; i < row; i++)
			for (int j = 0; j < anotherMat.getcol(); j++)
				for (int k = 0; k < colu; k++)
					temp.mat[i][j] = temp.mat[i][j] +( mat[i][k] * anotherMat.getMat()[k][j]);
		return temp;
	}
	else throw Matrix<T>();
}

template<class T>
Matrix<T> Matrix<T>::operator*(int x)
{
	Matrix<T> temp(row, colu);
	for (int i = 0; i < row; i++)
			for (int j = 0; j < colu; j++)
				temp.mat[i][j] = (mat[i][j] * x);
	return temp;
}


template <class T>
Matrix<T> & Matrix<T>::operator=(Matrix<T>& d)
{
	row = d.row;
	colu = d.colu;
	mat = new T *[d.row];
	for (int i = 0; i < row; i++) {
		mat[i] = new T[d.colu];
	}

	for (int i = 0; i < d.row; i++) {
		for (int j = 0; j < d.colu; j++) {
			mat[i][j] = d.mat[i][j];
		}
	}
	return *this;
}

template <class T>
Matrix<T> Matrix<T>::transpose()
{
	Matrix<T> temp(colu,row);
	for (int i = 0; i < row; i++)
		for (int j = 0; j < colu; j++)
			temp.mat[j][i] = mat[i][j];
	return temp;
}

template <class T>
ostream& operator << <> (ostream& out, const Matrix<T>& temp)
{
	cout << "The Matrix which is " << temp.row << "x" << temp.colu << " contains : " << endl;
	for (int i = 0; i < temp.row; i++)
	{
		for (int j = 0; j < temp.colu; j++)
			out << temp.mat[i][j] << " ";
		out << endl;
	}
	return out;
}

template <class T>
istream& operator >> <>(istream& in, Matrix<T>& temp)
{
	cout << "Enter the matrix which is " << temp.row << "x" << temp.colu << " : " << endl;
	for (int i = 0; i < temp.row; i++)
		for (int j = 0; j < temp.colu; j++)
			in >> temp.mat[i][j];
	return in;
}


#endif // MATRIX_H

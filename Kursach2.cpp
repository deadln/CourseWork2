#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include "Matrix.h"
#include <cstdio>

using namespace std;

int main()
{
	char f[10],f1[10],f2[10];
	strcpy(f, "matr.txt");
	strcpy(f1, "matr2.txt");
	strcpy(f2, "ans.txt");
	Matrix<double> m1(f), m2(f1),r;
	m1.show();
	m2.show();
	r = m1 * m2;
	r.show();
	r = r * 10;
	r.show();
	cout << (m1 == m2) << endl;
	cout << (r == r) << endl;
	r.save(f2);
	return 0;
}

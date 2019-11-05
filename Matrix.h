#pragma once
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdio>
#include <cstdlib>

using namespace std;

template <class T>
T max(T x1, T x2)
{
	if (x1 > x2)
		return x1;
	else
		return x2;
}

template <class T> class Matrix
{
	T** items;
	int widht;
	int height;
public:
	Matrix();
	Matrix(int h, int w);
	Matrix(const char* filename);
	~Matrix();
	int get_widht() { return widht; }
	int get_height() { return height; }
	void show();
	void operator=(Matrix *m);
	void operator=(Matrix &m);
	Matrix<T>* operator+(Matrix &m);
	Matrix<T>* operator-(Matrix& m);
	Matrix<T>* operator*(Matrix& m);
	Matrix<T>* operator*(double n);
	bool operator==(Matrix& m);
	T* operator[](int i) { return items[i]; }
	void save(const char* filename);
	void open(const char* filename);
};


template <class T>
Matrix<T>::Matrix()
{
	widht = 1;
	height = 1;
	items = new  T* [1];
	items[0] = new T[1];
	items[0][0] = 0;
}

template <class T>
Matrix<T>::Matrix(int h, int w)
{
	widht = w;
	height = h;
	items = new  T* [height];
	for (int i = 0; i < height; i++)
	{
		items[i] = new T[w];
		for (int j = 0; j < widht; j++)
		{
			items[i][j] = 0;
		}
	}
}

template <class T>
Matrix<T>::Matrix(const char* filename)
{
	ifstream in;
	in.open(filename);
	if (!in)
	{
		setlocale(LC_ALL, "rus");
		cout << "Не удалось открыть файл\n";
		height = 1;
		widht = 1;
		items = new  T* [1];
		items[0] = new T[1];
		items[0][0] = 1;
		return;
	}
	int w, h;
	in >> h >> w;
	widht = w;
	height = h;
	items = new  T* [height];
	for (int i = 0; i < height; i++)
	{
		items[i] = new T[w];
		for (int j = 0; j < widht; j++)
		{
			in >> items[i][j];
		}
	}
}

template <class T>
Matrix<T>::~Matrix()
{
	for (int i = 0; i < height; i++)
	{
		delete[] items[i];
	}
	delete[] items;
}

template <class T>
void Matrix<T>::show()
{
	cout << height << " x " << widht << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < widht; j++)
		{
			cout << items[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

template <class T>
void Matrix<T>::operator=(Matrix *m)
{
	for (int i = 0; i < height; i++)
	{
		delete[] items[i];
	}
	delete[] items;

	widht = m->widht;
	height = m->height;
	items = new T * [height];
	for (int i = 0; i < height; i++)
	{
		items[i] = new T[widht];
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < widht; j++)
		{
			items[i][j] = m->items[i][j];
		}
	}

	delete m;
}

template <class T>
void Matrix<T>::operator=(Matrix& m)
{
	for (int i = 0; i < height; i++)
	{
		delete[] items[i];
	}
	delete[] items;

	widht = m.widht;
	height = m.height;
	items = new T * [height];
	for (int i = 0; i < height; i++)
	{
		items[i] = new T[widht];
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < widht; j++)
		{
			items[i][j] = m.items[i][j];
		}
	}

}

template <class T>
Matrix<T>* Matrix<T>::operator+(Matrix &m)
{
	Matrix<T> s1(max(height, m.height), max(widht, m.widht)), s2(max(height, m.height), max(widht, m.widht));
	Matrix<T> *res = new Matrix<T>(max(height, m.height), max(widht, m.widht));
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < widht; j++)
		{
			s1.items[i][j] = items[i][j];
		}
	}

	for (int i = 0; i < m.height; i++)
	{
		for (int j = 0; j < m.widht; j++)
		{
			s2.items[i][j] = m.items[i][j];
		}
	}

	for (int i = 0; i < res->height; i++)
	{
		for (int j = 0; j < res->widht; j++)
		{
			res->items[i][j] = s1.items[i][j] + s2.items[i][j];
		}
	}
	
	return res;
}

template <class T>
Matrix<T>* Matrix<T>::operator-(Matrix& m)
{
	Matrix<T> s1(max(height, m.height), max(widht, m.widht)), s2(max(height, m.height), max(widht, m.widht));
	Matrix<T>* res = new Matrix<T>(max(height, m.height), max(widht, m.widht));
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < widht; j++)
		{
			s1.items[i][j] = items[i][j];
		}
	}

	for (int i = 0; i < m.height; i++)
	{
		for (int j = 0; j < m.widht; j++)
		{
			s2.items[i][j] = m.items[i][j];
		}
	}

	for (int i = 0; i < res->height; i++)
	{
		for (int j = 0; j < res->widht; j++)
		{
			res->items[i][j] = s1.items[i][j] - s2.items[i][j];
		}
	}

	return res;
}

template <class T>
Matrix<T>* Matrix<T>::operator*(Matrix& m)
{
	if (widht != m.height)
	{
		setlocale(LC_ALL, "rus");
		cout << "Умножение невозможно\n";
		Matrix<T>* res = new Matrix<T>();
		return res;
	}
	Matrix<T> s1(height, widht), s2(m.height, m.widht);
	Matrix<T>* res = new Matrix<T>(height, m.widht);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < widht; j++)
		{
			s1.items[i][j] = items[i][j];
		}
	}

	for (int i = 0; i < m.height; i++)
	{
		for (int j = 0; j < m.widht; j++)
		{
			s2.items[i][j] = m.items[i][j];
		}
	}

	for (int i = 0; i < res->height; i++)
	{
		for (int j = 0; j < res->widht; j++)
		{
			for (int k = 0; k < widht; k++)
			{
				res->items[i][j] += s1.items[i][k] * s2.items[k][j];
			}
			//res->items[i][j] = s1.items[i][j] * s2.items[i][j];
		}
	}

	return res;
}

template <class T>
Matrix<T>* Matrix<T>::operator*(double n)
{
	Matrix<T>* res = new Matrix<T>(height, widht);
	for (int  i = 0; i < height; i++)
	{
		for (int j = 0; j < widht; j++)
		{
			res->items[i][j] = items[i][j] * n;
		}
	}
	return res;
}

template <class T>
bool Matrix<T>::operator==(Matrix& m)
{
	if (height != m.height || widht != m.widht)
		return false;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < widht; j++)
		{
			if (items[i][j] != m.items[i][j])
				return false;
		}
	}
	return true;
}

template <class T>
void Matrix<T>::save(const char* filename)
{
	ofstream out;
	out.open(filename);
	if (!out)
	{
		setlocale(LC_ALL, "rus");
		cout << "Не удалось открыть файл\n";
		return;
	}
	out << height << ' ' << widht << '\n';
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < widht; j++)
		{
			out << items[i][j];
			if (j != widht - 1)
				out << ' ';
		}
		out << '\n';
	}
	out.close();
}

template <class T>
void Matrix<T>::open(const char* filename)
{
	ifstream in;
	in.open(filename);
	if (!in)
	{
		setlocale(LC_ALL, "rus");
		cout << "Не удалось открыть файл\n";
		return;
	}

	for (int i = 0; i < height; i++)
	{
		delete[] items[i];
	}
	delete[] items;

	int w, h;
	in >> h >> w;
	widht = w;
	height = h;
	items = new  T * [height];
	for (int i = 0; i < height; i++)
	{
		items[i] = new T[w];
		for (int j = 0; j < widht; j++)
		{
			in >> items[i][j];
		}
	}
}
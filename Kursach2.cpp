#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include "Matrix.h"
#include <cstdio>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	char f[50];
	Matrix<double> m1("m1.txt"), m2("m2.txt"), m3("m3.txt");
	int in;


	for (;;)
	{
		cout << "\n\nКоманды:\n";
		cout << "0. Справка\n";
		cout << "1. Открыть из файла матрицу\n";
		cout << "2. Вывести на экран матрицу\n";
		cout << "3. Поменять матрицы местами\n";
		cout << "4. Сложить первую и вторую матрицу\n";
		cout << "5. Вычесть вторую матрицу из первой\n";
		cout << "6. Умножить матрицу на число\n";
		cout << "7. Умножить матрицу на вектор\n";
		cout << "8. Умножить первую матрицу на вторую матрицу\n";
		cout << "9. Присвоить одну матрицу к другой\n";
		cout << "10. Сравнить матрицы\n";
		cout << "11. Сохранить матрицу в файл\n";
		cout << "12. Закрыть программу и сохранить матрицы\n";

		cin >> in;

		if (in == 0)
		{
			cout << "Программа имеет 3 матрицы, с номерами 1 2 3. Результат действий с 1ой и\n";
			cout << "2ой матрицей сохраняется в 3ю. Умножение на число и вектор меняют выбранную\n";
			cout << "матрицу.\n";
		}

		else if (in == 1)
		{
			cout << "Введите имя файла\n";
			gets_s(f);
			gets_s(f);
			cout << "Введите номер матрицы\n";
			cin >> in;
			if (in == 1)
				m1.open(f);
			else if (in == 2)
				m2.open(f);
			else if (in == 3)
				m3.open(f);
			else
				cout << "Неверный номер матрицы\n";
		}

		else if (in == 2)
		{
			cout << "Введите номер матрицы\n";
			cin >> in;
			if (in == 1)
				m1.show();
			else if (in == 2)
				m2.show();
			else if (in == 3)
				m3.show();
			else
				cout << "Неверный номер матрицы\n";
		}

		else if (in == 3)
		{
			int n1, n2;
			Matrix<double> m;
			cout << "Введите номера матриц\n";
			cin >> n1 >> n2;
			if (n1 == 1 && n2 == 2 || n1 == 2 && n2 == 1)
			{
				m = m1;
				m1 = m2;
				m2 = m;
			}
			else if (n1 == 1 && n2 == 3 || n1 == 3 && n2 == 1)
			{
				m = m1;
				m1 = m3;
				m3 = m;
			}
			else if (n1 == 3 && n2 == 2 || n1 == 2 && n2 == 3)
			{
				m = m3;
				m3 = m2;
				m2 = m;
			}
			else
			{
				cout << "Неверные номера матриц\n";
			}
		}

		else if (in == 4)
		{
			m3 = m1 + m2;
		}

		else if (in == 5)
		{
			m3 = m1 - m2;
		}

		else if (in == 6)
		{
			double n;
			cout << "Введите номер матрицы\n";
			cin >> in;
			if (in < 1 || in > 3)
			{
				cout << "Неверный номер матрицы\n";
				continue;
			}
			cout << "Введите число\n";
			cin >> n;
			if (in == 1)
				m1 = m1 * n;
			else if (in == 2)
				m2 = m2 * n;
			else if (in == 3)
				m3 = m3 * n;

		}

		else if (in == 7)
		{
			cout << "Введите номер матрицы\n";
			cin >> in;
			if (in < 1 || in > 3)
			{
				cout << "Неверный номер матрицы\n";
				continue;
			}

			int n;
			cout << "Введите длину вектора\n";
			cin >> n;
			Matrix<double> vect(n, 1),res,check;
			cout << "Введите значения вектора\n";
			for (int i = 0; i < n; i++)
				cin >> vect[i][0];
			
			if (in == 1)
			{
				res = m1 * vect;
				if (!(m1 == check) && !(vect == check) && !(res == check))
					m1 = res;
				else if (m1 == check || vect == check)
					m1 = res;
			}
			else if (in == 2)
			{
				res = m2 * vect;
				if (!(m2 == check) && !(vect == check) && !(res == check))
					m2 = res;
				else if (m2 == check || vect == check)
					m2 = res;
			}
			else if (in == 3)
			{
				res = m3 * vect;
				if (!(m3 == check) && !(vect == check) && !(res == check))
					m3 = res;
				else if (m3 == check || vect == check)
					m3 = res;
			}
		}

		else if (in == 8)
		{
			m3 = m1 * m2;
		}

		else if (in == 9)
		{
			int n1, n2;
			cout << "Введите номера матриц (m1 = m2)\n";
			cin >> n1 >> n2;
			if (n1 == 1 && n2 == 2)
				m1 = m2;
			else if (n1 == 2 && n2 == 1)
				m2 = m1;
			else if (n1 == 1 && n2 == 3)
				m1 = m3;
			else if (n1 == 3 && n2 == 1)
				m3 = m1;
			else if (n1 == 2 && n2 == 3)
				m2 = m3;
			else if (n1 == 3 && n2 == 2)
				m3 = m2;
			else
			{
				cout << "Неверные номера матриц\n";
				continue;
			}
		}

		else if (in == 10)
		{
			int n1, n2;
			bool res;
			cout << "Введите номера матриц\n";
			cin >> n1 >> n2;
			if (n1 == 1 && n2 == 2 || n1 == 2 && n2 == 1)
			{
				res = (n1 == n2);
			}
			else if (n1 == 1 && n2 == 3 || n1 == 3 && n2 == 1)
			{
				res = (m1 == m3);
			}
			else if (n1 == 3 && n2 == 2 || n1 == 2 && n2 == 3)
			{
				res = (m2 == m3);
			}
			else
			{
				cout << "Неверные номера матриц\n";
			}

			if (res)
				cout << "Матрицы равны\n";
			else
				cout << "Матрицы не равны\n";
		}

		else if (in == 11)
		{
			cout << "Введите номер матрицы\n";
			cin >> in;
			if (in < 1 || in > 3)
			{
				cout << "Неверный номер матрицы\n";
				continue;
			}
			cout << "Введите имя файла\n";
			gets_s(f);
			gets_s(f);
			if (in == 1)
				m1.save(f);
			else if (in == 2)
				m2.save(f);
			else if (in == 3)
				m3.save(f);
		}

		else if (in == 12)
			break;

		else
			cout << "Неизвестная команда\n";
	}

	/*char f[10],f1[10],f2[10];
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
	r.save(f2);*/
	m1.save("m1.txt");
	m2.save("m2.txt");
	m3.save("m3.txt");
	return 0;
}

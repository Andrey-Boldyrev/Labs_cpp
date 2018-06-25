// Laba4.cpp: определяет точку входа для консольного приложения.
//
//2к 91 группа Болдырев Андрей
//Написать программу содерж след ф-ции:
//1. Функцию заполнения текстового файла N целыми случайными числами в диапазоне  от -М до М. 
// Имя файла, N и М поступают на вход функции, файл возврашается функцией как результат(использовать потоки ввода-вывода). 
// Реализовать два варианта генерации чисел: с помощью цикла и алгоритма std::generate.
//2. Функцию получающую файл на вход и возвращающий послед контейнер, заполненый числами из файла.
//3. Функцию modify, выполняющую проеобразование полученного контейнера на вход функции должен поступать контейнер,
//   в качестве результата функция должна возвращать модифицированный контейнер.
//4. Перегруженную функцию modify, принимающую на вход итераторы начала и конца обрабатываемой  части контейнера.
//5. Функцию, реализующую требуемое преобразование с использованием алгоритма std::transform вместо функции modify.
//6. Функцию, реализующую требуемое преобразование с использованием алгоритма std::for_each вместо функции modify.
//7. Функции, вычисляющие сумму и сред арифм чисел, содерж в контейнере.
//8. Функцию вывода результата в файл и на экран (опционально).
//Контейнер: список. Преобразование: Добавить к каждому числу полусумму всех отрицательных чисел


#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <algorithm>


using namespace std;


ofstream RndFileCycle(string fname, int N, int M)
{
	ofstream file(fname);
	if (file.fail())
		throw "Can't open the file";

	if (N < 1)
		throw "Count of elements must be positive";

	if (M < 1)
		throw "Nubmer M must be positive";

	for (int i = 0; i < N; i++)
		file << rand() % (M * 2 + 1) - M << ' ';

	return file;
}

ofstream RndFileGen(string fname, int N, int M)
{
	ofstream file(fname);
	if (file.fail())
		throw "Can't open the file";

	if (N < 1)
		throw "Count of elements must be positive";

	if (M < 1)
		throw "Nubmer M must be positive";

	list<double> ls = list<double>(N);
	generate(ls.begin(), ls.end(), [M]() {return (rand() % (M * 2 + 1) - M); });
	copy(ls.begin(), ls.end(), ostream_iterator<double>(file, " "));

	return file;
}

list<double> LoadListFromFile(string fname)
{
	ifstream file(fname);
	if (file.fail())
		throw "Can't open the file";

	list<double> ls;
	copy(istream_iterator<double>(file), istream_iterator<double>(), back_inserter(ls));
	return ls;
}

double negativeSum(list<double>::iterator begin, list<double>::iterator end)
{
	if (begin == end)
	{
		throw "Can not transform. List is empty";

	}
	double res = 0;
	int cnt = 0;
	for (auto ils = begin; ils != end; ++ils)
	{
		if (*ils < 0)
		{
			res += *ils;
			cnt++;
		}
	}
	return res / cnt;
}

list<double> Modify(list<double>::iterator begin, list<double>::iterator end)
{
	double tempSum = negativeSum(begin, end);
	list<double> res;
	for (auto ils = begin; ils != end; ++ils)
	{
		res.push_back(*ils + tempSum);
	}
	return res;
}

list<double> Modify(list<double> &ls)
{
	return Modify(ls.begin(), ls.end());
}


list<double> TransformList(list<double> ls)
{
	list<double> res = list<double>(ls.size());
	if (ls.size() == 0)
		throw "List is empty";

	double tempSum = negativeSum(ls.begin(), ls.end());
	transform(ls.begin(), ls.end(), res.begin(), [tempSum](const double elem)
	{ return (elem + tempSum); });

	return res;
}

list<double> ForEachList(list<double> ls)
{
	if (ls.size() == 0)
		throw "List is empty!";

	double tempSum = negativeSum(ls.begin(), ls.end());
	for_each(ls.begin(), ls.end(), [tempSum](double &elem)
	{ elem = (elem + tempSum); });

	return ls;
}

double SumList(const list<double>& ls)
{

	if (ls.empty())
		throw "List is empty";
	double res = 0;
	for (auto ils : ls) res += ils;

	return res;
}

double AverageList(list<double> &ls)
{
	return (SumList(ls)) / (double)ls.size();
}

void PrintList(list<double> &ls, string fname)
{
	fstream file;
	file.open(fname, ios::out);
	if (!file.is_open())
	{
		file.close();
		throw "Can't open the file!";
	}

	if (ls.empty())
		cout << "List is empty!" << endl;
	else
	{
		copy(ls.begin(), ls.end(), ostream_iterator<double>(file, " "));
	}

}

void PrintList(list<double> &ls)
{
	if (ls.empty())
	{
		cout << "List is empty!" << endl;
	}
	else
	{
		for (auto ils : ls) cout << ils << ' ';
		cout << endl;
	}
}


//печать меню
void printMenu()
{
	cout << "===================================================================" << endl;
	cout << "Select a command:" << endl;
	cout << "[1]  - Fill out the file by random numbers with cycle" << endl;
	cout << "[2]  - Fill out the file by random numbers with generate" << endl;
	cout << "[3]  - Create a List based on a file" << endl;
	cout << "[4]  - Transform List" << endl;
	cout << "[5]  - Transform a List's range" << endl;
	cout << "[6]  - Transform the List with the transform" << endl;
	cout << "[7]  - Transform the List with the for_each" << endl;
	cout << "[8]  - Process the sum of List" << endl;
	cout << "[9]  - Process the average of List" << endl;
	cout << "[10] - Print the List to Console" << endl;
	cout << "[11] - Print the List to File " << endl;
	cout << "[0]  - Exit" << endl;
	cout << "===================================================================" << endl;
}


void InputNumber(string mes, int& num)
{
	cout << mes << endl;
	while (!(cin >> num))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Enter a number" << endl;
	}
}

void menu(int key, list<double>& ls)
{
	string fname;
	ofstream file;
	int N, M;
	list<double>::iterator head, last;
	switch (key)
	{
	case 1:
		cout << "Enter file's name" << endl;
		cin.clear();
		cin >> fname;
		InputNumber("Enter a count of random numbers", N);
		InputNumber("Enter a range (-M; M)", M);
		try
		{
			file = RndFileCycle(fname, N, M);
			file.close();
		}
		catch (char *s)
		{
			cout << s << endl;
		}
		break;
	case 2:
		cout << "Enter file's name" << endl;
		cin.clear();
		cin >> fname;

		InputNumber("Enter a count of random numbers", N);
		InputNumber("Enter a range (-M; M)", M);
		try
		{
			file = RndFileGen(fname, N, M);
			file.close();
		}
		catch (char *s)
		{
			cout << s << endl;
		}
		break;
	case 3:
		try
		{
			cout << "Enter file's name" << endl;
			cin.clear();
			cin >> fname;
			ls = LoadListFromFile(fname);
		}
		catch (char *s)
		{
			cout << s << endl;
		}
		break;
	case 4:
		if (!ls.empty())
		{
			ls = Modify(ls);
		}
		else
		{
			cout << "List is empty!" << endl;
		}
		break;
	case 5:
		InputNumber("Enter a lower limit of the range", N);
		InputNumber("Enter a high limit of the range", M);

		while ((N <= 0) || (M <= 0) || (N > (int)(ls.size())) || (M > (int)(ls.size())))
		{
			cout << "The wrong range(avalible from 1 to " << ls.size() << "). Repeate!" << endl;
			try
			{
				InputNumber("Enter a lower limit of the range", N);
				InputNumber("Enter a high limit of the range", M);
			}
			catch (char *s)
			{
				cout << s << endl;
			}
		}
		if (abs(N - M) < 2)
		{
			cout << "Transform has't the sense" << endl;
		}
		else
		{
			if (N > M)
				swap(N, M);

			try
			{
				head = last = ls.begin();

				advance(head, N - 1);
				advance(last, M);

				ls = Modify(head, last);
			}
			catch (char *s)
			{
				cout << s << endl;
			}
		}
		break;
	case 6:
		try
		{
			ls = TransformList(ls);
		}
		catch (char *s)
		{
			cout << s << endl;
		}
		break;
	case 7:
		try
		{
			ls = ForEachList(ls);
		}
		catch (char *s)
		{
			cout << s << endl;
		}
		break;
	case 8:
		try
		{
			cout << "Sum = " << SumList(ls) << endl;
		}
		catch (char *s)
		{
			cout << s << endl;
		}
		break;
	case 9:
		try
		{
			cout << "Average = " << AverageList(ls) << endl;
		}
		catch (char *s)
		{
			cout << s << endl;
		}
		break;
	case 10:
		try
		{
			PrintList(ls);
		}
		catch (char *s)
		{
			cout << s << endl;
		}
		break;
	case 11:
		cout << "Enter a file's name" << endl;
		cin.clear();
		cin >> fname;
		try
		{
			PrintList(ls, fname);
		}
		catch (char *s)
		{
			cout << s << endl;
		}
		break;
	case 0:
		break;
	default:
		cout << "Command not found! Repeat!" << endl;
		break;
	}
}

int main()
{
	list<double> ls;
	int key;
	do
	{
		printMenu();
		while (!(cin >> key))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Comand must be a digit" << endl;
		}
		menu(key, ls);
	} while (key != 0);
	return 0;
}

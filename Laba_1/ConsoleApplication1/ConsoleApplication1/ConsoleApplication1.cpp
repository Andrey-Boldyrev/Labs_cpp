// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.


/*В данном массиве найдите наибольшую серию подряд идущих элементов, расположенных по возрастанию*/

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include "iomanip" 

using namespace std;

typedef int TElem;

void Ex();
void Task();
void PrintMass(int str);
void Size();;
void InputMass();
void Rand();
void Menu();

TElem mas[500];
int n = 0;

void Ex()
{
	short answ;
	cout << "Choose next action:" << endl;
	cout << "1. Enter mass again" << endl << "2. End the programm" << endl;
	cin >> answ;
	switch (answ)
	{
	case 1:Menu(); break;
	case 2:return;
	default:
		cout << "Error.Enter correct number: " << endl;
		Ex();
		break;
	}
}


void Task()
{
	int index=0;
	int cnt = 1;
	int max_cnt = 1;
	for (int i = 1; i < n; i++)
	{
		if (mas[i] > mas[i - 1])
		{
			cnt++;
		}
		else
		{
			cnt = 1;
		}
		if (cnt > max_cnt)
		{
			max_cnt = cnt;
			index = i - max_cnt + 1;
		}
	}
	cout << endl;
	cout << "Solution of the task: " << max_cnt << endl;
	for (int i = index; i < (max_cnt+index); i++)
	{
		cout << setw(4) << setprecision(2) <<mas[i] << ' ';
	}
	cout << endl;
	
}

void PrintMass(int str)
{
	cout << "------------------" << endl;
	cout << "Massif: " << endl;
	for (int i = 0; i < str; i++)
	{
		cout << setw(4) << setprecision(2) << mas[i] << ' ';
		
	}
	cout << endl;
	Task();
	Ex();
	
}


void Size()
{
	do {
		cout << "Enter N (number of elements)= "; cin >> n;
	} while ((n<0) && (n!=0));
}

void InputMass()
{	
	cout << "Enter mass with  " << n << " elements " << endl;
	for (int i = 0; i < n; i++) {
		cout << "[" << i + 1 << "]="; cin >> mas[i];
	}
	PrintMass(n);
}

void Rand()
{
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		mas[i] = rand() % 240 - 20;
	}
	PrintMass(n);
}

void Menu()
{
	short answ;
	cout << "Choose point of menu: " << endl;
	cout << "1. Fill mass with keyboard" << endl;
	cout << "2. Fill mass with random" << endl;
	cin >> answ;
	switch (answ) 
	{
		case 1:
			InputMass();
			break;
		case 2:
			Rand();
			break;
		default:	
			cout << "Error.Enter correct number: " << endl;
			Menu();
			break;
	}
}


int main()
{
	Size();
	Menu();
	system("pause");
	return 0;
}
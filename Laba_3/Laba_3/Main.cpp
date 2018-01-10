// Laba3.cpp: определяет точку входа для консольного приложения.
//

/*2к,91гр,Болдырев Андрей, лаба №3, задача №2а.
Реализовать шаблон класса двусвязный (двунаправленный) список (DoublyLinkedList<X>), хранящий элементы произвольного типа.
Класс должен содержать:
- Инициализация списка;
- Добавление элемента в начало списка;
- Добавление элемента в конец списка;
- Показ всех элементов списка.

а)
- Удаление всех элементов списка;
- Определение количества элементов списка;
- Проверка списка на пустоту;
- Удаление первого элемента;
- Удаление последнего элемента;
*/
#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <string>
#include "List.cpp"
using namespace std;


int getPolyzenieChislaInt(int min1, int max1);
void menuSpisok();
void getInt();
void getString();
void print();


//получение числа int
int getPolyzenieChislaInt(int min1, int max1)
{
	int n;

	while (true)
	{
		cin >> n;
		if (!cin)
		{
			cout << "Ne verno, vvedite chslo\n";
			cin.clear();
			while (cin.get() != '\n');
		}
		else {
			if (n >= min1 && n <= max1)
				break;
			else
			{
				cout << "Ne pravilno, vvedite ot " << min1 << " do " << max1 << endl;
				continue;
			}
		}
	}
	return n;

}

void menuSpisok()
{
	cout << "------------------------" << endl
		<< "1 - Initialization" << endl
		<< "2 - Show list" << endl
		<< "3 - Push behind" << endl
		<< "4 - Push in back" << endl
		<< "5 - Delete all elements" << endl
		<< "6 - Number of elements" << endl
		<< "7 - Is empty?" << endl
		<< "8 - Delete first el" << endl
		<< "9 - Delete last el" << endl
		<< "10 - Exit" << endl
		<< "Input number menu: ";
}

void getInt()
{
	int n;
	int x;
	DoublyLinkedList<int> list; //инициализация

	do {
		menuSpisok();
		n = getPolyzenieChislaInt(1, 10);

		switch (n)
		{
		case 1:
		{
			cout << " Input element ";  cin >> x;
			list.addBackToList(x);
		}  break;

		case 2:
		{
			list.printList();
		}  break;

		case 3:
		{
			cout << " Input element ";  cin >> x;
			list.addBehindToList(x);
		}  break;

		case 4:
		{
			cout << " Input element ";  cin >> x;
			list.addBackToList(x);
		}  break;

		case 5:
		{
			list.DelList();
		}  break;

		case 6:
		{
			cout << "Number of elements: " << list.get_length() << endl;
			break;
		}

		case 7:
		{
			if (list.IsEmpty())
			{
				cout << "Empty!" << endl;
			}
			else
			{
				cout << "Not empty!" << endl;
			}
			break;
		}

		case 8:
		{
			try {
				list.RemoveHeadEl();
			}
			catch (invalid_argument& e)
			{
				cerr << e.what() << endl;
			}
			break;
		}
		case 9:
		{
			try {
				list.RemoveTailEl();
			}
			catch (invalid_argument& e)
			{
				cerr << e.what() << endl;
			}
			break;
		}

		default:
			break;
		}

	} while (n != 10);

	print();
}

void getString()
{
	int n;
	string x;
	DoublyLinkedList<string> list; //инициализация

	do {
		menuSpisok();
		n = getPolyzenieChislaInt(1, 10);

		switch (n)
		{
		case 1:
		{
			cout << " Input element ";  cin >> x;
			list.addBackToList(x);
		}  break;

		case 2:
		{
			list.printList();
		}  break;

		case 3:
		{
			cout << " Input element ";  cin >> x;
			list.addBehindToList(x);
		}  break;

		case 4:
		{
			cout << " Input element ";  cin >> x;
			list.addBackToList(x);
		}  break;

		case 5:
		{
			list.DelList();
		}  break;

		case 6:
		{
			cout << "Number of elements: " << list.get_length() << endl;
			break;
		}

		case 7:
		{
			if (list.IsEmpty())
			{
				cout << "Empty!" << endl;
			}
			else
			{
				cout << "Not empty!" << endl;
			}
			break;
		}

		case 8:
		{
			try {
				list.RemoveHeadEl();
			}
			catch (invalid_argument& e)
			{
				cerr << e.what() << endl;
			}
			break;
		}
		case 9:
		{
			try {
				list.RemoveTailEl();
			}
			catch (invalid_argument& e)
			{
				cerr << e.what() << endl;
			}
			break;
		}

		default:
			break;
		}

	} while (n != 10);

	print();
}



void print()
{
	system("cls");
	int n;

	do {
		cout << "1.Chislovoy\n";
		cout << "2.Strokovoy\n";
		cout << "3.Exit\n";
		n = getPolyzenieChislaInt(1, 3);

		switch (n)
		{
		case 1: getInt();
			break;
		case 2: getString();
			break;
		default:
			break;
		}

	} while (n != 3);
}

int main()
{
	print();
	system("pause");
	return 0;
}

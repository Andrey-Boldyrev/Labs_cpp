// Laba2.cpp: определяет точку входа для консольного приложения.
//
/*Реализовать класс Account представляющий собой банковский счет.
В классе должны быть 4 поля: ФИО, номер счета, процент начисления, сумма в рублях.
Открытие счета выполняется операцией инициализации.
Необходимо выполнять следующий операции: сменить владельца счета,снять некоторую сумму денег со счета,
положить деньги на счет, начислить проценты, перевести сумму в доллары, евро.*/

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Account.h"

using namespace std;

/*Инициализация*/
Account Init()
{
	string n;  int acc; double per; double m;
	cout << "Enter data for new acc: " << endl;
	cout << "FIO: "; cin >> n;
	cout << "Account: "; cin >> acc;
	cout << "Percent: "; cin >> per;
	cout << "Money: "; cin >> m;
	Account Ob(n, acc, per, m);
	return Ob;
}

/*Функция продолжения действий*/
bool Check()
{
	int check;
	cout << "------------" << endl;
	cout << "Do you want to continue?" << endl;
	cout << "1. Yes" << endl;
	cout << "2. No" << endl;
	cin >> check;
	switch (check)
	{
	case 1:
	{
		return true;
	}

	case 2:
	{
		return false;
	}

	default:
	{
		cout << "Error. Enter correct number of menu." << endl;
		Check();
		break;
	}
	}

}

void Task()
{
	Account Ob = Init();
	do
	{
		int answ;
		cout << "------------" << endl;
		cout << "Choose what you want:" << endl;
		cout << "1. Change FIO" << endl;
		cout << "2. Take money" << endl;
		cout << "3. Put money" << endl;
		cout << "4. Add a percent" << endl;
		cout << "5. Transfer money in dollars" << endl;
		cout << "6. Transfer money in euros" << endl;
		cin >> answ;
		switch (answ)
		{
		case 1:
		{
			string name_tmp;
			cout << "------------" << endl;
			cout << "Enter new FIO: ";
			cin >> name_tmp;
			Ob.ChangeOwner(name_tmp);
			Ob.Display();
			break;
		}

		case 2:
		{
			int money;
			cout << "Enter sum: ";
			cin >> money;
			Ob -= money;
			//Ob.MinusMoney(money);
			Ob.Display();
			break;
		}

		case 3:
		{
			int money;
			cout << "Enter sum: ";
			cin >> money;
			//Ob.PlusMoney(money);
			Ob += money;
			Ob.Display();
			break;
		}

		case 4:
		{
			Ob.AddPercent();
			Ob.Display();
			break;
		}
		double ans;
		case 5:
		{
			ans=Ob.TransferMoneyInDollar();
			cout << "Answer: " << ans << endl;
			break;
		}

		case 6:
		{
			ans=Ob.TransferMoneyInEuro();
			cout << "Answer: " << ans << endl;
			break;
		}

		default:
		{
			cout << "Enter. Input corrcet nunber of menu." << endl;
			Task();
			break;
		}
		}
	} while (Check());
}

int main()
{
	Task();
	system("pause");
	return 0;
}
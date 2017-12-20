#include "stdafx.h"
#include "Account.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
const int dollar = 60;
int euro = 70;

Account:: Account(string n, int acc, double per, double m)
	{
		name = n;
		accnum = acc;
		percent = per;
		money = m;
}

Account::~Account()
{
}

//сменить владельца счета
void Account::ChangeOwner(string n)
{
	name = n;
}

//переопределение сложения
void Account::operator +(int m)
{
	this->money += m;
}

//переопределения вычитания
void Account::operator -(int m)
{
	this->money -= m;
}

//снятие денег
void Account::MinusMoney(int sum)
{
	money -= sum;
}

//добавление денег
void Account::PlusMoney(int sum)
{
	money += sum;
}

//перевод в евро
double Account::TransferMoneyInEuro() const 
{
	return money / euro;
}

//перевод в доллары
double Account::TransferMoneyInDollar() const
{
	return money / dollar;
}

//начисление процентов
void Account::AddPercent()
{
	money = money*(1 + percent / 100);
}

//вывод
void Account::Display()
{
	cout << "FIO: " << name << endl;
	cout << "Account: " << accnum << endl;
	cout << "Percent: " << percent << endl;
	cout << "Money: " << money << endl;
}

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

//������� ��������� �����
void Account::ChangeOwner(string n)
{
	name = n;
}

//��������������� ��������
void Account::operator +(int m)
{
	this->money += m;
}

//��������������� ���������
void Account::operator -(int m)
{
	this->money -= m;
}

//������ �����
void Account::MinusMoney(int sum)
{
	money -= sum;
}

//���������� �����
void Account::PlusMoney(int sum)
{
	money += sum;
}

//������� � ����
double Account::TransferMoneyInEuro() const 
{
	return money / euro;
}

//������� � �������
double Account::TransferMoneyInDollar() const
{
	return money / dollar;
}

//���������� ���������
void Account::AddPercent()
{
	money = money*(1 + percent / 100);
}

//�����
void Account::Display()
{
	cout << "FIO: " << name << endl;
	cout << "Account: " << accnum << endl;
	cout << "Percent: " << percent << endl;
	cout << "Money: " << money << endl;
}

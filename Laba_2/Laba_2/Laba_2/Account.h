#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Account
{
private:
	string name;// фио клиента
	unsigned int accnum;// номер счета
	double percent;// проценты
	double money;//сумма в рублях 

public:

	Account(string n, int acc, double per, double m);

	~Account();

	//сменить владельца счета
	void ChangeOwner(string n);

	//переопределение сложения
	void operator +=(int m);

	//переопределения вычитания
	void operator -=(int m);

	//снятие денег
	void MinusMoney(int sum);

	//добавление денег
	void PlusMoney(int sum);

	//перевод в евро
	double TransferMoneyInEuro() const;

	//перевод в доллары
	double TransferMoneyInDollar() const;

	//начисление процентов
	void AddPercent();

	//вывод
	void Display();
};
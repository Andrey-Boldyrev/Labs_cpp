#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Account
{
private:
	string name;// ��� �������
	unsigned int accnum;// ����� �����
	double percent;// ��������
	double money;//����� � ������ 

public:

	Account(string n, int acc, double per, double m);

	~Account();

	//������� ��������� �����
	void ChangeOwner(string n);

	//��������������� ��������
	void operator +(int m);

	//��������������� ���������
	void operator -(int m);

	//������ �����
	void MinusMoney(int sum);

	//���������� �����
	void PlusMoney(int sum);

	//������� � ����
	double TransferMoneyInEuro() const;

	//������� � �������
	double TransferMoneyInDollar() const;

	//���������� ���������
	void AddPercent();

	//�����
	void Display();
};
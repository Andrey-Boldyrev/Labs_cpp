#pragma once
//AccauntFuncLib.h

namespace std
{

	class Account
	{
		string name;// ��� �������
		unsigned int accnum;// ����� �����
		double percent;// ��������
		double money;//����� � ������ 

	public:

		Account(string n,  int acc, double per, double m)
		{
			name = n;
			accnum = acc;
			percent = per;
			money = m;
		}

		//������� ��������� �����
		void ChangeOwner(string n)
		{
			name = n;
		}

		//��������������� ��������
		void operator +(int m)
		{
			this->money += m;
		}

		//��������������� ���������
		void operator -(int m)
		{
			this->money -= m;
		}

		//������ �����
		void MinusMoney( int sum)
		{
			money -= sum;
		}

		//���������� �����
		void PlusMoney(int sum)
		{
			money += sum;
		}

		//������� � ����
		void TransferMoneyInEuro()
		{
			money = money / 70;
		}

		//������� � �������
		void TransferMoneyInDollar()
		{
			money = money / 60;
		}

		//���������� ���������
		void AddPercent()
		{
			money = money*(1 + percent / 100);
		}

		//�����
		void Display()
		{
			cout << "FIO: " << name << endl;
			cout << "Account: " << accnum << endl;
			cout << "Percent: " << percent << endl;
			cout << "Money: " << money << endl;
		}
	};
}
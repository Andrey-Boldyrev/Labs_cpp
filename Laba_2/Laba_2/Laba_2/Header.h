#pragma once
//AccauntFuncLib.h

namespace std
{

	class Account
	{
		string name;// фио клиента
		unsigned int accnum;// номер счета
		double percent;// проценты
		double money;//сумма в рублях 

	public:

		Account(string n,  int acc, double per, double m)
		{
			name = n;
			accnum = acc;
			percent = per;
			money = m;
		}

		//сменить владельца счета
		void ChangeOwner(string n)
		{
			name = n;
		}

		//переопределение сложения
		void operator +(int m)
		{
			this->money += m;
		}

		//переопределения вычитания
		void operator -(int m)
		{
			this->money -= m;
		}

		//снятие денег
		void MinusMoney( int sum)
		{
			money -= sum;
		}

		//добавление денег
		void PlusMoney(int sum)
		{
			money += sum;
		}

		//перевод в евро
		void TransferMoneyInEuro()
		{
			money = money / 70;
		}

		//перевод в доллары
		void TransferMoneyInDollar()
		{
			money = money / 60;
		}

		//начисление процентов
		void AddPercent()
		{
			money = money*(1 + percent / 100);
		}

		//вывод
		void Display()
		{
			cout << "FIO: " << name << endl;
			cout << "Account: " << accnum << endl;
			cout << "Percent: " << percent << endl;
			cout << "Money: " << money << endl;
		}
	};
}
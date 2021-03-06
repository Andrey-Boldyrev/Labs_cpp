// Laba_5.cpp: определяет точку входа для консольного приложения.

/* Результатом должна быть консольная программа с текстовым меню. Программа
должна содержать шаблонный класс для управления данными согласно заданию.
Для хранения данных необходимо выбрать оптимальный с точки зрения задания
контейнер.
1. Предусмотреть операции добавления, изменения и удаления элемента
контейнера.
2. Реализовать ввод и вывод элементов контейнера с использованием потоковых
итераторов на экран и в файл.
3. Реализовать операции поиска по заданным критериям и выборки подмножества
элементов по заданным критериям. Реализовать поиск в двух вариантах: линейный
поиск и двоичный поиск на отсортированном контейнере.
4. Предусмотреть вывод подмножества выборки на экран и в файл.

Структура записи о коммунальном платеже содержит поля: адрес квартиры,
фамилия владельца, вид платежа, дата платежа, сумма платежа, процент пени,
количество дней просрочки платежа. Поиск по номеру дома, квартиры, владельцу,
дате, наличии долга. Вывод суммы долга в результатах поиска. */

#include "stdafx.h"
#include "locale.h"	
#include "Kom_plat.h"





void expor_vect(vector<kom_plat> v) {
	char print_choise;
	cout << "1.On screen\n2.In file\n";
	cin >> print_choise;
	switch (print_choise) {
	case '1':print_v(v);
		break;
	case '2':save_binary(v);
		break;
	default: cout << "\nError\n";
	}
}

int main(int argc, _TCHAR* argv[])
{
	vector<kom_plat> vect;
	char choise;
	do {
		cout << "Menu:\n1.Add.\n2.Print\n3.Delete\n4.Exchange\n5.Find\n6.Load from file\n0.Exit.\n";
		cin >> choise;
		switch (choise) {
		case '1':
			add_v(vect);
			break;
		case '2':
			expor_vect(vect);
			break;
		case '3':
			delete_v(vect);
			break;
		case '4':
			exchange_v(vect);
			break;
		case '5':
			expor_vect(search(vect));
			break;
		case '6':
			load_file(vect);
			break;
		default:
			if (choise != '0') cout << "\nError, Input number from 0 to 9\n";
		}
	} while (choise != '0');
	return 0;
}
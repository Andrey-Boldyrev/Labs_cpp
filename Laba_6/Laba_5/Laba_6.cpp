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
#include "Kom_plat.h"

//вывод вектора
void expor_vect(vector<kom_plat> v) {
	int choise = -1;
	string print_choise;
	cout << "1.On screen\n2.In file\n";
	cin >> print_choise;
	if (correct_number(print_choise))  choise = stoi(print_choise);
	switch (choise) {
	case 1:print_v(v);
		break;
	case 2:save_binary(v);
		break;
	default: cout << "\nError\n";
	}
}

//выбор под кем зайти
int StartMenu() 
{
	int choise = -1;
	string print_choise;
	cout << "--------------------------------------------------------" << endl;
	cout << "            Directory of  utility company" << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "Enter as:" << endl;
	cout << "1 - Client" << endl;
	cout << "2 - Admin" << endl;
	cout << "0 - Cancel" << endl;
	cout << "--------------------------------------------------------" << endl;
	cin >> print_choise;
	if (correct_number(print_choise))  choise = stoi(print_choise);
	return choise;
}

//меню клиента
int MenuClient()
{
	int choise = -1;
	string print_choise;
	cout << "--------------------------------------------------------" << endl;
	cout << "1 - Search" << endl;
	cout << "2 - Print directory" << endl;
	cout << "0 - Cancel" << endl;
	cout << "--------------------------------------------------------" << endl;
	cin >> print_choise;
	if (correct_number(print_choise))  choise = stoi(print_choise);
	return choise;
}

//меню админа
int MenuAdmin()
{
	int choise = -1;
	string print_choise;
	cout << "--------------------------------------------------------" << endl;
	cout << "                   Administration" << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "Menu:\n1.Add.\n2.Print\n3.Delete\n4.Exchange\n5.Find\n0.Exit.\n"; //добавить напечатать удалить заменить поиск
	cout << "--------------------------------------------------------" << endl;
	cin >> print_choise;
	if (correct_number(print_choise))  choise = stoi(print_choise);
	return choise;
}


int main(int argc, _TCHAR* argv[])
{
	vector<kom_plat> vect;
	load_binary_file(vect);
	bool modify = false;
	int first_choise,second_choise;
	do {
		first_choise = StartMenu();
		switch (first_choise) {
		case 1:
			do {
				second_choise = MenuClient();
				switch (second_choise) {
				case 1:
					search(vect);
					print_v(vect);
					break;
				case 2: 
					print_v(vect);
					break;
				default:
					if (second_choise != 0) cout << "\nError, Input number from 0 to 2\n";
				}
			} while (second_choise != 0);
			break;
		case 2:
			do {
				second_choise = MenuAdmin();
				switch (second_choise) {
				case 1:
					add_v(vect);
					modify = true;
					break;
				case 2:
					expor_vect(vect);
					break;
				case 3:
					delete_v(vect);
					modify = true;
					break;
				case '4':
					exchange_v(vect);
					modify = true;
					break;
				case '5':
					expor_vect(search(vect));
					break;
				default:
					if (second_choise != 0) cout << "\nError, Input number from 0 to 5\n";
				}
				if (modify) save_binary(vect);
			} while (second_choise != 0);
			break;		
		default:
			if (first_choise != 0) cout << "\nError, Input number from 0 to 2\n";
		}
	} while (first_choise != 0);
	return 0;
}
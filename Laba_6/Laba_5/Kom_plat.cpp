#include "stdafx.h"
#include "Kom_plat.h"


kom_plat::kom_plat()
{
	date *d = new date();
	d->day = 0;
	d->month = 0;
	d->year = 0;
	
	house = 0;
	room = 0;
	street = "";
	FIO = "";
	pay_type = "";
	pay_date = *d;
	pay_cost = 0;
	peni_percent = 0;
	day_delay_pay = 0;
}

kom_plat::kom_plat(string AFIO,string Astreet,int Ahouse, int Aroom,   string Apay_type, date Apay_date, int Apay_cost,
	int Apeni_percent, int Aday_delay_pay)
{
	FIO = AFIO;
	house = Ahouse;
	room = Aroom;
	street = Astreet;
	pay_type = Apay_type;
	pay_date = Apay_date;
	pay_cost = Apay_cost;
	peni_percent = Apeni_percent;
	day_delay_pay = Aday_delay_pay;	
}

kom_plat::~kom_plat(){}


bool correct_symbol(char c) {
	switch (c)
	{
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case '0':
		return true;
	default:
		return false;
	}
}

//проверка на корректный цифру
bool correct_number(string s) {
	bool is_correct = true;
	for (int i = 0; ((i < s.length()) && (is_correct)); i++) {
		is_correct = correct_symbol(s[i]);
	}
	is_correct = is_correct && (s.length() < 9);
	return is_correct;

}

//перевод даты в строку
string date_to_str(date d) {
	string result;
	result = to_string(d.day) + "." + to_string(d.month) + "." + to_string(d.year);
	return result;
}

//строка в дату
date str_to_date(string str) {
	date result;

	result.day = (int)(str[0] - '0');
	int i = 1;
	while (str[i] != '.') {
		result.day *= 10;
		result.day += (int)(str[i] - '0');
		i++;
	}
	i++;
	result.month = (int)(str[i] - '0');
	i++;
	while (str[i] != '.') {
		result.month *= 10;
		result.month += (int)(str[i] - '0');
		i++;
	}
	i++;
	result.year = (int)(str[i] - '0');
	i++;
	while (i < str.length()) {
		result.year *= 10;
		result.year += (int)(str[i] - '0');
		i++;
	}
	return result;
}

void kom_plat::print_record() 
{
	cout << FIO << "\t" << street << ";" << house << ";" << room << "\t\t" << pay_type << "\t\t" << pay_cost
		<< "\t\t" << peni_percent << "\t\t" << day_delay_pay << "\t\t\t" << pay_date.day
		<< "." << pay_date.month << "." << pay_date.year << "\n";
}
//вывод на экран
void print_v(vector<kom_plat> &v)
{
	cout << "FIO\t\tAddress\t\tPay type\tPay cost\tPeni percent\tDays delay payment\tPay date" << endl;
	for (vector<kom_plat>::iterator it = v.begin(); it != v.end(); it++) (*it).print_record();
}

// чтение строки из бинарного файла
bool string_from_bin(ifstream& in, string &str)
{
	__int64 len;
	if (in.read((char *)(&len), sizeof(len))) {
		char * buf = new char[len];
		if (in.read((char *)(buf), len)) {
			str = buf;
			return true;
		}
	}
	return false;
}

//чтение одной записи
bool load_one_rec(ifstream& in, kom_plat &plat) {
	bool result = true;
	string tmp_str;
	if (string_from_bin(in, tmp_str)) plat.FIO = (tmp_str);
	else result = false;
	if (result&&string_from_bin(in, tmp_str)) plat.room=(stoi(tmp_str));
	else result = false;
	if (result&&string_from_bin(in, tmp_str)) plat.house= (stoi(tmp_str));
	else result = false;
	if (result&&string_from_bin(in, tmp_str)) plat.street=(tmp_str);
	else result = false;
	if (result&&string_from_bin(in, tmp_str)) plat.pay_type=(tmp_str);
	else result = false;
	if (result&&string_from_bin(in, tmp_str)) plat.pay_date=(str_to_date(tmp_str));
	else result = false;
	if (result&&string_from_bin(in, tmp_str)) plat.pay_cost=(stoi(tmp_str));
	else result = false;
	if (result&&string_from_bin(in, tmp_str)) plat.peni_percent=(stoi(tmp_str));
	else result = false;
	if (result&&string_from_bin(in, tmp_str)) plat.day_delay_pay=(stoi(tmp_str));
	else result = false;
	return result;
}
//загрузка из бинарного файла
void load_binary_file(vector<kom_plat> &vect) 
{
	string filename ="1.dat";
	ifstream in(filename, ios::binary);
	if (!in.is_open()) {
		cout << "Enabled to open file\n";
		return;
	}
	if (in.eof())
	{
		cout << "file is empty\n";
		return;
	}
	else
	{
		kom_plat plat;
		while (load_one_rec(in, plat)) 
		{
		vect.push_back(plat);
	}
	}
	in.close();
}


// запись строки в бинарный файл
void string_to_bin(ofstream& out, string str)
{
	__int64 len = str.length() + 1;
	const char *buf = str.c_str();
	out.write((char *)(&len), sizeof(len));
	out.write((char *)(buf), len);
}

//сохранение в бинарный файл
void save_binary(vector<kom_plat> &v) {
	string filename = "1.dat";
	string tmp_str;
	ofstream out(filename, ios_base::out | ios_base::trunc);
	for (auto &plat : v)
	{
		string_to_bin(out, plat.FIO);
		string_to_bin(out, to_string(plat.room));
		string_to_bin(out, to_string(plat.house));
		string_to_bin(out, plat.street);
		string_to_bin(out, plat.pay_type);
		string_to_bin(out, date_to_str(plat.pay_date));
		string_to_bin(out, to_string(plat.pay_cost));
		string_to_bin(out, to_string(plat.peni_percent));
		string_to_bin(out, to_string(plat.day_delay_pay));
	}
	out.close();
}

bool contains(vector<kom_plat> v, string str) {
	for (vector<kom_plat>::iterator it = v.begin(); it != v.end(); it++) {
		if ((*it).FIO == str) return true;
	}
	return false;
}

kom_plat input_kom_plat() {
	string tmp_FIO;
	int tmp_room;
	int tmp_house;
	string tmp_street;
	string tmp_pay_type;
	int tmp_pay_cost;
	int tmp_peni_percent;
	int tmp_day_delay_pay;
	date tmp_pay_date;
	
	cout << "\nInput fio: ";
	cin >> tmp_FIO;

	cout << "\nInput address: (street,house,room through the space) ";
	cin >> tmp_street>> tmp_house>> tmp_room;

	cout << "\nInput pay type: ";
	cin >> tmp_pay_type;

	do {
		cout << "\nInput sum of payment: ";
		cin >> tmp_pay_cost;
	} while (tmp_pay_cost<1);

	do {
		cout << "\nInput percent of peni: ";
		cin >> tmp_peni_percent;
	} while(tmp_peni_percent < 0);
	
	do {
		cout << "\nInput number of days of delay in payments: ";
		cin >> tmp_day_delay_pay;
	} while (tmp_day_delay_pay < 0);
	cout << "\nInput date of payment (day,month, year through the space): ";
	cin >> tmp_pay_date.day >> tmp_pay_date.month >> tmp_pay_date.year;
	
	kom_plat tmp(tmp_FIO, tmp_street, tmp_house, tmp_room, tmp_pay_type,  tmp_pay_date, tmp_pay_cost,
		tmp_peni_percent, tmp_day_delay_pay);
	return tmp;
}

void add_v(vector<kom_plat> &v) {
	kom_plat cur = input_kom_plat();
	v.insert(v.end(), cur);
	cout << "Record added!" << endl;
}

void delete_v(vector<kom_plat> &v) {
	string str;
	cout << "Input abonents's FIO for delete: ";
	cin >> str;
	vector<kom_plat>::iterator it = v.begin();
	while (it != v.end() && (*it).FIO != str ) it++;
	if (it != v.end())
	{
		v.erase(it);
		cout << "Abonent deleted!" << endl;
	}
	else cout << "Such abonent doesn't exist!" << endl;
}

void exchange_v(vector<kom_plat> &v) {
	string str;
	cout << "Input abonent's FIO for exchange: ";
	cin >> str;
	vector<kom_plat>::iterator it = v.begin();
	while ((*it).FIO != str && it != v.end()) it++;
	if (it != v.end())
	{
		v.erase(it);
		add_v(v);
	}//заменить по запросу!
	else cout << "Such abonent doesn't exist!" << endl;
}

//компараторы
static bool FIO_rec_plat( kom_plat &r,  kom_plat &b) //ФИО
{
	return r.FIO < b.FIO;

}
static bool FIO_plat( kom_plat &r, string value)
{
	return (r.FIO < value);
}

static bool delayPay_rec_plat( kom_plat &r,  kom_plat &b) //наличие долга
{
	return r.day_delay_pay < b.day_delay_pay;

}
static bool delayPay_plat( kom_plat &r, int value)
{
	return (r.day_delay_pay < value);
}

static bool date_rec_plat( kom_plat &r,  kom_plat &b)//дата платежа
{
	return (r.pay_date.year < b.pay_date.year) ||
		((r.pay_date.year == b.pay_date.year) && (r.pay_date.month < b.pay_date.month)) ||
		((r.pay_date.year == b.pay_date.year) && (r.pay_date.month == b.pay_date.month) &&
		(r.pay_date.day < b.pay_date.day));
}
static bool date_plat( kom_plat &r, date value)
{
	return (r.pay_date.year < value.year) ||
		((r.pay_date.year == value.year) && (r.pay_date.month < value.month)) ||
		((r.pay_date.year == value.year) && (r.pay_date.month == value.month) &&
		(r.pay_date.day < value.day));
}

static bool room_rec_plat( kom_plat &r,  kom_plat &b)//номер комнаты
{
	return r.room < b.room;
}
static bool room_plat( kom_plat &r, int value)
{
	return r.room < value;
}

static bool house_rec_plat( kom_plat &r,  kom_plat &b)//номер дома
{
	return r.house < b.house;
}
static bool house_plat( kom_plat &r, int value)
{
	return r.house < value;
}

//--------------------------------------------------------------

bool equals_FIO( kom_plat & a, string strquery) {
	if (a.FIO == strquery) return true;
	return false;
}

bool equals_delay_pay( kom_plat & a, int intquery) {
	if (a.day_delay_pay == intquery) return true;
	return false;
}

bool equals_room( kom_plat & a, int intquery) {
	if (a.room == intquery) return true;
	return false;
}

bool equals_house( kom_plat & a, int intquery) {
	if (a.house == intquery) return true;
	return false;
}

bool equals_date( kom_plat & a, date datequery) {
	if (a.pay_date.day == datequery.day &&
		a.pay_date.month == datequery.month &&
		a.pay_date.year == datequery.year)
		return true;
	return false;
}

template <class T>
vector<kom_plat> lin_search(T search_elem,vector<kom_plat> &v, bool(*equals)(kom_plat &, T)) {
	vector<kom_plat> results;
	vector<kom_plat>::iterator v_it = v.begin();
	
	while (v_it != v.end())
	{
		if (equals(*v_it, search_elem)) results.insert(results.end(), *v_it);
		v_it++;
	}
	return results;
}

template <class T>
vector<kom_plat> bin_search(T search_elem, vector<kom_plat> &v, bool(*comparator_rec)(kom_plat &, kom_plat &),
	bool(*comparator)(kom_plat &, T), bool(*equals)(kom_plat &, T))
{
	vector<kom_plat> results;

	sort(v.begin(), v.end(), comparator_rec);
	auto index = std::lower_bound(v.begin(), v.end(), search_elem, comparator);
	int left = 0;
	int right = (int)v.size();
	if (index != v.end() && !comparator(*index, search_elem))
	{
		results.insert(results.end(), *index);
		while ((++index != v.end()) && (equals(*index, search_elem)))
		{
			results.insert(results.end(), *index);

		}
	}
	return results;
}

vector<kom_plat> search(vector<kom_plat> &v) {
	vector<kom_plat> results;
	vector<kom_plat>::iterator v_it = v.begin();
	int choise, type;
	do
	{
		cout << "Choose parameter of search:\n1.FIO\n2.Room\n3.House\n4.Number of days with delay payment\n5.Pay date\n";
		cin >> choise;
	} while (choise<1 || choise>5);
	do
	{
		cout << "Choose algorithm of search:\n1.Linear\n2.Binary\n";
		cin >> type;
	} while (type<1 || type>2);
	cout << "Input inquiry:";
	switch (type)
	{
	case 1:
	{
		switch (choise)
		{
		case 1: {
			string strquery;
			cin >> strquery;
			results = lin_search(strquery, v, equals_FIO); }
				break;
		case 2: {
			int intquery;
			cin >> intquery;
			results = lin_search(intquery, v, equals_room); }
				break;
		case 3: {
			int intquery;
			cin >> intquery;
			results = lin_search(intquery, v, equals_house); }
				break;
		case 4: {
			int intquery;
			cin >> intquery;
			results = lin_search(intquery, v, equals_delay_pay); }
				break;
		case 5: {
			cout << "day,month, year through the space";
			date datequery;
			cin >> datequery.day >> datequery.month >> datequery.year;
			results = lin_search(datequery, v, equals_date); }
				break;
		}
	} break;

	case 2:
	{
		switch (choise)
		{
		case 1: {
			string strquery;
			cin >> strquery;
			results = bin_search(strquery, v, FIO_rec_plat, FIO_plat, equals_FIO); }
				break;
		case 2: {
			int intquery;
			cin >> intquery;
			results = bin_search(intquery, v, room_rec_plat, room_plat, equals_room); }
				break;
		case 3: {
			int intquery;
			cin >> intquery;
			results = bin_search(intquery, v, house_rec_plat, house_plat, equals_house); }
				break;
		case 4: {
			int intquery;
			cin >> intquery;
			results = bin_search(intquery, v, delayPay_rec_plat, delayPay_plat, equals_delay_pay); }
				break;
		case 5: {
			cout << "day,month, year through the space: ";
			date datequery;
			cin >> datequery.day >> datequery.month >> datequery.year;
			results = bin_search(datequery, v, date_rec_plat, date_plat, equals_date); }
				break;
		}
	} break;
	}
	return results;
}
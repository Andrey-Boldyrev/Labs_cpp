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

kom_plat::~kom_plat()
{

}

void kom_plat::print_record()
{
	cout << FIO << "\t" << street << ";" << house << ";"<<room<<"\t" << "\t" << pay_type << "\t" << pay_cost
		<< "\t" << peni_percent << "\t" << day_delay_pay << "\t\t" << pay_date.day
		<< "." << pay_date.month << "." << pay_date.year << "\n";
}

string input_filename() {
	string filename;
	do {
		cout << "Input file name\n";
		cin >> filename;
	} while (filename == "");
	return filename;
}

void load_file(vector<kom_plat> &vect) {

	string filename = input_filename();

	ifstream in(filename, ios::binary);
	if (!in.is_open()) {
		cout << "Enabled to open file\n";
		return;
	}
	else {
		while (!in.eof())
		{
			kom_plat *plat = new kom_plat();
			in.read((char*)&plat, sizeof(kom_plat));
			vect.insert(vect.end(), *plat);
		}
	}
	in.close();
}

void print_v(vector<kom_plat> &v) {
	cout << "FIO\t\tAddress\tPay type\tPay cost\tPeni percent\tNumber of days with delay payment\tPay date" << endl;
	for (vector<kom_plat>::iterator it = v.begin(); it != v.end(); it++) (*it).print_record();
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
	if (!contains(v, cur.FIO)) {
		v.insert(v.end(), cur);
		cout << "Record added!" << endl;
	}
	else cout << "Such abonent already exist.\n";

}

void delete_v(vector<kom_plat> &v) {
	string str;
	cout << "Input abonents's FIO for delete: ";
	cin >> str;
	vector<kom_plat>::iterator it = v.begin();
	while ((*it).FIO != str && it != v.end()) it++;
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

void save_binary(vector<kom_plat> &v) {
	string filename = input_filename();
	ofstream out(filename, ios::binary);
	for  (auto &plat:v)
	{
		out.write((char*)&plat, sizeof(kom_plat));
	}
	out.close();
}

void save_file(vector<kom_plat> &v) {
	string filename = input_filename();
	ofstream file;
	file.open(filename, ios::out);
	for (vector<kom_plat>::iterator it = v.begin(); it != v.end(); it++)
	{
		file << (*it).FIO << "\t\t" << (*it).street<<";"<< (*it).house<<";"
			<< (*it).room<<";" << "\t" << (*it).pay_type << "\t" << (*it).pay_cost << "\t"
			<< (*it).peni_percent << "\t" << (*it).day_delay_pay << "\t\t" << (*it).pay_date.day
			<< "." << (*it).pay_date.month << "." << (*it).pay_date.year << endl;
	}
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


vector<kom_plat> lin_str(vector<kom_plat> &v, bool(*equals)( kom_plat &, string)) {
	vector<kom_plat> results;
	vector<kom_plat>::iterator v_it = v.begin();
	string strquery;
	cin >> strquery;

	while (v_it != v.end())
	{
		if (equals(*v_it, strquery)) results.insert(results.end(), *v_it);
		v_it++;
	}
	return results;
}

vector<kom_plat> lin_int(vector<kom_plat> &v, bool(*equals)( kom_plat &, int)) {
	vector<kom_plat> results;
	vector<kom_plat>::iterator v_it = v.begin();
	int intquery;
	cin >> intquery;

	while (v_it != v.end())
	{
		if (equals(*v_it, intquery)) results.insert(results.end(), *v_it);
		v_it++;
	}
	return results;
}

vector<kom_plat> lin_date(vector<kom_plat> &v, bool(*equals)( kom_plat &, date)) {
	vector<kom_plat> results;
	vector<kom_plat>::iterator v_it = v.begin();
	cout << "day,month, year through the space";
	date datequery;
	cin >> datequery.day >> datequery.month >> datequery.year;

	while (v_it != v.end())
	{
		if (equals(*v_it, datequery))
			results.insert(results.end(), *v_it);
		v_it++;
	}
	return results;
}

vector<kom_plat> bin_str(vector<kom_plat> &v, bool(*comparator_rec)( kom_plat &,  kom_plat &),
	bool(*comparator)( kom_plat &, string), bool(*equals)( kom_plat &, string)) {
	vector<kom_plat> results;
	vector<kom_plat>::iterator v_it = v.begin();
	string strquery;
	cin >> strquery;

	sort(v.begin(), v.end(), comparator_rec);
	v_it = lower_bound(v.begin(), v.end(), strquery, comparator);
	while (equals(*v_it, strquery)) {
		results.insert(results.end(), *v_it);
		v_it++;
	}
	return results;
}

vector<kom_plat> bin_int(vector<kom_plat> &v, bool(*comparator_rec)( kom_plat &,  kom_plat &),
	bool(*comparator)( kom_plat &, int), bool(*equals)( kom_plat &, int)) {
	vector<kom_plat> results;
	vector<kom_plat>::iterator v_it = v.begin();
	int intquery;
	cin >> intquery;

	sort(v.begin(), v.end(), comparator_rec);
	v_it = lower_bound(v.begin(), v.end(), intquery, comparator);
	while (equals(*v_it, intquery)) {
		results.insert(results.end(), *v_it);
		v_it++;
	}
	return results;
}



vector<kom_plat> bin_date(vector<kom_plat> &v, bool(*comparator_rec)( kom_plat &,  kom_plat &),
	bool(*comparator)( kom_plat &, date), bool(*equals)( kom_plat &, date)) {
	vector<kom_plat> results;
	vector<kom_plat>::iterator v_it = v.begin();
	cout << "day,month, year through the space";
	date datequery;
	cin >> datequery.day >> datequery.month >> datequery.year;

	sort(v.begin(), v.end(), comparator_rec);
	v_it = lower_bound(v.begin(), v.end(), datequery, comparator);
	while (equals(*v_it, datequery)) {
		results.insert(results.end(), *v_it);
		v_it++;
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
		case 1:
			results = lin_str(v, equals_FIO);
			break;
		case 2:
			results = lin_int(v, equals_room);
			break;
		case 3:
			results = lin_int(v, equals_house);
			break;
		case 4:
			results = lin_int(v, equals_delay_pay);
			break;
		case 5:
			results = lin_date(v, equals_date);
			break;
		}
	} break;

	case 2:
	{
		switch (choise)
		{
		case 1:
			results = bin_str(v, FIO_rec_plat, FIO_plat, equals_FIO);
			break;
		case 2:
			results = bin_int(v, room_rec_plat, room_plat, equals_room);
			break;
		case 3:
			results = bin_int(v, house_rec_plat,house_plat, equals_house);
			break;
		case 4:
			results = bin_int(v, delayPay_rec_plat, delayPay_plat, equals_delay_pay);
			break;
		case 5:
			results = bin_date(v, date_rec_plat, date_plat, equals_date);
			break;
		}
	} break;
	}
	return results;
}
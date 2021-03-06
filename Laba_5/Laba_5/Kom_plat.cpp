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
	cout << FIO << "\t" << street << ";" << house << ";"<<room<<"\t\t"  << pay_type << "\t\t" << pay_cost
		<< "\t\t" << peni_percent << "\t\t" << day_delay_pay << "\t\t\t" << pay_date.day
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
	cout << "FIO\t\tAddress\t\tPay type\tPay cost\tPeni percent\tDays delay payment\tPay date" << endl;
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
	//if (!contains(v, cur.FIO)) {
		v.insert(v.end(), cur);
		cout << "Record added!" << endl;
	//}
	//else cout << "Such abonent already exist.\n";

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
	}//�������� �� �������!
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

//�����������
static bool FIO_rec_plat( kom_plat &r,  kom_plat &b) //���
{
	return r.FIO < b.FIO;

}
static bool FIO_plat( kom_plat &r, string value)
{
	return (r.FIO < value);
}

static bool delayPay_rec_plat( kom_plat &r,  kom_plat &b) //������� �����
{
	return r.day_delay_pay < b.day_delay_pay;

}
static bool delayPay_plat( kom_plat &r, int value)
{
	return (r.day_delay_pay < value);
}

static bool date_rec_plat( kom_plat &r,  kom_plat &b)//���� �������
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

static bool room_rec_plat( kom_plat &r,  kom_plat &b)//����� �������
{
	return r.room < b.room;
}
static bool room_plat( kom_plat &r, int value)
{
	return r.room < value;
}

static bool house_rec_plat( kom_plat &r,  kom_plat &b)//����� ����
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
vector<kom_plat> lin_search(T search_elem, vector<kom_plat> &v, bool(*equals)(kom_plat &, T)) {
	vector<kom_plat> results;
	vector<kom_plat>::iterator v_it = v.begin();

	while (v_it != v.end())
	{
		if (equals(*v_it, search_elem)) results.insert(results.end(), *v_it);
		v_it++;
	}
	return results;
}

/*
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
*/


/*template <class Type>
vector<Type> Task<Type>::BinarySearch(Type find_element, bool(*Compare)(Type, Type), bool(*Equal)(Type, Type))
{
	vector<Type> NewVect;

	sort(vect.begin(), vect.end(), Compare);
	auto index = std::lower_bound(vect.begin(), vect.end(), find_element, Compare);
	int left = 0;
	int right = vect.size();
	if (index != vect.end() && !Compare(*index, find_element))
	{
		NewVect.push_back(*index);
		while ((++index != vect.end()) && Equal(*index, find_element))
		NewVect.push_back(*index);
	}
	return NewVect;
}*/

/*
template <class T>
vector<kom_plat> bin_search(T search_elem, vector<kom_plat> &v, bool(*comparator_rec)(kom_plat &, kom_plat &),
	bool(*comparator)(kom_plat &, T), bool(*equals)(kom_plat &, T)) 
{
	vector<kom_plat> results;
	vector<kom_plat>::iterator v_it = v.begin();

	sort(v.begin(), v.end(), comparator_rec);
	v_it = lower_bound(v.begin(), v.end(), search_elem, comparator);
	while (equals(*v_it, search_elem)) 
	{
		results.insert(results.end(), *v_it);
		v_it++;
	}
	return results;
}*/

template <class T>
vector<kom_plat> bin_search(T search_elem, vector<kom_plat> &v, bool(*comparator_rec)(kom_plat &, kom_plat &),
	bool(*comparator)(kom_plat &, T), bool(*equals)(kom_plat &, T))
{
	vector<kom_plat> results;
	vector<kom_plat>::iterator v_it = v.begin();

	sort(v.begin(), v.end(), comparator_rec);
	auto index = std::lower_bound(v.begin(), v.end(), search_elem, comparator);
	int left = 0;
	int right = v.size();
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




/*
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
}*/

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
			results = lin_search(strquery,v, equals_FIO); }
			break;
		case 2: {
			int intquery;
			cin >> intquery;
			results = lin_search(intquery,v, equals_room); }
			break;
		case 3: {
			int intquery;
			cin >> intquery;
			results = lin_search(intquery,v, equals_house); }
			break;
		case 4: {
			int intquery;
			cin >> intquery;
			results = lin_search(intquery,v, equals_delay_pay); }
			break;
		case 5: {
			cout << "day,month, year through the space: ";
			date datequery;
			cin >> datequery.day >> datequery.month >> datequery.year;
			results = lin_search(datequery,v, equals_date); }
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
			results = bin_search(strquery,v, FIO_rec_plat, FIO_plat, equals_FIO); }
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
			results = bin_search(intquery,v, delayPay_rec_plat, delayPay_plat, equals_delay_pay); }
			break;
		case 5: {
			cout << "day,month, year through the space: ";
			date datequery;
			cin >> datequery.day >> datequery.month >> datequery.year;
			results = bin_search(datequery,v, date_rec_plat, date_plat, equals_date); }
			break;
		}
	} break;
	}
	return results;
}
#include "stdafx.h"
#include "Task.h"

template <class Type>
Task<Type>::Task() {}

template <class Type>
Task<Type>::~Task() {}

string input_filename() {
	string filename;
	do {
		cout << "Input file name\n";
		cin >> filename;
	} while (filename == "");
	return filename;
}

template <class Type>
void Task<Type>::load_file(vector<Type> &vect) {

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

template <class Type>
void Task<Type>::print_v(vector<Type> &v) {
	cout << "FIO\t\tAddress\tPay type\tPay cost\tPeni percent\tNumber of days with delay payment\tPay date" << endl;
	for (vector<Type>::iterator it = v.begin(); it != v.end(); it++) (*it).print_record();
}

bool contains(vector<kom_plat> v, string str) {
	for (vector<kom_plat>::iterator it = v.begin(); it != v.end(); it++) {
		if ((*it).FIO == str) return true;
	}
	return false;
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
	for (auto &plat : v)
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
		file << (*it).FIO << "\t\t" << (*it).street << ";" << (*it).house << ";"
			<< (*it).room << ";" << "\t" << (*it).pay_type << "\t" << (*it).pay_cost << "\t"
			<< (*it).peni_percent << "\t" << (*it).day_delay_pay << "\t\t" << (*it).pay_date.day
			<< "." << (*it).pay_date.month << "." << (*it).pay_date.year << endl;
	}
}

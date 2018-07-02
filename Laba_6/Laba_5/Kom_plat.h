#pragma once
#include "stdafx.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <cstdlib>
#include "iostream"
using namespace std;

typedef struct date
{
	int day;
	int month;
	int year;
} date;
class kom_plat
{
public:
	string FIO;//фио владельца
	int room;
	int house;
	string street;//адрес квартиры	
	string pay_type;//тип платежа
	date pay_date;//дата платежа
	int pay_cost;//сумма платежа
	int peni_percent;//процент пени
	int day_delay_pay;//количество дней задержки платежа
	kom_plat();
	kom_plat(string FIO, string street, int house,int room,  string pay_type, date pay_date,int pay_cost, int peni_percent, int day_delay_pay);
	~kom_plat();

	void print_record();
};
kom_plat input_kom_plat();

//компораторы
static bool FIO_rec_plat( kom_plat &r,  kom_plat &b);
static bool FIO_plat( kom_plat &r, string value);
static bool delayPay_rec_plat( kom_plat &r,  kom_plat &b);
static bool delayPay_plat( kom_plat &r, int value);
static bool date_rec_plat( kom_plat &r,  kom_plat &b);
static bool date_plat( kom_plat &r, date value);
static bool room_rec_plat( kom_plat &r,  kom_plat &b);
static bool room_plat( kom_plat &r, int value);
static bool house_rec_plat( kom_plat &r,  kom_plat &b);
static bool house_plat( kom_plat &r, int value);


void load_binary_file(vector<kom_plat> &vect);
void print_v(vector<kom_plat> &v);
bool contains(vector<kom_plat> v, string n);
void add_v(vector<kom_plat> &v);
void delete_v(vector<kom_plat> &v);
void exchange_v(vector<kom_plat> &v);
bool correct_symbol(char c);
bool correct_number(string s);
void save_binary(vector<kom_plat> &v);
vector<kom_plat> search(vector<kom_plat> &v);
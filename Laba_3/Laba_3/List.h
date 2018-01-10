#pragma once
#include "stdafx.h"
#include <iostream>

using namespace std;


template <typename ValueType>
class DoublyLinkedList
{
private:
	struct Element
	{
		ValueType data;	//сами данные
		Element *next; // указатели на следующий
		Element *prev; //и на предыдущий элементы списка
		Element(const ValueType& el, Element *prev_, Element *next_)
		{
			data = el;
			prev = prev_;
			next = next_;
		}
	};
	Element *Head; // указатель на первый элемент списка
	Element *Tail; // указатель на последний элемент списка
	int countElem; // количество элементов в списке

public:
	DoublyLinkedList();	//конструктор
	~DoublyLinkedList();	//деструктор

	int get_length() const { return countElem; }// вычисление длины
	void addBackToList(const ValueType &data);	//функция добавки элемента (слова) в список
	void addBehindToList(const ValueType &data);
	void printList();	//функция вывода на экран всех элементов списка

	bool IsEmpty();
	void RemoveHeadEl();
	void RemoveTailEl();
	void DelList();//функция удаления всех элементов списка
};

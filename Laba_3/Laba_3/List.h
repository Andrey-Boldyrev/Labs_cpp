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
		ValueType data;	//���� ������
		Element *next; // ��������� �� ���������
		Element *prev; //� �� ���������� �������� ������
		Element(const ValueType& el, Element *prev_, Element *next_)
		{
			data = el;
			prev = prev_;
			next = next_;
		}
	};
	Element *Head; // ��������� �� ������ ������� ������
	Element *Tail; // ��������� �� ��������� ������� ������
	int countElem; // ���������� ��������� � ������

public:
	DoublyLinkedList();	//�����������
	~DoublyLinkedList();	//����������

	int get_length() const { return countElem; }// ���������� �����
	void addBackToList(const ValueType &data);	//������� ������� �������� (�����) � ������
	void addBehindToList(const ValueType &data);
	void printList();	//������� ������ �� ����� ���� ��������� ������

	bool IsEmpty();
	void RemoveHeadEl();
	void RemoveTailEl();
	void DelList();//������� �������� ���� ��������� ������
};

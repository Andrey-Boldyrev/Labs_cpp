#include "stdafx.h"
#include "List.h"
#include <string>

template <typename ValueType>
DoublyLinkedList<ValueType>::DoublyLinkedList()
{
	Head = nullptr;
	Tail = nullptr;
	countElem = 0;
}

template <typename ValueType>
DoublyLinkedList<ValueType>::~DoublyLinkedList()
{
	DelList();
}

//���������� ������� ���������� � ����� ������
template <typename ValueType>
void DoublyLinkedList<ValueType>::addBackToList(const ValueType &data)
{
	Element *temp = new Element(data, Tail, nullptr);	//��������� ������ ��� ����� ������� ���������
	if (Head == nullptr)	//���� ��� ������ �������, ��
	{
		//temp>prev = nullptr;	//�������� ��������� �� �������������� ������� �.�. ��� ���
		Head = Tail = temp;	//������=�����=��� �������, ��� ������ ��������
	}
	else //���� �� ������, ��
	{
		Tail->next = temp;	//���������� ��������� �� ����
		Tail = temp; //������ ����� ������
	}
	countElem++;	//����������� ������� ��������� � ������
}

//���������� ������� ���������� � ������ ������
template <typename ValueType>
void DoublyLinkedList<ValueType>::addBehindToList(const ValueType &data)
{
	Element *temp = new Element(data, nullptr, Head);	//��������� ��������� �������
	if (Head == nullptr)	//���� ��� ������ �������, ��
	{
		//	temp->prev = nullptr;	//�������� ��������� �� �������������� ������� �.�. ��� ���
		Head = Tail = temp;	//������=�����=��� �������, ��� ������ ��������
	}
	else	//���� �� ������, ��
	{
		Head->prev = temp; //��������� ��������� �� ����
		Head = temp; //������ ����� ������
	}
	countElem++;
}

//���������� ������� ������ �� ����� ������
template <typename ValueType>
void DoublyLinkedList<ValueType>::printList()
{
	//� ������
	Element* Temp = Head;	//��������� ��������� ������� //

	if (Head == nullptr)	//���� ������ ����, �� 
	{
		cout << "Spisok pust" << endl;	//������� ��������������� ���������
	}
	else	//���� �� �� ����, ��
	{
		cout << "Spisok ->: ";
		while (Temp != nullptr)	//���� ����. ����. �� ����� ��������� �� �����
		{
			ValueType ret_elem = Temp->data;
			cout << ret_elem << ' ';	//������� ������ ��������
			Temp = Temp->next;	//� ��������� �� ��������� �� ��� ����.
		}
		cout << endl;
	}
}

//�������� �� �������
template <typename ValueType>
bool DoublyLinkedList<ValueType>::IsEmpty()
{
	if (!Head) return true;
	else return false;
}

// �������� ������
template <typename ValueType>
void DoublyLinkedList<ValueType>::RemoveHeadEl()
{
	if (Head) // ���� ������ �� ������
	{
		Element* cur = Head;
		Head = cur->next;
		if (Head)
			Head->prev = nullptr;
		else Tail = nullptr;
		delete cur;
		countElem--;
	}
	else
	{
		throw invalid_argument("Head is null");
	}

}

// �������� ������
template <typename ValueType>
void DoublyLinkedList<ValueType>::RemoveTailEl()
{
	if (Tail) // ���� ������ �� ������
	{
		Element* cur = Tail;
		Tail = Tail->prev;
		if (Tail) Tail->next = nullptr;
		else Head = nullptr;
		delete cur;
		countElem--;
	}
	else
	{
		throw invalid_argument("Tail is null");
	}

}

// �������� ����� ������
template <typename ValueType>
void DoublyLinkedList<ValueType>::DelList()
{
	Element *tmp = Head;
	while (tmp) //���� �� ������ �� ������ ������ ���-�� ����
	{
		tmp = Head->next; //��������� ����� ������ ���������� ����� ������
		delete Head; //������� ������ �� ������� �����
		Head = tmp; //����� ������ ������ �� ����� ���������� ��������
	}
	countElem = 0;
}

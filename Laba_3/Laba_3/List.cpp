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

//реализация функции добавления в конец списка
template <typename ValueType>
void DoublyLinkedList<ValueType>::addBackToList(const ValueType &data)
{
	Element *temp = new Element(data, Tail, nullptr);	//Выделение памяти под новый элемент структуры
	if (Head == nullptr)	//если это первый элемент, то
	{
		//temp>prev = nullptr;	//обнуляем указатель на предшествующий элемент т.к. его нет
		Head = Tail = temp;	//Голова=Хвост=тот элемент, что сейчас добавили
	}
	else //если не первый, то
	{
		Tail->next = temp;	//предыдущий указывает на него
		Tail = temp; //Меняем адрес хвоста
	}
	countElem++;	//увеличиваем счетчик элементов в списке
}

//реализация функции добавления в начало списка
template <typename ValueType>
void DoublyLinkedList<ValueType>::addBehindToList(const ValueType &data)
{
	Element *temp = new Element(data, nullptr, Head);	//создается временный элемент
	if (Head == nullptr)	//если это первый элемент, то
	{
		//	temp->prev = nullptr;	//обнуляем указатель на предшествующий элемент т.к. его нет
		Head = Tail = temp;	//Голова=Хвост=тот элемент, что сейчас добавили
	}
	else	//если не первый, то
	{
		Head->prev = temp; //следующий указывает на него
		Head = temp; //Меняем адрес головы
	}
	countElem++;
}

//реализация функции вывода на экран списка
template <typename ValueType>
void DoublyLinkedList<ValueType>::printList()
{
	//с начала
	Element* Temp = Head;	//создается временный элемент //

	if (Head == nullptr)	//если список пуст, то 
	{
		cout << "Spisok pust" << endl;	//выводим соответствующее сообщение
	}
	else	//если он не пуст, то
	{
		cout << "Spisok ->: ";
		while (Temp != nullptr)	//пока врем. элем. не будет указывать на хвост
		{
			ValueType ret_elem = Temp->data;
			cout << ret_elem << ' ';	//выводим данные элемента
			Temp = Temp->next;	//и переходим на следующий за ним элем.
		}
		cout << endl;
	}
}

//проверка на пустоту
template <typename ValueType>
bool DoublyLinkedList<ValueType>::IsEmpty()
{
	if (!Head) return true;
	else return false;
}

// удаление головы
template <typename ValueType>
void DoublyLinkedList<ValueType>::RemoveHeadEl()
{
	if (Head) // если голова не пустая
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

// удаление хвоста
template <typename ValueType>
void DoublyLinkedList<ValueType>::RemoveTailEl()
{
	if (Tail) // если голова не пустая
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

// удаление всего списка
template <typename ValueType>
void DoublyLinkedList<ValueType>::DelList()
{
	Element *tmp = Head;
	while (tmp) //Пока по адресу на начало списка что-то есть
	{
		tmp = Head->next; //Резервная копия адреса следующего звена списка
		delete Head; //Очистка памяти от первого звена
		Head = tmp; //Смена адреса начала на адрес следующего элемента
	}
	countElem = 0;
}

/// \file Spisok_main.cpp
/// \brief тело основной программы
/// \brief создан репозиторий в GitHub
/// \author Бурдинская Наталья ВМК-22
/// \date 29.03.2024

#include "Spisok_one.h"
#include "Spisok_class.h"

int main()
{
	// «Rus» локализация произойдёт на русский язык
	setlocale(LC_ALL, "russian");
	// Тесты ASSERT
	Test_AddFront();
	Test_AddBack();
    Test_AddInList();
	Test_DelFront();
	Test_DelInList();
	Test_DelBack();
	Test_Find();
	Test_Sort();
	Test_Assert();

	DoublyList <int> list_1;
	list_1.AddFront(111);
	list_1.AddBack(222);
	list_1.AddInList(333, list_1.get_OneList(0));
	cout << endl;
	cout << list_1.to_string() << endl;
	cout << "-- Сортировка --" << endl;
	list_1.sort();
	cout << list_1.to_string() << endl;
	cout << "Найти 111 из списка - " << list_1.find(111)->data << endl;
    cout << "Длина списка = " << list_1.length() << endl;
}
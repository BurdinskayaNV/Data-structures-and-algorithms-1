/// \file Spisok_class.cpp
/// \brief Работа с двусвязным списком
/// \author Бурдинская Наталья ВМК-22
/// \date 29.03.2024

#include "Spisok_one.h"
#include "Spisok_class.h"

void Test_AddFront()
{
    DoublyList<int> list;
    assert(list.length() == 0);
    // Тестирование добавления элемента в пустой список
    list.AddFront(1);
    assert(list.length() == 1);
    assert(list.get_OneList(0)->data == 1);
    // Добавляем элементы в список
    list.AddFront(2);
    list.AddFront(3);
    // Тестирование добавления элементов в начало списка
    assert(list.length() == 3);
    assert(list.get_OneList(1)->data == 2);
    cout << "-- Тестирование AddFront выполнено успешно --------" << endl;
}

void Test_AddBack()
{
    DoublyList<int> list;
    assert(list.length() == 0);
    // Тестирование добавления элемента в пустой список
    list.AddBack(1);
    assert(list.length() == 1);
    assert(list.get_OneList(0)->data == 1);
    // Добавляем еще элементы в список
    list.AddBack(2);
    list.AddBack(3);
    // Тестирование добавления элементов в конец списка
    assert(list.length() == 3);
    assert(list.get_OneList(1)->data == 2);
    assert(list.get_OneList(2)->data == 3);
    cout << "-- Тестирование Test_AddBack выполнено успешно ----" << endl;
}

void Test_AddInList()
{
    DoublyList<int> list;
    assert(list.length() == 0);
    // Тестирование добавления элемента в пустой список
    list.AddBack(1);
    assert(list.length() == 1);
    assert(list.get_OneList(0)->data == 1);
    // Добавляем еще элементы в список
    list.AddBack(3);
    list.AddInList(2, list.get_OneList(0));
    // Тестирование добавления элементов в середине списка
    assert(list.length() == 3);
    assert(list.get_OneList(1)->data == 2);
    assert(list.get_OneList(2)->data == 3);
    cout << "-- Тестирование Test_AddInList выполнено успешно --" << endl;
}

void Test_DelFront() {
    DoublyList<int> list;
    assert(list.length() == 0);
    // Добавляем элементы в список
    list.AddBack(1);
    list.AddBack(2);
    list.AddBack(3);
    assert(list.length() == 3);
    list.DelFront();
    // Тестирование удаление элементов из начала списка
    assert(list.length() == 2);
    //assert(list.find(1)->data == 1);
    assert(list.find(2)->data == 2);
    assert(list.find(3)->data == 3);
    cout << "-- Тестирование Test_DelFront выполнено успешно ---" << endl;
}

void Test_DelBack() {
    DoublyList<int> list;
    assert(list.length() == 0);
    // Добавляем элементы в список
    list.AddBack(1);
    list.AddBack(2);
    list.AddBack(3);
    assert(list.length() == 3);
    list.DelBack();
    // Тестирование удаление элементов с конца списка
    assert(list.length() == 2);
    assert(list.find(1)->data == 1);
    assert(list.find(2)->data == 2);
    //assert(list.find(3)->data == 3);
    cout << "-- Тестирование Test_DelBack выполнено успешно ----" << endl;
}

void Test_DelInList() {
    DoublyList<int> list;
    assert(list.length() == 0);
    // Добавляем элементы в список
    list.AddBack(1);
    list.AddBack(2);
    list.AddBack(3);
    assert(list.length() == 3);
    list.DelInList(2);
    // Тестирование удаление элементов с середины списка
    assert(list.length() == 2);
    assert(list.find(1)->data == 1);
    assert(list.find(3)->data == 3);
    //assert(list.find(3)->data == 3);
    cout << "-- Тестирование Test_DelInList выполнено успешно --" << endl;
}

void Test_Find() {
    DoublyList<int> list;
    assert(list.length() == 0);
    // Добавляем элементы в список
    list.AddBack(1);
    list.AddBack(2);
    list.AddBack(3);
    // Тестирование поиска существующего элемента
    assert(list.find(2) != nullptr);
    // Тестирование поиска несуществующего элемента
    assert(list.find(5) == nullptr);
    cout << "-- Тестирование Test_Find выполнено успешно -------" << endl;
}

void Test_Sort() {
    DoublyList<int> list;
    // Тестирование сортировки пустого списка
    list.sort();
    assert(list.length() == 0);
    // Добавляем элементы в список
    list.AddBack(3);
    list.AddBack(1);
    list.AddBack(2);
    // Тестирование сортировки списка
    list.sort();
    assert(list.find(1)->data == 1);
    assert(list.find(2)->data == 2);
    assert(list.find(3)->data == 3);
    cout << "-- Тестирование Test_Sort выполнено успешно -------" << endl;
}

// Тестирование класса
void Test_Assert()
{
    // Конструктор по умолчанию список пуст
    DoublyList<int> list1;
    assert(list1.length() == 0);

    // Конструктор, заполняющий список n элементами с значением value
    DoublyList<int> list2(5, 10);
    assert(list2.length() != 0);
    assert(list2.length() == 5);
    assert(list2.get_OneList(2)->data == 10);

    
    // Вставка нового узла, содержащего data, после указанного узла node
    list1.AddFront(2);
    list1.AddInList(8, list1.find(2));
    assert(list1.length() == 2);

    // Склеивание двух списков
    list1.ConcatenateLists(list2);
    assert(list1.length() == 7);
    cout << "-- Тестирование Test_Assert выполнено успешно -----" << endl;
 }


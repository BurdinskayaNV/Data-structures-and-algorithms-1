/// \file Deque.h
/// \brief Тело основной программы
/// \author Бурдинская Наталья ВМК-22
/// \date 10.05.2024
/// Класс описывающий тип дек.Реализованы функции добавление в начало и в конец, 
/// удаление из начала и из конца, проверка на то пустой ли дек (isEmpty), 
/// возвращение размера(size), возвращение значения элемента из начала и конца дека,
/// очистка дека (clear)
/// Реализован на основе класса двусвязный список DoublyList

#pragma once
#include "Queue.h"
#include "Spisok_one.h"    // односвязный список с прошлого задания
#include "Spisok_class.h"  // двусвязный список с прошлого задания
#include <iostream>
#include <cassert>
#include <string>
using namespace std;

// Класс Deque двусторонняя очередь, наследуется от обычной очереди
template <class Type>
class Deque : private Queue<Type>
{
public:
    // Добавление элемента в начало очереди
    // element Добавляемый элемент
    void pushFront(Type element)
    {
        this->AddQueue(element);
    }

    /// @brief Добавление элемента в конец очереди E
    /// @param element Добавляемый элемент
    /// BigO: O(1)
    void pushBack(Type element)
    {
        this->AddBack(element);
    }

    /// @brief Удаление элемента из конца очереди F
    /// @return Значение удаленного элемента, или значение по умолчанию для Type, если очередь пуста
    /// BigO: O(1)
    Type popBack()
    {
        if (this->isEmpty())
        {
            return Type(); // вернется значение по умолчанию для Type
        }
        return this->DelQueue(); 
    }

    /// @brief Удаление элемента из начала очереди E
    /// @return Значение удаленного элемента, или значение по умолчанию для Type, если очередь пуста
    /// BigO: O(1)
    Type popFront()
    {
        // Если пусто
        if (this->isEmpty())
        {
            return Type(); // вернется значение по умолчанию для Type
        }

        Type val = this->get_OneList(0)->data;
        this->DelFront();
        return val;
    }

    /// @brief Проверяет пуста ли очередь
    /// @return Значение true||false
    /// BigO: O(1)
    bool isEmpty()
    {
        return this->Queue<Type>::isEmpty();
    }

    /// @brief Вернет размер очереди
    /// @return size_t - размер
    size_t size() {
        return this->Queue<Type>::size();
    }

    /// @brief Очистка очереди
    /// BigO: O(n)
    void clear()
    {
        while (!this->isEmpty())
        {
            this->DelQueue();
        }
    }

    /// @brief Вернет значение конца очереди
    /// @return Type
    Type getBackData() {
        return this->getTailData();
    }

    /// @brief Вернет значение начала очереди
    /// @return Type
    Type getFrontData() {
        return this->getHeadData();
    }

    string to_string() const {
        return this->to_string();
    }
};

// Тестирование метода pushFront
void testPushFront() {
    Deque<int> queue1;
    //добавляем
    queue1.pushFront(1); assert(queue1.getBackData() == 1);
    queue1.pushFront(2); assert(queue1.getBackData() == 2);
    queue1.pushFront(3); assert(queue1.getBackData() == 3);
    assert(queue1.getFrontData() == 1);
    cout << "-- Тестирование pushFront выполнено успешно -------" << endl;
}

// Тестирование метода pushBack
void testPushBack() {
    Deque<int> queue2;
    //добавляем
    queue2.pushBack(1); assert(queue2.getFrontData() == 1);
    queue2.pushBack(2); assert(queue2.getFrontData() == 2);
    queue2.pushBack(3); assert(queue2.getFrontData() == 3);
    assert(queue2.getBackData() == 1);
    cout << "-- Тестирование pushBack выполнено успешно --------" << endl;
}

// Тестирование метода popBack
void testPopBack() {
    Deque<int> queue3;
    //добавляем
    queue3.pushFront(1); assert(queue3.getBackData() == 1);
    queue3.pushFront(2); assert(queue3.getBackData() == 2);
    queue3.pushFront(3); assert(queue3.getBackData() == 3);
    assert(queue3.getFrontData() == 1);
    //удаляем
    queue3.popBack(); assert(queue3.size() == 2);
    assert(queue3.getBackData() == 3);

    queue3.popBack(); assert(queue3.size() == 1);
    assert(queue3.getBackData() == 3);

    assert(queue3.popBack() == 3); assert(queue3.size() == 0);

    //проверка на ассерт пустой очереди double
    Deque<double> queueEmpty1;
    assert(queueEmpty1.popBack() == 0.0);

    //проверка на ассерт пустой очереди строк
    Deque<string> queueEmpty2;
    assert(queueEmpty2.popBack() == "");

    cout << "-- Тестирование popBack выполнено успешно ---------" << endl;
}

// Тестирование метода popFront
void testPopFront() {
    Deque<int> queue4;
    //добавляем
    queue4.pushBack(1);
    queue4.pushBack(2);
    queue4.pushBack(3);
    //удаляем
    queue4.popFront(); assert(queue4.size() == 2);
    assert(queue4.getFrontData() == 3);

    queue4.popFront(); assert(queue4.size() == 1);
    assert(queue4.getFrontData() == 3);

    assert(queue4.popFront() == 3);	assert(queue4.size() == 0);

    //проверка на ассерт пустой очереди double
    Deque<double> queueEmpty1;
    assert(queueEmpty1.popFront() == 0.0);

    //проверка на ассерт пустой очереди строк
    Deque<string> queueEmpty2;
    assert(queueEmpty2.popFront() == "");
    cout << "-- Тестирование popFront выполнено успешно --------" << endl;
}

// Тестирование isEmpty
void testIsEmpty() {
    Deque<int> queue5;
    assert(queue5.isEmpty());

    queue5.pushFront(123);	assert(!queue5.isEmpty());

    queue5.popBack(); assert(queue5.isEmpty());
    cout << "-- Тестирование isEmpty выполнено успешно ---------" << endl;
}
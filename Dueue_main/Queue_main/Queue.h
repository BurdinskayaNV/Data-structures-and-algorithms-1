#pragma once
#include "Spisok_one.h"    // односвязный список с прошлого задания
#include "Spisok_class.h"  // двусвязный список с прошлого задания
#include <iostream> //объявляет cin cout
#include <sstream>  //потоковой работы со строчным типом данных
#include <cassert>  //для assert
#include <locale>   //определяет функцию setlocale для установки русской локали


// Класс Queue есть представитель структуры данных - очередь (FIFO)
// param Type тип элементов очереди
// наследование от двусвязного списка DoublyList
template <typename Type>
class Queue : public DoublyList<Type>
{
public:

    // Конструктор по умолчанию
    Queue() {}

    // Деструктор
    ~Queue() {}

    // Добавление элемента в очередь
    // param element Добавляемый элемент
    void AddQueue(Type element)
    {
        this->AddFront(element);
    }

    // Удаление элемента из очереди, удалится первый вошедший, вернется значение по умолчанию для Type
    Type DelQueue()
    {
        // Если стек пуст
        if (this->isEmpty())
        { return Type(); } //вернется значение по умолчанию для Type
         
        Type val = this->get_OneList(this->length() - 1)->data;
        this->DelBack();
        return val;
    }

    // Проверяет пуста ли очередь
    // return Значение true||false
    bool isEmpty() const {
        bool empty = false;
        if (this->length() == 0)
            empty = true;
        return empty;
    }

    // Вернет размер очереди
    // return size_t - размер
    size_t size() const {
        return this->length();
    }

    // Вернет значение конца очереди
    // return Type
    Type getTailData() {
        return this->get_OneList(0)->data;
    }

    // Вернет значение начала очереди
    // return Type
    Type getHeadData() {
        return this->get_OneList(this->size() - 1)->data;
    }

    // Возращает элемент очереди, готовый к выходу из нее
    // return Элемент, если список пуст, то 0
    Type peek() {
        if (this->isEmpty())
        {
            return 0;
        }
        return this->get_OneList(this->length() - 1)->data;
    }

    // Выводит очередь в стандартный вывод.
    void print() const {
        cout << this->to_string() << endl;
    }

    // Возвращает первый элемент очереди.
    Type front() const {
        if (!this->isEmpty()) {
            return this->first();
        }
        return Type();
    }

    // Возвращает последний элемент очереди.
    Type back() const {
        if (!this->isEmpty()) {
            return this->last();
        }
        return Type();
    }
};

// Функция тестирования метода AddQueue
void Test_AddQueue() {
    Queue<int> queue;

    queue.AddQueue(1);
    assert(queue.getTailData() == 1);

    queue.AddQueue(2);
    assert(queue.getTailData() == 2);
    
    queue.AddQueue(3);
    assert(queue.getHeadData() == 1);
    assert(queue.getTailData() == 3);
    cout << "-- Тестирование AddQueue выполнено успешно -------" << endl;
}

// Функция тестирования метода DelQueue
void Test_DelQueue() {
    Queue<int> queue;

    //добавляем
    queue.AddQueue(1);
    queue.AddQueue(2);
    queue.AddQueue(3);

    //проверяем
    queue.DelQueue();
    assert(queue.size() == 2);
    assert(queue.getHeadData() == 2);
    assert(queue.getTailData() == 3);

    queue.DelQueue();
    assert(queue.size() == 1);
    assert(queue.getHeadData() == 3);
    assert(queue.getTailData() == 3);

    assert(queue.DelQueue() == 3);
    assert(queue.size() == 0);

    //проверка на ассерт пустой очереди double
    Queue<double> queueEmpty;
    assert(queueEmpty.DelQueue() == 0.0);

    //проверка на ассерт пустой очереди строк
    Queue<string> queueEmpty2;
    assert(queueEmpty2.DelQueue() == "");

    //проверяем на ассерт удаление из пустого очереди
    //Queue<string> queueEmpty2;
    //assert(queueEmpty2.DelQueue() == "");

    cout << "-- Тестирование DelQueue выполнено успешно -------" << endl;
}

// Тестирование функции Peek
void Test_Peek() {
    Queue<int> queue;

    queue.AddQueue(1);
    queue.AddQueue(2);
    queue.AddQueue(3);

    assert(queue.peek() == 1);

    queue.DelQueue();
    assert(queue.peek() == 2);

    queue.AddQueue(123);
    assert(queue.peek() == 2);
    cout << "-- Тестирование Peek выполнено успешно -----------" << endl;
}

// Тестирование функции isEmpty
void Test_IsEmpty() {
    Queue<int> queue;
    assert(queue.isEmpty());

    queue.AddQueue(123);
    assert(!queue.isEmpty());

    queue.DelQueue();
    assert(queue.isEmpty());
    cout << "-- Тестирование isEmpty выполнено успешно --------" << endl;
}

// Функция тестирования класса Stack
void Test_Queue() 
{
    Test_AddQueue();
    Test_DelQueue();
    Test_Peek();
    Test_IsEmpty();
}

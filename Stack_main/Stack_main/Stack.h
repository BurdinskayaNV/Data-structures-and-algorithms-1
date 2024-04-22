#pragma once
#include "Spisok_one.h"    // односвязный список с прошлого задания
#include "Spisok_class.h"  // двусвязный список с прошлого задания
#include <cassert>

// Класс Stack есть представитель структуры данных - стека
// Type тип элементов стека
template <typename Type>
// наследование от двусвязного списка DoublyList
class Stack : public DoublyList<Type>
{
public:
    // Добавление элемента в вершину стека
    // element Добавляемый элемент
    void push(Type element)
    {
        this->AddFront(element);
    }

    // Удаление элемента из вершины стека
    Type pop()
    {
        // Если стек пуст
        if (this->isEmpty())
        { return 0; }
        
        Type val = this->get_OneList(0)->data;
        this->DelFront();
        return val;
    }

    // Проверяет пустой ли стек
    // return Значение true||false или 1||0
    bool isEmpty() {
        bool b = false;
        if (this->length() == 0)
            b = true;
        return b;
    }

    // Возращает последний элемент стека
    // return Элемент, если список пуст, то 0
    Type peek() {
        if (this->isEmpty())
        { return 0; }
        return this->get_OneList(0)->data;
    }
};

// Тестирование метода Push
void Test_Push() {
    Stack<int> stack;
    // Добавление элемента в вершину стека
    stack.push(1);
    assert(stack.get_OneList(0)->data == 1);
    stack.push(2);
    assert(stack.get_OneList(0)->data == 2);
    
    stack.push(3);
    assert(stack.get_OneList(1)->data == 2);
    assert(stack.get_OneList(0)->data == 3);

    cout << "-- Тестирование Push выполнено успешно -------" << endl;
}

// Тестирование метода Pop
void Test_Pop() {
    Stack<int> stack;
    // Добавление элемента в вершину стека
    stack.push(1);
    stack.push(2);
    stack.push(3);
    assert(stack.get_OneList(0)->data == 3);

    // Удаление элемента из вершины стека
    stack.pop();
    assert(stack.length() == 2);
    assert(stack.get_OneList(0)->data == 2);

    stack.pop();
    assert(stack.length() == 1);
    assert(stack.get_OneList(0)->data == 1);

    stack.pop();
    assert(stack.length() == 0);
    cout << "-- Тестирование Pop выполнено успешно --------" << endl;
}

// Тестирование метода Peek
void Test_Peek() {
    Stack<int> stack;
    // Добавление элемента в вершину стека
    stack.push(1);
    stack.push(2);
    stack.push(3);
    assert(stack.peek() == 3); // Возращает последний элемент стека
    
    // Удаление элемента из вершины стека
    stack.pop();
    assert(stack.peek() == 2); // Возращает последний элемент стека
    
    // Добавление элемента в вершину стека
    stack.push(123);
    assert(stack.peek() == 123); // Возращает последний элемент стека
    cout << "-- Тестирование Peek выполнено успешно -------" << endl;
}

// Тестирование метода isEmpty
void Test_IsEmpty() {
    Stack<int> stack;
    assert(stack.isEmpty()); // пусто

    stack.push(123); // Добавление элемента в вершину стека
    assert(!stack.isEmpty()); // не пусто
    cout << "-- Тестирование isEmpty выполнено успешно ----" << endl;
}

// Тестирование класса Stack
void Test_Stack()
{
    Test_Push();
    Test_Pop();
    Test_Peek();
    Test_IsEmpty();
}
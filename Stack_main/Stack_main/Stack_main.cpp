/// \file Stack_main.cpp
/// \brief тело основной программы
/// \author Бурдинская Наталья ВМК-22
/// \date 15.04.2024

#include <iostream>
#include "stack.h"

using namespace std;

int main() 
{
    // «Rus» локализация произойдёт на русский язык
    setlocale(LC_ALL, "russian");
    cout << endl;
    // Тесты ASSERT
    Test_Stack();
    cout << endl;

    Stack<int> stack1;
    Stack<int> stack2;

    // добавили элементы в первый стек
    stack1.push(10);
    stack1.push(20);
    stack1.push(30);
    cout << "stack1 : " << stack1.to_string() << endl;
    // добавили элементы во второй стек
    stack2.push(10);
    stack2.push(20);
    stack2.push(30);
    cout << "stack2 : " << stack2.to_string() << endl;
    cout << endl;

    // удалили элемент из вершины первого стека
    cout << stack1.pop() << " удален из stack1" << endl;
    cout << "stack1 : " << stack1.to_string() << endl;
    cout << endl;

    // добавили элементы в первый стек
    stack1.push(40);
    cout << "stack1 : " << stack1.to_string() << " элемент добавлен в stack1" << endl;
    cout << endl;

    // объединяем стек один и стек два
    stack1.ConcatenateLists(stack2);
    cout << "Объединенный стек : " << stack1.to_string() << endl;
    cout << "Длина списка = " << stack1.length() << endl;
    cout << "Последний элемент стека - " << stack1.peek() << endl; // Возращает последний элемент стека
    cout << endl;

    // пустой стек
    Stack<int> stack3;
    cout << "stack3 пустой : " << stack3.to_string() << endl;
    cout << "Один элемент - " << stack3.isEmpty() << endl;
    cout << "Последний элемент стека - " << stack3.peek(); // Возращает последний элемент стека
    cout << endl;

    return 0;
}
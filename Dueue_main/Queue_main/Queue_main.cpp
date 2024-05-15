#include <iostream>
#include "Queue.h"
#include "Deque.h"

using namespace std;

int main()
{
    // «Rus» локализация произойдёт на русский язык
    setlocale(LC_ALL, "russian");
    cout << endl;
    // Тесты ASSERT
    //Test_Queue();
    testPushFront();
    testPushBack();
    testPopBack();
    testPopFront();
    testIsEmpty();
    cout << endl;

    /* Queue<int> queue1;
    // добавили элементы в первую очередь
    queue1.AddQueue(18);
    queue1.AddQueue(28);
    queue1.AddQueue(38);
 
    cout << "queue1 : " << endl;
    // Выводим очередь.
    queue1.print();
    cout << queue1.peek() << " Peek() Возращает элемент очереди, готовый к выходу из нее" << endl;
    cout << queue1.DelQueue() << " был удален из queue1" << endl;
    queue1.print();
    cout << queue1.size() << " длина очереди queue1" << endl;
    queue1.AddQueue(48);
    cout << queue1.getTailData() << " добавлен новый элемент в queue1 " << endl;
    queue1.print();
    cout << queue1.size() << " длина очереди queue1 стала после добавления " << endl;
    cout << queue1.peek() << " Peek() Возращает элемент очереди, готовый к выходу из нее" << endl;
    cout << endl; 

    Queue<int> queue2;
    // Добавлена пустая очередь 
    cout << "Создана пустая очередь queue2" << endl;
    cout << queue2.isEmpty() << " isEmpty() очередь queue2 пуста, т.к. = 1 (true)" << endl;
    queue2.print();
    cout << queue2.size() << " длина очереди queue2" << endl;
    cout << queue2.front() << " первый элемент пустой очереди queue2" << endl;
    cout << queue2.back() << " последний элемент пустой очереди queue2" << endl;
    cout << endl;

    cout << queue2.peek() << " Peek() Возращает элемент очереди, готовый к выходу из нее" << endl;
    cout << queue2.DelQueue() << " был удален из queue2" << endl;
    queue2.print();
    cout << queue2.size() << " длина очереди queue2" << endl;
    cout << queue2.front() << " первый элемент пустой очереди queue2" << endl;
    cout << queue2.back() << " последний элемент пустой очереди queue2" << endl; */
    
    return 0;
} /// дек - это двухсторонная очередь
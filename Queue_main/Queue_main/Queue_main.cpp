#include <iostream>
#include "Queue.h"

using namespace std;

int main()
{
    // «Rus» локализация произойдёт на русский язык
    setlocale(LC_ALL, "russian");
    cout << endl;
    // Тесты ASSERT
    Test_Queue();
    cout << endl;

    Queue<int> queue1;
    // добавили элементы в первую очередь
    queue1.AddQueue(18);
    queue1.AddQueue(28);
    queue1.AddQueue(38);
 
    cout << "queue1 : " << endl;
    cout << queue1.peek() << " Peek() Возращает элемент очереди, готовый к выходу из нее" << endl;
    cout << queue1.DelQueue() << " был удален из queue1" << endl;
    cout << queue1.size() << " длина очереди queue1" << endl;
    queue1.AddQueue(48);
    cout << queue1.getTailData() << " добавлен новый элемент в queue1 " << endl;
    cout << queue1.size() << " длина очереди queue1 стала после добавления " << endl;

    return 0;
}
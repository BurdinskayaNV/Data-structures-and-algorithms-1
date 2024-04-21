/// \file Dinamo_main.cpp
/// \brief тело основной программы
/// \brief создан репозиторий в GitHub
/// \author Бурдинская Наталья ВМК-22
/// \date 29.03.2024

#include "Modul_array.h"

int main()
{
    //srand(time(0)); // Время необходимо для рандомных чисел
    system("chcp 65001 > nul"); //подключение русского языка 
    setlocale(LC_ALL, "RUSSIAN");
    // Тестирование ASSERT
    //testAdd();
    //testResized();
    //testDelete();
    testSearch();
    testSort();

    DinamoArray<int> a(3); // массив из трех целых чисел
    a[0] = 22;
    a[1] = 33;
    a[2] = 11;

    a.Add_Front(123); // добавить впереди
    a.Add_Back(321);  // добавить с обратной стороны
    //a.Delete_Last();  // удалить последнюю
    //a.Delete_Firts(); // удалить первую

    // вывести массив на экран
    for (size_t i = 0; i < a.lenght(); i++)
    {
        cout << a[i] << "\n";
    }
}
/// \file Recursion.cpp
/// \brief Вариант 6
/// \brief Написать функцию умножения двух чисел, используя только операцию сложения.
/// \brief Измерение размера стека с помощью бесконечной рекурсии
/// \author Бурдинская Наталья ВМК-22
/// \date 04.03.2024

#include <iostream> //объявляет cin cout
#include <cassert>  //для assert
#include <locale>   // определяет функцию setlocale для установки русской локали
#include <string>   //для использования строк
using namespace std;
int result;
int m; int n;

/// Вычисляет умножения двух чисел, используя только операцию сложения
/// \param m первое целое число
/// \param n второе целое число
/// \return результат умножения через рекурсию
static int rmultiply(int m, int n) // rmultiply - перевод многократно
{
    if (n > 1)
        return(m + (rmultiply(m, n - 1)));
    // если m=6 n=3
    // 6 + rmultiply(3 - 1)
    // 6 + 6 + rmultiply(2 - 1)
    // 6 + 6 + 6 , т.к. n =1
    // return 6 + 6 + 6 
    else if ((m == 0) || (n == 0))
        return 0;
    // умножение на 0 равно 0
    else if (n == 1)
        return m;
    // умножение на 1 равно m
    else if (m == 1)
        return n;
    // умножение на 1 равно n
}

/// Измерение размера стека с помощью бесконечной рекурсии
/// функция сложения числа на единицу
static int StackSizeMeasurement(int& i) // StackSizeMeasurement - перевод Измерение размера стека
{
    cout << i << "   ";
    i += 1;
    StackSizeMeasurement(i);
    return 0;
}

///*** Тест измерения размера стека
static void Test_StackSizeMeasurement() {
    assert(rmultiply(2, 4) == 8);    // 2 * 4 = 8
    assert(rmultiply(8, 50) == 400); // 8 * 50 = 400
    assert(rmultiply(1, 25) == 25);  // 1 * 25 = 25
    cout << "Тест выполнен успешно " << endl;
    cout << endl;
}

int main(int argc, char* argv[])
{
    // «Rus» локализация произойдёт на русский язык
    setlocale(LC_ALL, "russian");
    // Аргументы командной строки cmd arg для функции main
    // argv[0] - имя файла Recursion.exe
    // значит начинаем argv[1] и argv[2] 
    // в нашем случае argc = 3
    // (argv[0] имя самого проекта, argv[1] первый множитель m и argv[2] второй множитель n)
    string str_m, str_n;
    int k = argc;
    if (k == 1)
    {
        cout << "Введите два целых числа для умножения" << endl;
        // сохраняем их в m и n
        cout << "m = "; cin >> m;
        cout << "n = "; cin >> n;
    }
    else if ((k == 2)||(k > 3))
    {
        str_m = argv[1];
        if (str_m == "help")	// Если введут help
        {
            cout << "Чтобы программа работала корректно, введите первый аргумент число: <первый множитель m>" << endl;
            cout << "Далее через пробел введите второй аргумент число: <второй множитель n> " << endl;
            return 0;
        }
        else
        {
            cout << "Чтобы программа работала корректно, нужно ввести два аргумента числа m и n" << endl;
            cout << "Если нужна помощь введите 'help' в качестве аргумента" << endl;
            return 0;
        }
        cout << "\n";
    }
    else if (k == 3)
    {
        try {
            m = stoi(argv[1]); // преобразовать строку в int 
            n = stoi(argv[2]); // преобразовать строку в int 
        }
        catch (const std::invalid_argument& error) {
            std::cout << error.what(); // выводим сообщение об ошибке
        }
    }
    try {
       result = rmultiply(m, n);
    }
    catch (const std::invalid_argument& error) {
       std::cout << error.what();
    }
    cout << "результат умножения через рекурсию " << result << endl;
    cout << endl;
    Test_StackSizeMeasurement();
    int c = 0;
    //StackSizeMeasurement(c);
    return 0;
} 
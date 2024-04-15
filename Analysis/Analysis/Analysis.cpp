/// \file Analysis.cpp
/// \brief Вариант 8
/// \brief Задан массив размера n и число x.
/// \brief Напишите программу, определяющую какой элемент наиболее близок к числу x.
/// \brief Какой случай для алгоритма является наилучшим? Наихудшим? 
/// \brief Результаты тестирования вывести в текстовый файл.
/// \brief Количество сравнений в лучшем случае равно n - 1
/// \brief 
/// \author Бурдинская Наталья ВМК-22
/// \date 04.03.2024

#include "Analysis_modul.h" // вызов заголовочного файла Analysis_modul

int main(int argc, char* argv[])
{
    system("chcp 65001 > nul"); //подключение русского языка 
    // «RUSSIAN» локализация произойдёт на русский язык
    setlocale(LC_ALL, "RUSSIAN");
    // Генерирует случайное число, используя текущею дату, для непредсказуемости результата
    srand(time(0));

    // Аргументы командной строки cmd arg для функции main
    // argv[0] - имя файла Analysis.exe
    // значит начинаем argv[1], argv[2] и argv[3]
    // в нашем случае argc = 4
    // (argv[0] имя самого проекта, argv[1] размерность массива n,
    // argv[2] число x, argv[3] имя файла для ввода и сохранения данных)
    int k = argc;
    if (k == 1)
    {
        cout << "Введите размерность массива" << endl;
        cout << "n = "; cin >> n;
        cout << "\n";
        cout << "Введите число x " << endl;
        cout << "x = "; cin >> x;
        cout << "\n";
        cout << "Введите имя файла " << endl;
        cout << "file_name = "; cin >> file_name;
        cout << "\n";
    }
    else if ((k == 2) || (k == 3) || (k > 4))
    {
        str_n = argv[1];
        if (str_n == "help")	// Если введут help
        {
            cout << "Чтобы программа работала корректно, введите первый аргумент число: <размерность массива n>" << endl;
            cout << "Далее через пробел введите второй аргумент число: <число x> " << endl;
            cout << "Далее <имя файла для ввода и сохранения данных> " << endl;
            return 0;
        }
        else
        {
            cout << "Чтобы программа работала корректно, нужно ввести три аргумента числа n и x, а так же имя файла" << endl;
            cout << "Если нужна помощь введите 'help' в качестве аргумента" << endl;
            return 0;
        }
        cout << "\n";
    }
    else if (k == 4)
    {
        try {
            n = stoi(argv[1]); // преобразовать строку в int 
            x = stoi(argv[2]); // преобразовать строку в int 
        }
        catch (const std::invalid_argument& error) {
            std::cout << error.what(); // выводим сообщение об ошибке
        }
        file_name = argv[3];
    }
    
    Test_Work_array();
    //int* arr = new int[n] {1, 2, 3, 4};
    //int* arr = new int[n] {1, 2, 4, 3};
    //int* arr = new int[n] {1, 3, 2, 4}; 
    //int* arr = new int[n] {1, 3, 4, 2};
    //int* arr = new int[n] {1, 4, 2, 3};
    //int* arr = new int[n] {1, 4, 3, 2};
    //int* arr = new int[n] {2, 1, 3, 4};
    //int* arr = new int[n] {2, 1, 4, 3};
    //int* arr = new int[n] {2, 3, 1, 4};
    //int* arr = new int[n] {2, 3, 4, 1};
    //int* arr = new int[n] {2, 4, 1, 3};
    int near = find_nearby(Iarr, n, x, 10); //  15042024.txt
    // int near = find_nearby(Darr, n, x, 10);
    // int near = find_nearby(arr, n, x, 10);
    cout << "Ближайший элемент к X в массиве " << near << endl;
    //Test_Find_nearby();
    return 0;
}


/// \file Analysis_modul.h
/// \brief Работа с массивами
/// \author Бурдинская Наталья ВМК-22
/// \date 04.03.2024

#pragma once
#include <string>    // для использования строк
#include <iomanip>   // для setw setprecision
#include <cassert>   // для assert
#include <iostream>  // объявляет cin cout
#include <ctime>     // время для рандомных элементов массива
#include <fstream>   // для работы с файлами
#include <exception> // обработка исключений
#include <locale>    // определ¤ет функцию setlocale для русской локали 
using namespace std; // пространоство имен std::

int result;
int x = 0, n = 200;
string str_n, str_x, file_name;
int* Iarr = new int[n] {0}; // описываем динамический массив Int
double* Darr = new double[n] {0}; // описываем динамический массив double
string fileTxt = "TxtArray.txt";

//---процедура ввода массива размерности n случайными числами
// динамические массивы в функции передаются как векторы
// ничего не возвращает, просто вводит данные в массив
template <typename TArray>
void Set_array(TArray* a, size_t size, int high, int low)
//void Set_array(TArray* a, size_t size, TArray high, TArray low)
{
	// массив a, size, high, low - формальные параметры
	// заполнение массива случайными числами от low до high включительно
	TArray delta = high - low; // диапазон рандома
	for (size_t i = 0; i < size; ++i) // нумерация с нул¤ до size-1
	{
		a[i] = (((TArray)rand() / RAND_MAX) * delta) + low;
		a[i] = rand() % (2 * high) + low;
		// rand() возвращает случайное целое число
	}
}

//---процедура вывода на экран массива N
// ничего не возвращает, просто выводит на консоль
template<typename TArray>
void Screen_array(const TArray* a, size_t size)
{
	// массив a, size - формальные параметры
	for (size_t i = 0; i < size; i++)
	{
		cout << a[i] << "  ";
		// cout << "a[" << i << "] = " << a[i] << " ";
	}
	cout << endl;
}

//---тест работы с массивами
void Test_Work_array()
{
	// для проверки шаблона TArray
	cout << "----- Проверка шаблонной функции при вводе массива рандомными элементами -----" << endl;
	cout << "------- Массив Int ----------------------------------" << endl;
	Set_array(Iarr, n, 100, 0); // выполняем ввод массива Int
	Screen_array(Iarr, n); // выводим на экран массив Int
	cout << endl;
	// вызвать в программе один раз, перед выводом чисел.
	cout << fixed << setprecision(2); // два знака после запятой
	cout << "------- Массив Double -------------------------------" << endl;
	Set_array(Darr, n, 100, 0); // выполняем ввод массива Double
	Screen_array(Darr, n); // выводим на экран массив Double
	cout << endl;
}

template <typename TArray>
/// выводит массив в файл
/// \param a массив типа TArray
/// \param n размер массива
/// \param FileName файл, куда выводится массив
/// \return ничего, но в файл выводиться массив
void output_to_file(const TArray* a, unsigned n, const string& file_name) {
	// режим открытия файла дл¤ записи ios::out
	// устанавливаетс¤ при создании файла
	ofstream Fin(file_name, ios::out); //затирает старые и пишет новые данные
	if (!Fin.is_open())	  // Если не открыт файл
	{
		throw runtime_error("Файл не найден");
	}
	// пишем в файл отправленный массив
	for (size_t i = 0; i < size; ++i)
	{
		Fin << a[i] << " " << endl;
	}
	Fin.close(); // функция close() закрывает поток файла
	cout << "Пишем в текстовый файл. Конец записи в файл." << endl;
	cout << "-----------------------------------------------------" << endl;
}

/// Функция поиска ближайшего элемента к x в массиве
/// (n-1)*4+3 =  => Big-O(n), т.к. константы обрезаем
/// \param n размер массива
/// \param x число, которое нужно найти
/// \param arr числовой массив
/// \return результат nearby - ближнего числа
template <typename TArray>
TArray find_nearby(const TArray* arr, size_t size, TArray x, TArray comparisions) // comparisions - сравнения
{
    comparisions = 1; // количество сравнений присваиваем первоначально 1
    if (size == 1)	return arr[0]; // если массив с 1 элементом, то возращаем значение элемента arr[0]
    TArray nearby = arr[0];	// предполагаем, что первый элемент наиболее близок  - рядом
    TArray difference = abs(x - arr[0]); // находим разницу между x и первым элементом по модулю
    for (size_t i = 1; i < size; i++)  // BigO(n-1)
    {
        TArray currentDiff = abs(x - arr[i]); // находим элемент в момент итерации
        if (currentDiff < difference)		  // вот сравнение
        {
            comparisions++; // счетчик сравнений
            nearby = arr[i];	// перемещаемся по массиву
            difference = currentDiff; // заменяем конкретный элемент на элемент в момент итерации
        }
    }
	//ofstream Fin("TxtArray.txt", ios::app); //затирает старые и пишет новые данные
	ofstream Fin(file_name, ios::app); //затирает старые и пишет новые данные
	if (!Fin.is_open())	  // Если не открыт файл
	{
		throw runtime_error("Файл не найден");
	}
	// пишем в файл отправленный массив
	Fin << "Массив " << endl;
	for (size_t i = 0; i < size; ++i)
	{
		Fin << arr[i] << " ";
	}
	Fin << endl;
	Fin << "выполнено " << comparisions << " сравнений" << endl;
	Fin << "Это число " << nearby << endl;
	Fin << endl;
	Fin.close(); // функция close() закрывает поток файла
	return nearby;
}

//---тест функции find_nearby  ///**** сделать побольше размер
static void Test_Find_nearby()
{
    int sizemin = 5;
    int comparision1 = 0;
    //double comparision2 = 0.00;
    int* a = new int[sizemin] {1, 2, 3, 4, 5};
    //double* b = new double[sizemin] {1.11, 2.22, 3.33, 4.44, 5.55};
    int* c = new int[sizemin] {5, 3, 2, 67, 34};

    int test1 = find_nearby(a, sizemin, 8, comparision1);
    assert(test1 == 5);

    //double test2 = find_nearby(b, sizemin, 1.132, comparision2);
    //assert(test2 == 1.11);

    int test3 = find_nearby(c, sizemin, 1, comparision1);
    assert(test3 == 2);

    delete[] a;
    //delete[] b;
    delete[] c;
    cout << "--- Test_Find_nearby() выполнен успешно -------------" << endl;
}
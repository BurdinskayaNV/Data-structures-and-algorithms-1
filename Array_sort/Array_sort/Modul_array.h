/// \file Modul_array.h
/// \brief Работа с массивами
/// \author Бурдинская Наталья ВМК-22
/// \date 18.02.2024

#pragma once
#include <string>    // для использования строк
#include <iomanip>   // для setw setprecision
#include <cassert>   // для assert
#include <iostream>  // объявляет cin cout
#include <ctime>     // время для рандомных элементов массива
#include <exception> // обработка исключений
#include <locale>    // определ¤ет функцию setlocale для русской локали 
#include <chrono>    // Измерение времени работы кода
#include <stack>	 // для стека, функции push и pop
#include <cstdio> 
using namespace std::chrono;
using namespace std; // пространоство имен std::

size_t Asize = 10; // *** Для хранения размера массива, индексов стоит использовать тип size_t.
// *** Он может хранить только положительные значения из большого диапазона.
int* Iarr = new int[Asize] {0}; // описываем динамический массив Int
double* Darr = new double[Asize] {0}; // описываем динамический массив double

//---процедура ввода массива размерности size случайными числами
// динамические массивы в функции передаются как векторы
// ничего не возвращает, просто вводит данные в массив
/// *** Vvod_array переименован в Set_array - Задать массив
/// *** TArray high, TArray low поставлены как тип TArray
template <typename TArray>
void Set_array(TArray* a, size_t size, int high, int low)
//void Set_array(TArray* a, size_t size, TArray high, TArray low)
{
	// массив a, size, high, low - формальные параметры
	// заполнение массива случайными числами от low до high включительно
	TArray delta = high - low; // диапазон рандома
	for (size_t i = 0; i < size; ++i) // нумерация с нул¤ до size-1
	{
		//a[i] = (((TArray)rand() / RAND_MAX) * delta) + low;
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
/// *** выделен в отдельный тест
void Test_Work_array()
{
	// для проверки шаблона TArray
	cout << "Проверка шаблонной функции при вводе массива рандомными элементами" << endl;
	cout << "------- Массив Int ----------------------------------" << endl;
	Set_array(Iarr, Asize, 100, -100); // выполняем ввод массива Int
	Screen_array(Iarr, Asize); // выводим на экран массив Int
	cout << endl;
	// вызвать в программе один раз, перед выводом чисел.
	cout << fixed << setprecision(2); // два знака после запятой
	cout << "------- Массив Double -------------------------------" << endl;
	Set_array(Darr, Asize, 100.00, -100.00); // выполняем ввод массива Double
	Screen_array(Darr, Asize); // выводим на экран массив Double
	cout << endl;
}
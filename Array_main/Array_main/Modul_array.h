/// \file Modul_array.h
/// \brief Работа с массивами
/// \author Бурдинская Наталья ВМК-22
/// \date 18.02.2024

#pragma once
#include <string>    // для использования строк
#include <iomanip>   // для setw setprecision
#include <cassert>   // для assert
#include <iostream>  // объявляет cin cout
#include <ctime>    // время для рандомных элементов массива
#include <fstream>   // для работы с файлами
#include <exception> // обработка исключений
#include <locale>    // определ¤ет функцию setlocale для русской локали 
#include <chrono>    // Измерение времени работы кода
using namespace std::chrono;
using namespace std; // пространоство имен std::

size_t Asize = 10; // *** Для хранения размера массива, индексов стоит использовать тип size_t.
// *** Он может хранить только положительные значения из большого диапазона.
int* Iarr = new int[Asize] {0}; // описываем динамический массив Int
double* Darr = new double[Asize] {0}; // описываем динамический массив double
string fileTxt = "TxtArray.txt";
string fileBin = "BinArray.txt";

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
	cout << "-- Проверка шаблонной функции при вводе массива рандомными элементами --" << endl;
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

//--- функция, которая проверяет, отсортирован ли массив
// два вида сортировки: по возрастанию (по умолчанию)
// и убыванию (задается третьим параметром rule: 'l' по убыванию)
template <typename TArray>
bool sortArr(const TArray* a, size_t size, const char rule = '2')
{
	if (size == 0 || size == 1) return true; // 1 или 0 возращаем true
	if (rule == 'l') // сортировка по убыванию
		for (size_t i = 0; i < size - 1; i++)
		{
			// если первый меньше второго возвращаем false
			// потому что убывающая
			if (a[i] < a[i + 1]) return false;
		}
	else // сортировка по возврастанию
		for (size_t i = 0; i < size - 1; i++)
		{
			// если первый больше второго возвращаем false
			// потому что возрастающая
			if (a[i] > a[i + 1]) return false;
		}
	return true;
}

//---тест работы функции sortArr
void Test_sortArr()
{
	unsigned* sorInt = new unsigned[3] {1, 2, 3};   // сортированный Int
	unsigned* nosorInt = new unsigned[3] {4, 2, 3}; // несортированный Int, сортировка ломается в начале
	assert(sortArr(sorInt, 3) == true);
	assert(sortArr(nosorInt, 3) == false);
	delete[] sorInt;		// сортированный Int
	delete[] nosorInt;		// несортированный Int

	double* sortDob = new double[3] {1.11, 2.22, 3.33};   // сортированный double
	double* nosortDob = new double[3] {1.11, 2.22, 1.33}; // несортированный double, сортировка ломается в конце
	assert(sortArr(sortDob, 3) == true);
	assert(sortArr(nosortDob, 3) == false);
	delete[] sortDob;		// сортированный Double
	delete[] nosortDob;		// несортированный Double

	string* sortStr = new string[3]{ "aaa", "bbb", "ccc" };   // сортированный string
	string* nosortStr = new string[5]{ "aaa", "bbb", "eee", "ccc", "ddd" }; // несортированный string, сотиовка ломается в середине
	assert(sortArr(sortStr, 3) == true);
	assert(sortArr(nosortStr, 5) == false);
	delete[] sortStr;		// сортированный String
	delete[] nosortStr;		// несортированный String

	unsigned* decsortInt = new unsigned[3] {3, 2, 1};		// сортированный Int убывает
	assert(sortArr(decsortInt, 3, 'l') == true);
	double* decsortDob = new double[3] {3.33, 2.22, 1.11};	// сортированный Dob убывает
	assert(sortArr(decsortDob, 2.22, 'l') == true);
	/// *** порядок ломается в середине или в конце или начале assert
	delete[] decsortInt;
	delete[] decsortDob;

	cout << "--- Test_sortArr() выполнен успешно -----------------" << endl;
}

//---последовательный поиск по массиву,
// если key будет найден, то вернется его индекс,
// если нет, то вернется число -1
/// *** про size_t, index переименован в key
/// *** Для хранения размера массива, индексов стоит использовать тип size_t.
/// *** Он может хранить только положительные значения из большого диапазона.
template <typename TArray>
long long Search_sequential(const TArray* a, size_t size, TArray key) /// *** Poisk переименован в Search 
{
	for (size_t i = 0; i < size; ++i)
		if (a[i] == key) return i; // значение найдено, возвращаем индекс
	return -1; // значение не найдено, возращаем -1
}

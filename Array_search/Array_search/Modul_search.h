/// \file Modul_search.h
/// \brief Работа с поиском в массиве
/// \author Бурдинская Наталья ВМК-22
/// \date 18.02.2024
#pragma once
/// *** Poisk переименован в Search

#include "Modul_array.h" // вызов заголовочного файла Modul_array

//---последовательный поиск по массиву,
// BigO(n)-худший случай, Big0(n) - средний случай, BigO(1)-лучший случай
// 
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

//---тест работы функции Search_sequential
/// *** добавлен поиск элемента из середины 
void Test_Search_sequential()
{
	size_t sizemin = 3;
	// для проверки шаблона TArray
	int* a = new int[sizemin] {1, 2, 3};
	double* b = new double[sizemin] {1.11, 2.22, 3.33};
	string* c = new string[sizemin]{ "Sunday", "Monday", "Tuesday" };

	long long test1 = Search_sequential(a, sizemin, 3);
	assert(test1 == 2); // поиск элемента в конце массива
	long long test2 = Search_sequential(b, sizemin, 1.11);
	assert(test2 == 0); // поиск элемента в начале массива
	string str = "Wednesday";
	long long temp3 = Search_sequential(c, sizemin, str);
	assert(temp3 == -1); // если элемент отсутствует
	/// *** 
	long long temp4 = Search_sequential(a, sizemin, 2);
	assert(temp4 == 1);	/// *** добавлен поиск элемента из середины  

	delete[] a;
	delete[] b;
	delete[] c;
	cout << "--- Test_Search_sequential() выполнен успешно -------" << endl;
}

//---бинарный поиск в массиве 
// Сколько раз вы можете разделить на 2, прежде чем останется только один элемент? 
// n / (2 * 2 * 2 * ... * 2) = 1 ['2' повторяется x раз], или n = 2 ^ x
// Итак, логарифмическая база 2 из n дает вам x, то есть количество принимаемых решений.
// BigO(logn)-худший случай, Big0(logn) - средний случай, BigO(1)-лучший случай
// 
// если key будет найден, то вернется его индекс,
// если нет, то вернется число -1, если массив не отсортирован, то вернется число -2
// бинарный поиск работает только с упорядочными данными 
/// *** index переименован в key
/// *** long long: представляет целое число занимает в памяти 8 байт (64 бита)
/// *** Имеет псевдонимы long long int
template <typename TArray>
long long Search_binary(TArray* arr, size_t size, TArray key)
{
	// если массив не отсортирован, возращаем -2
	if (sortArr(arr, size) == false) { return -2; }

	size_t low = 0;     // нижняя граница, начальное значение = 0
	size_t high = size; // верхняя граница, начальное значение = размерности массива
	size_t middle;	     // cередина [low,high]

	while (low <= high)
	{
		middle = (low + high) / 2; // срединный индекс [low,high]
		if (arr[middle] == key) // если середина равна искомому элементу
			return middle;
		if (arr[middle] > key) // в какой части находится искомый элемент
			high = middle - 1;	// к верхней границе
		else
			low = middle + 1;    // к нижней границе
	}
	return -1; // значение не найдено, возращаем -1
}

//---тест работы функции Poisk_binary
/// *** добавлены 3 поиска
void Test_Search_binary()
{
	size_t sizemin = 5;
	// для проверки шаблона TArray
	int* a = new int[sizemin] {1, 2, 3, 4, 5}; // отсортирован
	double* b = new double[sizemin] {1.11, 2.22, 3.33, 4.44, 5.55}; // отсортирован
	int* c = new int[sizemin] {5, 3, 2, 1, 4}; // не отсортирован

	long long test1 = Search_binary(a, sizemin, 5);
	assert(test1 == 4); // поиск элемента в конце массива
	long long test2 = Search_binary(b, sizemin, 1.11);
	assert(test2 == 0); // поиск элемента в начале массива
	long long test3 = Search_binary(c, sizemin, 2);
	assert(test3 == -2); // массив не отсортирован
	/// *** добавлены тесты
	long long test4 = Search_binary(b, sizemin, 6.66);
	assert(test4 == -1); // *** если элемент отсутствует
	long long test5 = Search_binary(a, sizemin, 3);
	assert(test5 == 2); // *** поиск элемента из середины
	long long test6 = Search_binary(b, sizemin, 4.44);
	assert(test6 == 3); // *** поиск элемента не из середины, не с начала, не с конца

	delete[] a;
	delete[] b;
	delete[] c;
	cout << "--- Test_Search_binary() выполнен успешно -----------" << endl;
}

//---интерполяционный поиска в массиве
// BigO(n)-худший случай, Big0(loglogn) - средний случай, BigO(1)-лучший случай
// 
// если index будет найден, то вернется его индекс,
// если нет, то вернется число -1, если массив не отсортирован, то вернется число -2
// бинарный поиск работает только с упорядочными данными 
/// *** index переименован в key
/// *** long long: представляет целое число занимает в памяти 8 байт (64 бита)
/// *** Имеет псевдонимы long long int
template <typename TArray>
long long Search_interpolation(TArray* arr, size_t size, TArray key)
{
	// если массив не отсортирован, возращаем -2
	if (sortArr(arr, size) == false) { return -2; }

	size_t low = 0;         // нижняя граница, начальное значение = 0
	size_t high = size - 1; // верхняя граница, начальное значение = размерности массива

	while (low <= high && key >= arr[low] && key <= arr[high]) // Пока не найдем индекц нашего key
	{
		if (low == high) // если в массиве 1 элемент
		{
			if (arr[low] == key) return low; // если этот элемент есть key, возращаем его индекс
			return -1;	// если нет то -1, что значит key не найден
		}
		// Формула интерполяции для определения предполагаемого положения искомого элемента
		size_t pos = low + ((key - arr[low]) * (high - low) / (arr[high] - arr[low]));
		if (arr[pos] == key) return pos; // если позиция pos элемента и есть key, то возращаем pos
		if (arr[pos] < key) low = pos + 1; // если позиция pos элемента меньше, тогда увеличиваем нижнюю границу на pos
		else high = pos - 1; // иначе увеличиваем верхнюю границу на pos 
	}
	return -1; // значение не найдено, возращаем -1
}

//---тест работы функции Poisk_interpolation
/// *** добавлены 3 поиска
void Test_Search_interpolation()
{
	size_t sizemin = 5;
	// для проверки шаблона TArray
	int* a = new int[sizemin] {1, 2, 3, 4, 5}; // отсортирован
	double* b = new double[sizemin] {1.11, 2.22, 3.33, 4.44, 5.55}; // отсортирован
	int* c = new int[sizemin] {5, 3, 2, 1, 4}; // не отсортирован

	long long test1 = Search_interpolation(a, sizemin, 5);
	assert(test1 == 4); // поиск элемента в конце массива
	long long test2 = Search_interpolation(b, sizemin, 1.11);
	assert(test2 == 0); // поиск элемента в начале массива
	long long test3 = Search_interpolation(c, sizemin, 2);
	assert(test3 == -2); // массив не отсортирован
	/// *** добавлены тесты
	long long test4 = Search_interpolation(b, sizemin, 6.66);
	assert(test4 == -1); // *** если элемент отсутствует
	long long test5 = Search_interpolation(a, sizemin, 3);
	assert(test5 == 2); // *** поиск элемента из середины
	long long test6 = Search_interpolation(b, sizemin, 4.44);
	assert(test6 == 3); // *** поиск элемента не из середины, не с начала, не с конца

	delete[] a;
	delete[] b;
	delete[] c;
	cout << "--- Test_Search_interpolation() выполнен успешно ----" << endl;
}
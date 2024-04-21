/// \file Array.h
/// \brief Работа с массивами
/// \author Бурдинская Наталья ВМК-22
/// \date 29.03.2024

#include <string>
#include <iomanip>
#include <cassert>
#include <cstddef>
#include <type_traits>

using namespace std; // Пространоство имен

/// Последовательный поиск по массиву, если key будет найден, то вернется его индекс, если же нет, то вернется число -1
template <typename Array>
long long sequential_search(const Array arr[], long long size, Array key)
{
	for (long long i = 0; i < size; ++i)
		if (arr[i] == key)
			return i; // значение найдено, возвращаем индекс
	return -1;		  // значение не найдено, возращаем -1
}

/// Функция слияния двух отсортированных подмассивов из merge_sort
template <typename Array>
void merge_mas(Array* arr, size_t left, size_t mid, size_t right)
{
	// вычисление размеров двух подмассивов  - левого и правого, а на какой стороне ты?
	size_t leftSize = mid - left + 1;
	size_t rightSize = right - mid;

	// тут храним эти массивы
	Array* LeftArr = new Array[leftSize];
	Array* RightArr = new Array[rightSize];

	// копируем элементы левого подмассива во временный левый
	// memcpy(куда, откуда, размер в байтах)
	memcpy(LeftArr, &arr[left], sizeof(Array) * leftSize);

	// копируем элементы правого подмассива во временный правый
	memcpy(RightArr, &arr[mid + 1], sizeof(Array) * rightSize);

	// обьявляем индексы подмассивов для их обьединения, ибо в цикле while это удобнее
	size_t i = 0;
	size_t j = 0;
	size_t k = left;

	// слияние двух подмассивов в основной массив arr
	while (i < leftSize && j < rightSize)
	{
		if (LeftArr[i] <= RightArr[j])
		{
			arr[k] = LeftArr[i];
			i++;
		}
		else
		{
			arr[k] = RightArr[j];
			j++;
		}
		k++;
	}

	// добавление оставшихся элементов из левого подмассива
	if (i < leftSize)
	{
		memcpy(&arr[k], &LeftArr[i], (leftSize - i) * sizeof(Array)); // добавление оставшихся элементов из левого подмассива
		k += leftSize - i;
	}

	// добавление оставшихся элементов из правого подмассива
	if (j < rightSize)
	{
		memcpy(&arr[k], &RightArr[j], (rightSize - j) * sizeof(Array)); // добавление оставшихся элементов из правого подмассива
		k += rightSize - j;
	}

	delete[] LeftArr, RightArr;
}

/// Функция сортировки массива методом merge (слияний) по порядку - от меньшего к большему
/// arr - сам массив, left - указывает на левую границу массива (для первого вызова является 0),
/// right - указывает на правую границу массива (для первого вызова является n - последним индексом массива)
/// Big O::
/// Лучший случай: когда массив уже отсортирован или почти отсортирован, сортировка слиянием все равно выполняется за O(n log n) операций
/// Худший случай: Для сортировки слиянием худший случай также составляет O(n log n)
/// Средний случай: Средняя сложность сортировки слиянием также составляет O(n log n)
template <typename Array>
void merge_sort(Array& arr, size_t left, size_t right)
{
	// если массив вовсе не является размера 1, то делаем
	if (left < right)
	{
		// вычисляем серединку
		size_t mid = left + (right - left) / 2;

		// и тут мы вызываем рекурсию, чтобы дальше делить уже разделенные левые и правые части массива от 0 до середины и от середины до конца
		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);

		// тут вызываем функцию, которая производит слияние двух отсортированных массивов
		merge_mas(arr, left, mid, right);
	}
}
/// \file Modul_sort.h
/// \brief Работа с сортировкой в массиве
/// \author Бурдинская Наталья ВМК-22
/// \date 18.02.2024
#pragma once
#include "Modul_array.h" // вызов заголовочного файла Modul_array

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

//---сортировка массива пузырьком по порядку - от меньшего к большему
/// Т.к.цикл вложенный, то его BigO(n^2)
/// Худшее  – O(n2), Среднее – O(n2), Лучшее  – O(n), слайд 147
/// \param a массив, тип TArray
/// \param size размер массива
/// \return ничего, просто сортирует массив a
template <typename TArray>
void Sorting_bubbles(TArray* a, size_t size)
{
	TArray temporary;	  // temporary - Временное хранение
	for (size_t i = 0; i < size - 1; i++) // Один цикл O(n)
	{
		for (size_t j = 0; j < size - i - 1; j++) // Второй цикл O(n*n)
		{
			if (a[j] > a[j + 1]) // Если пред > след
			{
				temporary = a[j]; // меняем элементы местами
				a[j] = a[j + 1];
				a[j + 1] = temporary;
			}
		}
	}
}

//---тест работы функции Sorting_bubbles
void Test_Sorting_bubbles()
{
	size_t sizemin = 6;

	int* a = new int[sizemin] {6, 2, 3, 4, 5, 1}; // несортированный Int
	double* b = new double[sizemin] {1.11, 2.22, 3.33, 4.44, 5.55, 6.66}; // сортированный double
	int* c = new int[sizemin] {5, 3, 1, 5, 3, 1}; // несортированный Int
	int* d = new int[sizemin] {6, 5, 4, 3, 2, 1}; // сортированный Int в обратном порядке

	int* a_result = new int[sizemin] {1, 2, 3, 4, 5, 6}; // результат сортировки массива a
	double* b_result = new double[sizemin] {1.11, 2.22, 3.33, 4.44, 5.55, 6.66}; // результат сортировки массива b
	int* c_result = new int[sizemin] {1, 1, 3, 3, 5, 5}; // результат сортировки массива c
	int* d_result = new int[sizemin] {6, 5, 4, 3, 2, 1}; // результат сортировки массива d

	// тестирование сортировки пузырьками
	Sorting_bubbles(a, sizemin);
	assert(a[0] == 1);
	assert(a[1] == 2);
	assert(a[2] == 3);
	assert(a[3] == 4);
	assert(a[4] == 5);
	assert(a[5] == 6);

	Sorting_bubbles(b, sizemin);
	Sorting_bubbles(c, sizemin);
	Sorting_bubbles(d, sizemin);
	for (size_t i = 0; i > sizemin; i++)
	{
		assert(a[i] == a_result[i]);
		assert(b[i] == b_result[i]);
		assert(c[i] == c_result[i]);
		assert(d[i] == d_result[i]);
	}

	delete[] a, b, c, d;
	delete[] a_result, b_result, c_result, d_result;
	cout << "--- Test_Sorting_bubbles() выполнен успешно ---------" << endl;
}

//---сортировка массива слиянием двух отсортированных подмассивов для Sorting_merge
/// \param a массив, тип TArray
/// \param разбиваем массив от середины middle на две части
/// \param left размер полумассива слева от middle
/// \param right размер полумассива справа от middle
/// \return ничего, просто сортирует массив a
template <typename TArray>
void Merge(TArray* arr, size_t left, size_t mid, size_t right) // Merge - слияние ///*** int заменить на size_t
{
	// вычисление размеров двух подмассивов 
	size_t LSize = mid - left + 1;
	size_t RSize = right - mid;
	// временные подмассивы для слияния
	TArray* LeftArr = new TArray[LSize];
	TArray* RightArr = new TArray[RSize];
	// копируем элементы левого подмассива во временный левый
	// memcpy(куда, откуда, размер в байтах) // размер типа данных TArray
	memcpy(LeftArr, &arr[left], sizeof(TArray) * LSize);
	// копируем элементы правого подмассива во временный правый
	memcpy(RightArr, &arr[mid + 1], sizeof(TArray) * RSize);
	// обьявляем индексы подмассивов для их обьединения, ибо в цикле while это удобнее
	size_t i = 0; size_t j = 0; size_t k = left;
	// слияние двух подмассивов в основной массив arr
	while (i < LSize && j < RSize)
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
	if (i < LSize)
	{
		memcpy(&arr[k], &LeftArr[i], (LSize - i) * sizeof(TArray)); // добавление оставшихся элементов из левого подмассива
		k += LSize - i;
	}
	// добавление оставшихся элементов из правого подмассива
	if (j < RSize)
	{
		memcpy(&arr[k], &RightArr[j], (RSize - j) * sizeof(TArray)); // добавление оставшихся элементов из правого подмассива
		k += RSize - j;
	}
	delete[] LeftArr, RightArr;
};

//---сортировка слиянием по возрастанию (рекурсивная)
// BigO(n*logn)-худший случай, Big0(n*logn) - средний случай,
// BigO(n*logn)-лучший случай  слайд 118
/// \param a массив, тип TArray
/// \param first индекс элемента, с которого начинается сортировка
/// \param last индекс элемента, на котором заканчивается сортировка
/// \return просто сортирует массивы 
/// Лучший случай: когда массив уже отсортирован, сортировка слиянием все равно выполняется за O(n log n) операций
/// Худший случай: Для сортировки слиянием худший случай также составляет O(n log n)
/// Средний случай: Средняя сложность сортировки слиянием также составляет O(n log n)
template <typename TArray>
void Sorting_merge(TArray* a, size_t left, size_t right)
{
	if (left < right)
	{
		// вычисляем mid
		size_t mid = left + (right - left) / 2;
		Sorting_merge(a, left, mid); //сортировка левой части
		Sorting_merge(a, mid + 1, right); //сортировка правой части
		Merge(a, left, mid, right); //слияние двух частей
	}
};

//---тест работы функции Sorting_merge
void Test_Sorting_merge()
{
	size_t sizemin = 6;

	int* a = new int[sizemin] {6, 2, 3, 4, 5, 1}; // несортированный Int
	double* b = new double[sizemin] {1.11, 2.22, 3.33, 4.44, 5.55, 6.66}; // сортированный double
	int* c = new int[sizemin] {5, 3, 1, 5, 3, 1}; // несортированный Int
	int* d = new int[sizemin] {6, 5, 4, 3, 2, 1}; // сортированный Int в обратном порядке

	int* a_result = new int[sizemin] {1, 2, 3, 4, 5, 6}; // результат сортировки массива a
	double* b_result = new double[sizemin] {1.11, 2.22, 3.33, 4.44, 5.55, 6.66}; // результат сортировки массива b
	int* c_result = new int[sizemin] {1, 1, 3, 3, 5, 5}; // результат сортировки массива c
	int* d_result = new int[sizemin] {6, 5, 4, 3, 2, 1}; // результат сортировки массива d

	// тестирование сортировки пузырьками
	Sorting_merge(a, 0, 5);
	assert(a[0] == 1);
	assert(a[1] == 2);
	assert(a[2] == 3);
	assert(a[3] == 4);
	assert(a[4] == 5);
	assert(a[5] == 6);

	Sorting_merge(b, 0, 5);
	Sorting_merge(c, 0, 5);
	Sorting_merge(d, 0, 5);
	for (size_t i = 0; i > sizemin; i++)
	{
		assert(a[i] == a_result[i]);
		assert(b[i] == b_result[i]);
		assert(c[i] == c_result[i]);
		assert(d[i] == d_result[i]);
	}

	delete[] a, b, c, d;
	delete[] a_result, b_result, c_result, d_result;
	cout << "--- Test_Sorting_merge() выполнен успешно ---------" << endl;
}

//---функция для определения опорного элемента в массиве 
/// \param a массив, тип TArray
/// \param left - указывает на левую границу массива (для первого вызова является 0)
/// \param right - указывает на правую границу массива (n - последним индексом массива)
/// \return просто сортирует массивы 
/// element выбирается рандомно
template <typename TArray>
size_t Search_element(TArray* a, size_t left, size_t right)
{
	size_t Elem_rand = rand() % right;  //**** рандомный индекс
	TArray element = a[Elem_rand];
	// Выбираем последний элемент в качестве опорного ///*** случайный эл

	size_t i = (left - 1); 			// Инициализация индекса меньших элементов

	for (size_t j = left; j <= right - 1; j++) {
		if (a[j] < element) {
			i++; 				// Увеличиваем индекс меньших элементов
			swap(a[i], a[j]);   // Меняем элементы местами
		}
	}
	swap(a[i + 1], a[right]); 	// Меняем опорный элемент с элементом в позиции i + 1
	return (i + 1); 			// Возвращаем индекс опорного элемента
}

//---рекурсивная функция для сортировки массива
/// Big O:: Худший случай: O(n2)
/// Средний случай: O(n log n), Лучший случай: O(n)
/// \param a массив, тип TArray
/// \param left - указывает на левую границу массива (для первого вызова является 0)
/// \param right - указывает на правую границу массива (n - последним индексом массива)
/// \return просто сортирует массивы 
template <typename TArray>
void Sorting_quick(TArray* a, size_t left, size_t right) {
	if (left < right) {
		size_t element = Search_element(a, left, right);// Находим опорный элемент
		if (element > 0) {
			Sorting_quick(a, left, element - 1); 		// рекурсивно сортируем элементы перед опорным
		}
		Sorting_quick(a, element + 1, right); 			// рекурсивно сортируем элементы после опорного
	}
}

//---тест работы функции Sorting_quick ///****поменять размеры массива, надо чтобы везде было разное количество элементов
void Test_Sorting_quick()
{
	size_t sizemin = 6;

	int* a = new int[sizemin] {6, 2, 3, 4, 5, 1};
	double* b = new double[sizemin] {1.04, 1.05, 1.03, 1.01, 1.02, 1.06};
	int* c = new int[9] {5, 3, 2, 5, 3, 2, 5, 9, 8};
	int* d = new int[7] {6, 5, 4, 3, 4, 5, 1};

	int* a_result = new int[sizemin] {1, 2, 3, 4, 5, 6};
	double* b_result = new double[sizemin] {1.01, 1.02, 1.03, 1.04, 1.05, 1.06};
	int* c_result = new int[sizemin] {2, 2, 3, 3, 5, 5};
	int* d_result = new int[sizemin] {6, 5, 4, 3, 2, 1};

	Sorting_quick(a, 0, 5);
	Sorting_quick(b, 0, 5);
	Sorting_quick(c, 0, 9);
	Sorting_quick(d, 0, 7);
	for (size_t i = 0; i > sizemin; i++)
	{
		assert(a[i] == a_result[i]);
		assert(b[i] == b_result[i]);
		assert(c[i] == c_result[i]);
		assert(d[i] == d_result[i]);
	}

	delete[] a, b, c;
	delete[] a_result, b_result, c_result, d_result;
	cout << "--- Test_Sorting_quick() выполнен успешно ---------" << endl;
}
///*** Big_O везде и в сортировке и в поиске

//---тест работы функции Sorting_Shell
/// Шаг выбирается size/2 и потом уменьшается каждый раз в два раза
/// Big O::  Худший случай: O(n^2)
/// Лучший случай: O(n log n), Средний случай: O(n^(3/2))
template <typename Array>
void Sorting_Shell(Array arr[], size_t size)
{
	// начало с большого step шага, что уменьшается с каждым шагом на два
	for (size_t step = size / 2; step > 0; step /= 2)
	{
		// смотрим элементы по массиву, начиная с элемента на расстоянии stepik от начала
		for (size_t i = step; i < size; i++)
		{
			Array temp = arr[i];
			size_t j;
			// сортируем подмассивы с шагом stepik, сравнивая и меняя их
			for (j = i; j >= step && arr[j - step] > temp; j -= step)
			{
				arr[j] = arr[j - step];
			}
			arr[j] = temp;
		}
	}
}

/// Функция тестирования для функции Sorting_Shell
void Test_Sorting_Shell()
{
	long long sizeSmall = 6;

	// a - средний, b - лучший, c - с повторениями, d - обратный

	int* a = new int[sizeSmall] {6, 2, 3, 4, 5, 1};
	double* b = new double[8] {1.01, 1.02, 1.03, 1.04, 1.05, 1.06, 1.07, 1.08};
	int* c = new int[7] {5, 3, 2, 5, 3, 2, 8};
	int* d = new int[sizeSmall] {6, 5, 4, 3, 2, 1};

	int* a_ = new int[9] {1, 2, 3, 4, 5, 6, 7, 8, 9};
	double* b_ = new double[sizeSmall] {1.01, 1.02, 1.03, 1.04, 1.05, 1.06};
	int* c_ = new int[sizeSmall] {2, 2, 3, 3, 5, 5};
	int* d_ = new int[sizeSmall] {6, 5, 4, 3, 2, 1};

	// сортировка, ее проверка
	Sorting_Shell(a, sizeSmall);
	Sorting_Shell(b, sizeSmall);
	Sorting_Shell(c, sizeSmall);
	Sorting_Shell(d, sizeSmall);
	for (int i = 0; i > sizeSmall; i++)
	{
		assert(a[i] == a_[i]);
		assert(b[i] == b_[i]);
		assert(c[i] == c_[i]);
		assert(d[i] == d_[i]);
	}

	delete[] a, b, c;
	delete[] a_, b_, c_;
	cout << "--- Test_Sorting_Shell() выполнен успешно ---------" << endl;
}
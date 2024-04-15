/// \file Array_sort.cpp
/// \brief тело основной программы
/// \brief подготовительный код для работы с массивами,
/// \brief использован одномерный динамический массив
/// \brief для хранения размера массива, индексов использован тип size_t
/// \brief выделение памяти для массива, освобождение памяти массива
/// \brief передача массива в функции, возврат из функции через return, указатели * и ссылки &
/// \brief использованы шаблонные функции template с типом <typename TArray>
/// \brief применение srand(time(NULL)) и rand() для случайных чисел
/// \brief проверка, отсортирован ли массив, автоматический тест для шаблонной функции (assert)
/// \brief измерение времени работы кода
/// \brief Сортировка массива пузырьком, автоматический тест для шаблонной функции (assert) 
/// \brief Сортировка массива merge слиянием, автоматический тест для шаблонной функции (assert) 
/// \brief Сортировка массива quick быстро, автоматический тест для шаблонной функции (assert)
/// \brief Сортировка массива Shell, автоматический тест для шаблонной функции (assert)
/// \brief автоматическое тестирование программы с помощью assert
/// \brief создан репозиторий в GitHub
/// \author Бурдинская Наталья ВМК-22
/// \date 18.02.2024

#include "Modul_array.h" // вызов заголовочного файла Modul_array
#include "Modul_sort.h" // вызов заголовочного файла Modul_sort

int main()
{
	system("chcp 65001 > nul"); //подключение русского языка 
	setlocale(LC_ALL, "RUSSIAN");
	// Генерирует случайное число, используя текущею дату, для непредсказуемости результата
	srand(time(0));
	/// *** выделены в отдельные тесты
	Test_Work_array(); // работа с массивами в Modul_array.h
	cout << "-----------------------------------------------------" << endl;
	cout << endl;

	delete[] Iarr;
	delete[] Darr;

	// Тесты ASSERT
	cout << "--- Тест ASSERT отсортирован ли массив ? ------------" << endl;
	Test_sortArr();
	cout << endl;
	cout << "--- Тест ASSERT Сортировка массива пузырьком --------" << endl;
	Test_Sorting_bubbles();
	cout << endl;
	cout << "--- Тест ASSERT Сортировка массива merge слиянием ---" << endl;
	Test_Sorting_merge();
	cout << endl;
	cout << "--- Тест ASSERT Сортировка массива quick быстро -----" << endl;
	Test_Sorting_quick();
	cout << endl;
	cout << "--- Тест ASSERT Сортировка массива Sorting_Shell ----" << endl;
	Test_Sorting_Shell();
	cout << endl;
	cout << "-----------------------------------------------------" << endl;

    // Работа для построения графика времени работы сортировочных функций
	size_t big_n = 100000;
	cout << fixed << setprecision(10); // три знака после запятой
	float milliSeconds1 = 0.0;
	float milliSeconds2 = 0.0;
	for (int j = 0; big_n < 100000000; j++)
	{
		//cout << j + 1 << " итерация" << endl;
		int* a = new int[big_n];
		cout << "Размерность = " << big_n << endl;
		Set_array(a, big_n, 1000000, 1);

		// измеряем сортировку merge
		auto begin1 = steady_clock::now();
		for (int i = 0; i < 1; i++)
		{
			Sorting_merge(a, 0, big_n);
		}
		auto end1 = steady_clock::now();
		milliSeconds1 = duration_cast<milliseconds>(end1 - begin1).count();
		//milliSeconds1 = duration_cast<seconds>(end1 - begin1).count();

		// измеряем сортировку Sorting_bubbles
		auto begin2 = steady_clock::now();
		for (int i = 0; i < 1; i++)
		{
			Sorting_bubbles(a, big_n);
		}
		auto end2 = steady_clock::now();
		milliSeconds2 = duration_cast<milliseconds>(end2 - begin2).count();
		//milliSeconds2 = duration_cast<seconds>(end2 - begin2).count();

		//if (big_n >= 1000000000) big_n += big_n * 2;
		//else big_n *= 10;

		// сколько заняло миллисекунд 5 итераций
		cout << "Время (в миллисекундах) для Sequential Search: " << milliSeconds1 / 10000 << endl;
		cout << "Время (в миллисекундах) для Binary Search: " << milliSeconds2 / 1000000 << endl;
		//cout << "Время (в секундах) для Sequential Search: " << milliSeconds1 / 5 << endl;
		//cout << "Время (в секундах) для Binary Search: " << milliSeconds2 / 5 << endl;
		cout << endl;

		//delete[] a;
	}
	return 0;
}
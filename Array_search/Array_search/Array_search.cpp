/// \file Array_search.cpp
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
/// \brief последовательный поиск значения в массиве, автоматический тест для шаблонной функции (assert) 
/// \brief бинарный поиск значения в массиве, автоматический тест для шаблонной функции (assert) 
/// \brief интерполяционный поиск значения в массиве, автоматический тест для шаблонной функции (assert)
/// \brief автоматическое тестирование программы с помощью assert
/// \brief создан репозиторий в GitHub
/// \author Бурдинская Наталья ВМК-22
/// \date 18.02.2024

#include "Modul_array.h" // вызов заголовочного файла Modul_array
#include "Modul_search.h" // вызов заголовочного файла Modul_search

int main()
{
	system("chcp 65001 > nul"); //подключение русского языка 
	setlocale(LC_ALL, "RUSSIAN");
	// Генерирует случайное число, используя текущею дату, для непредсказуемости результата
	srand(time(0));
	/// *** выделены в отдельные тесты
	cout << "-----------------------------------------------------" << endl;
	Test_Work_array(); // работа с массивами в Modul_array.h
	cout << "-----------------------------------------------------" << endl;
	cout << endl;
	// Тесты ASSERT
	cout << "--- Тест ASSERT отсортирован ли массив ? ------------" << endl;
	Test_sortArr();
	cout << endl;
	cout << "--- Тест ASSERT Последовательный поиск по массиву ---" << endl;
	Test_Search_sequential();
	cout << endl;
	cout << "--- Тест ASSERT Бинарный поиск по массиву -----------" << endl;
	Test_Search_binary();
	cout << endl;
	cout << "--- Тест ASSERT Интерполяционный поиск по массиву ---" << endl;
	Test_Search_interpolation();
	cout << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << endl;

	// Работа для построения графика времени работы посиковых функций
	size_t big_n = 100000000;
	cout << fixed << setprecision(10); // три знака после запятой
	float milliSeconds1 = 0.0;
	float milliSeconds2 = 0.0;
	float milliSeconds3 = 0.0;
	int el = 0; // число для поиска
	for (int j = 0; big_n < 100000000000; j++)
	{
		//cout << j + 1 << " итерация" << endl;
		int* a = new int[big_n];
		cout << "Размерность = " << big_n << endl;
		Set_array(a, big_n, 1000000, 1);
		
		// измеряем Последовательный поиск
		auto begin1 = steady_clock::now();
		for (int i = 0; i < 10000; i++)
		{
			el = (int)rand() / RAND_MAX * 10000 + 1; // случайное число для поиска 
			Search_sequential(a, big_n, el);
		}
		auto end1 = steady_clock::now();
		milliSeconds1 = duration_cast<milliseconds>(end1 - begin1).count();
		//milliSeconds1 = duration_cast<seconds>(end1 - begin1).count();
		
		// измеряем Бинарный поиск
		auto begin2 = steady_clock::now();
		for (int i = 0; i < 1000000; i++)
		{
			el = (int)rand() / RAND_MAX * 10000 + 1; // случайное число для поиска 
			Search_binary(a, big_n, el);
		}
		auto end2 = steady_clock::now();
		milliSeconds2 = duration_cast<milliseconds>(end2 - begin2).count();
		//milliSeconds2 = duration_cast<seconds>(end2 - begin2).count();
		
		// измеряем Интерполяционный поиск
		auto begin3 = steady_clock::now();
		for (int i = 0; i < 10000000; i++)
		{
			el = (int)rand() / RAND_MAX * 10000 + 1; // случайное число для поиска 
			Search_interpolation(a, big_n, el);
		}
		auto end3 = steady_clock::now();
		milliSeconds3 = duration_cast<milliseconds>(end3 - begin3).count();
		//milliSeconds3 = duration_cast<seconds>(end3 - begin3).count();
		
		//if (big_n >= 1000000000) big_n += big_n * 2;
		//else big_n *= 10;
		
		// сколько заняло миллисекунд 5 итераций
		cout << "Время (в миллисекундах) для Sequential Search: " << milliSeconds1 / 10000 << endl;
		cout << "Время (в миллисекундах) для Binary Search: " << milliSeconds2 / 1000000 << endl;
		cout << "Время (в миллисекундах) для Interpolation Search: " << milliSeconds3 / 10000000 << endl;

		//cout << "Время (в секундах) для Sequential Search: " << milliSeconds1 / 5 << endl;
		//cout << "Время (в секундах) для Binary Search: " << milliSeconds2 / 5 << endl;
		//cout << "Время (в секундах) для Interpolation Search: " << milliSeconds3 / 5 << endl;
		cout << endl;

		delete[] a;
	}
	cout << "-----------------------------------------------------" << endl;

	delete[] Iarr;
	delete[] Darr;
	return 0;
}

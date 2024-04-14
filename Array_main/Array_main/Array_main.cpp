/// \file Array_main.cpp
/// \brief тело основной программы
/// \brief подготовительный код для работы с массивами,
/// \brief использован одномерный динамический массив
/// \brief для хранения размера массива, индексов использован тип size_t
/// \brief выделение памяти для массива, освобождение памяти массива
/// \brief передача массива в функции, возврат из функции через return, указатели * и ссылки &
/// \brief использованы шаблонные функции template с типом <typename TArray>
/// \brief применение srand(time(NULL)) и rand() для случайных чисел
/// \brief демонстрация работы с библиотекой <fstream> с файлами
/// \brief записи в файлы текстовый и бинарный
/// \brief проверка, отсортирован ли массив, автоматический тест для шаблонной функции (assert)
/// \brief автоматическое тестирование программы с помощью assert
/// \brief создан репозиторий в GitHub
/// \author Бурдинская Наталья ВМК-22
/// \date 18.02.2024

#include "Modul_array.h" // вызов заголовочного файла Modul_array
#include "Modul_file.h" // вызов заголовочного файла Modul_file

int main()
{
	system("chcp 65001 > nul"); //подключение русского языка 
	setlocale(LC_ALL, "RUSSIAN");
	// Генерирует случайное число, используя текущею дату, для непредсказуемости результата
	srand(time(0));
	/// *** выделены в отдельные тесты
	Test_Work_array(); // работа с массивами в Modul_array.h
	Test_Work_files(); // работа с файлами в Modul_file.h
	Test_sortArr();  // работа с функции sortArr
	cout << "-----------------------------------------------------" << endl;
	cout << endl;
	// Измерение времени работы кода
	/// *** в секундах
	double el = 100.0;
	//cout << fixed << setprecision(5); // три знака после запятой
	double* time = new double[5];
	double key = 0;
	for (int i = 0; i < 100; i++)
	{
		cout << i + 1 << " итерация" << endl;

		auto begin = steady_clock::now();
		(Search_sequential(Darr, Asize, el) == -1) ?
			cout << el << " не найден в этом массиве" << endl :
			cout << el << " был найден по указателю: " << key << endl;
		auto end = steady_clock::now();

		//auto elapsedSeconds = duration_cast<seconds>(end - begin).count();
		auto elapsedSeconds = duration_cast<milliseconds>(end - begin).count();
		time[i] = elapsedSeconds;
		//cout << "Прошедшее время (в секундах): " << elapsedSeconds << endl; // сколько заняло секунд
		cout << "Прошедшее время (в миллисекундах): " << elapsedSeconds << endl; // сколько заняло секунд
	}
	// вычисляем среднее время итераций
	double everageTime = (time[0] + time[1] + time[2] + time[3] + time[4]) / 5;
	//cout << endl << "Затраченное время (среднее): " << everageTime << " сек." << endl;
	cout << endl << "Затраченное время (среднее): " << everageTime << " мсек." << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << endl;

	delete[] Iarr;
	delete[] Darr;
	cout << "-----------------------------------------------------" << endl;
	return 0;
}

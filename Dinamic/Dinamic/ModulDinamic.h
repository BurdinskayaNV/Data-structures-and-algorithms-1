/// \file ModulDinamic.h
/// \brief Dynamic programming - Динамическое программирование
/// \author Бурдинская Наталья ВМК-22
/// \date 10.03.2024

#pragma once
#include <iostream>  //объявляет cin cout
#include <cassert>   //для assert
#include <locale>    // определяет функцию setlocale для установки русской локали
#include <string>    //для использования строк
#include <fstream>   // для работы с файлами
#include <exception> // обработка исключений
#include <cstdlib>   // случайные числа
#include <ctime>     // время для работы с rand()
using namespace std;
const string infile = "input.txt";
const string outfile = "output.txt";

/// функция выделение памяти для двумерного массива N х М
/// \param n первое целое число 
/// \param m второе целое число
/// \param n x m размерность матрицы
/// \return ** объявляет указатель на int, на выходе будет целочисленная матрица А
static int** Memo_Array(int n, int m)
{
	// инициализация всего двумерного массива нулями
	int** a = new int* [n]; // строк N
	for (size_t i = 1; i <= n; i++) a[i] = new int[m + 1] {0}; // столбцов M
	a[n][m] = 2;  // правый нижний из которых «отравлен» равен 2
	// если a[n][m] = 0 - это кусок пирога
	// если a[n][m] = 1 - этот кусок пирога съели
	// если a[n][m] = 2 - это отравленный кусок пирога
	return a; // возврат двумерного массива А из функции Memo_Array
}

/// процедура вывода на экран двумерного массива N х М
/// \param a матрица - пирог
/// \param n первое целое число 
/// \param m второе целое число
/// \param n x m размерность матрицы
/// \return процедура ничего не возвращает, просто выводит массив на экран
static void Screen_Array(int** a, size_t n, size_t m)
{
	cout << "если a[n][m] = 0 - это кусок пирога" << endl;
	cout << "если a[n][m] = 1 - этот кусок пирога съели" << endl;
	cout << "если a[n][m] = 2 - это отравленный кусок пирога" << endl;
	cout << endl;
	for (size_t i = 1; i <= n; i++) // строк N
	{
		for (size_t j = 1; j <= m; j++) // столбцов M
			cout << a[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

/// <summary>
/// Входные данные. Начальное открытие файла.
/// Данные во входном файле расположены в следующем порядке: N, M (1 ≤ N, M ≤ 9), X1, ...,XN.
/// Здесь Xi – число оставшихся клеток в i-м снизу горизонтальном ряду.
/// Запись в новый файл input.txt или перезапись старого файла input.txt
/// </summary>
/// <param infile = "input.txt"></param>
/// <param name="a"></param>
/// <param name="n"></param>
/// <param name="m"></param>
static void WriteInFile(const string& infile, int** a, size_t n, size_t m)
{
	string str;
	// режим открытия файла дл¤ записи ios::out
	// устанавливаетс¤ при создании файла
	ofstream Fin(infile, ios::out); //затирает старые и пишет новые данные
	if (!Fin.is_open())   // Если не открыт файл
	{
		throw runtime_error("Файл input.txt не найден");
	}
	Fin << "Начало" << endl;
	Fin << endl;
	// пишем в файл заданные n и m
	Fin << n << " " << m << endl;
	// пишем в файл оставшиеся куски пирога
	for (size_t i = 1; i <= n; i++) // строк N
	{
		str = "";
		for (size_t j = 1; j <= m; j++) // столбцов M
		{
			if ((a[i][j] == 0) || (a[i][j] == 2)) str = str + to_string(a[i][j]) + " ";
		}
		Fin << str << endl;
	}
	Fin << endl;
	Fin.close(); // функция close() закрывает поток файла
	cout << "Пишем в текстовый файл input.txt. Конец записи в файл." << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << endl;
}

/// <summary>
/// Входные данные. добавление записей в файл
/// Данные во входном файле расположены в следующем порядке: N, M (1 ≤ N, M ≤ 9), X1, ...,XN.
/// Здесь Xi – число оставшихся клеток в i-м снизу горизонтальном ряду.
/// Добавление записи в существующий файл input.txt
/// </summary>
/// <param infile = "input.txt"></param>
/// <param name="a"></param>
/// <param name="n"></param>
/// <param name="m"></param>
static void AddInFile(const string& infile, int** a, size_t n, size_t m, int x, int y, int z)
{
	string str, ss;
	if (z == 0) ss = "ход компьютера";
	else ss = "ваш ход";
	// режим открытия файла для записи ios::app
	// устанавливаетс¤ при создании файла
	ofstream Fin(infile, ios::app); //добавляет данные
	if (!Fin.is_open())   // Если не открыт файл
	{
		throw runtime_error("Файл input.txt не найден");
	}
	// пишем в файл заданные x и y
	Fin << x << " " << y << " " << ss << endl;
	// пишем в файл оставшиеся куски пирога
	for (size_t i = 1; i <= n; i++) // строк N
	{
		str = "";
		for (size_t j = 1; j <= m; j++) // столбцов M
		{
			if ((a[i][j] == 0) || (a[i][j] == 2)) str = str + to_string(a[i][j]) + " ";
			else str = str + "  ";
		}
		Fin << str << endl;
	}
	Fin << endl;
	Fin.close(); // функция close() закрывает поток файла
	cout << "Пишем в текстовый файл input.txt. Конец записи в файл." << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << endl;
}

/// <summary>
/// Выходные данные В первую строку выходного файла необходимо вывести количество различных выигрышных ходов К,
/// а в последующие K строк – сами выигрышные ходы.
/// Каждый ход задается парой чисел (i, j), где i – номер (снизу) горизонтального ряда, а j –номер (справа) вертикального ряда,
/// которому принадлежит выбранная клетка (1 ≤ i ≤ N, 1≤ j ≤ M). 
/// </summary>
/// <param outfile = "output.txt"></param>
/// <param name="a"></param>
/// <param name="n"></param>
/// <param name="m"></param>
static void AddOutFile(const string& outfile, string fstr, int k, int z)
{
	string ss;
	if (z == 0) ss = "компьютер";
	else ss = "ваша игра";
	// режим открытия файла дл¤ записи ios::app
	// устанавливаетс¤ при создании файла
	ofstream Fout(outfile, ios::app); //добавляет данные
	if (!Fout.is_open())   // Если не открыт файл
	{
		throw runtime_error("Файл output.txt не найден");
	}
	// пишем в файл k количество удачных ходов
	Fout << k << " " << ss << endl;
	// пишем в файл съевшие куски пирога
	Fout << fstr << endl;
	Fout << endl;
	Fout.close(); // функция close() закрывает поток файла
	cout << "Пишем в текстовый файл output.txt. Конец записи в файл." << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << endl;
}

/// функция поиска *** несъеденных неотравленных кусков
/// \param n первое целое число 
/// \param m второе целое число
/// \param n x m размерность матрицы
/// \return функция boolean, на выходе будет false или true
static bool Search_pie(int** a, size_t n, size_t m)
{
	for (size_t i = 1; i <= n; i++) // строк N
	{
		for (size_t j = 1; j <= m; j++) // столбцов M
		{
			//if ((a[i][j] == 0) || (a[i][j] == 2)) {
			if (a[i][j] == 0) {
				return true; break;
			}
			else return false;
		}
	}
}

//---тест работы функции Search_pie
void Test_Search_pie()
{
	int n = 2, m = 2;
	// инициализация всего двумерного массива нулями
	int** a = new int* [n]; // строк N
	for (size_t i = 1; i <= n; i++) a[i] = new int[m + 1] {0}; // столбцов M
	a[2][2] = 2;  // правый нижний из которых «отравлен» равен 2

	bool test1 = Search_pie(a, n, m);
	assert(test1 == true);
	
	a[1][2] = 1; a[2][1] = 1; a[1][1] = 1;
	bool test2 = Search_pie(a, n, m);
	assert(test2 == false); // только остался отравленный
	
	cout << "_Тест_ASSERT_функции_Search_pie_выполнен_успешно_" << endl;
}

/// функция рандомного числа Х
/// \param n первое целое число 
/// \param n x m размерность матрицы
/// \param Х целое число, кооржината последнего съеденного куска пирога
/// \return возвращает X или Y
static int Random(size_t n, int x)
{
	return 1 * (n - x) * rand() / RAND_MAX + x; // [x,n]
}

/// процедура задания координат пирога для компьютера ///*** разделить на компьютерный 
/// \param a матрица - пирог
/// \param n первое целое число 
/// \param m второе целое число
/// \param n x m размерность матрицы
/// \param X и Y координаты пирога
/// \return процедура ничего не возвращает, просто задает X и Y
void Move_Computer(int** a, size_t n, size_t m, int& x, int& y)
{
	int k = x; int l = y;
	cout << "КОМПЬЮТЕР ваш ход x <= n и y <= m" << endl;
	do
	{
		x = Random(n, x);
		y = Random(m, y);
		bool v = Search_pie(a, n, m);
		if ((x == n) && (y == m-1) && (a[n][m-2] == 0))
		{
			y = m - 2;
		}
		if ((x == n-1) && (y == m) && (a[n-2][m] == 0))
		{
			y = n - 2;
		}
		if ((v == true) && (a[x][y] == 2))
		{
			Move_Computer(a, n, m, k, l);
		}
	} while (a[x][y] == 1);
}

/// процедура задания координат пирога руками ///*** разделить на компьютерный 
/// \param a матрица - пирог
/// \param n первое целое число 
/// \param m второе целое число
/// \param n x m размерность матрицы
/// \param X и Y координаты пирога
/// \return процедура ничего не возвращает, просто задает X и Y
void Move_Man(int& x, int& y)
{
	cout << "Введите координаты куска пирога x <= n и y <= m" << endl;
	// сохраняем их в x и y
	cout << "X = "; cin >> x;
	cout << "Y = "; cin >> y;
	cout << endl;
}

/// функция результата поедания ///*** разделить на компьютерный 
/// \param a матрица - пирог
/// \param n первое целое число 
/// \param m второе целое число
/// \param n x m размерность матрицы
/// \param X и Y координаты пирога
/// \param Z признак хода комьютер или человек
/// \return возвращает результат поедания пирога
static int Rezult_Eating(int** a, size_t n, size_t m, int x, int y, int z)
{
	// если координаты выходят за пределы массива
	if ((x > n) || (y > m)) {
		cout << "Такого куска нет в пироге, задайте новые координаты... " << endl;
		cout << endl;
		return 0;
	}
	// если по координатам кусок уже съеден
	else if (a[x][y] == 1) {
		cout << "Этот кусок пирога съели, возьмите другой... " << endl;
		cout << endl;
		return 0;
	}
	// если по координатам кусок отправлен
	else if (a[x][y] == 2)
	{
		if (z == 0) cout << "Компьютер ПРОИГРАЛ, кусок отравлен..." << endl;
		else cout << "ВЫ ПРОИГРАЛИ, кусок отравлен..." << endl;
		cout << endl;
		return 1;
	}
	// кусок можно съесть
	else
	{
		// тест на наличие кусков пирога
		//***Test_Search_pie();
		bool v = Search_pie(a, n, m);
		if (v = true)
		{
			cout << "Этот кусок можно съесть !!! " << endl;
			cout << endl;
			//if (z == 0) z = 1; else z = 0;
			return 2;
		}
	}
}

//---тест работы функции Rezult_Eating
void Test_Rezult_Eating()
{
	cout << "________Тестирование_Rezult_Eating__________________" << endl;
	int n = 2, m = 2, z = 1;
	// инициализация всего двумерного массива нулями
	int** a = new int* [n]; // строк N
	for (size_t i = 1; i <= n; i++) a[i] = new int[m + 1] {0}; // столбцов M
	a[2][2] = 2;  // правый нижний из которых «отравлен» равен 2

	int test1 = Rezult_Eating(a, n, m, 3, 3, z); // если таких координат нет
	assert(test1 == 0);

	a[1][2] = 1; a[2][1] = 1;
	int test2 = Rezult_Eating(a, n, m, 2, 2, z); // если съеден отравленный кусок
	assert(test2 == 1);

	int test3 = Rezult_Eating(a, n, m, 1, 2, z); // если съеден не отравленный кусок
	assert(test3 == 0);

	a[1][2] = 1; a[2][1] = 0;
	int test4 = Rezult_Eating(a, n, m, 2, 1, z); // если кусок можно съесть
	assert(test4 == 2);

	cout << "_Тест_ASSERT_функции_Rezult_Eating_выполнен_успешно_" << endl;
	cout << "____________________________________________________" << endl;
}

/// процедура поедания пирога ///*** разделить на компьютерный 
/// \param a матрица - пирог
/// \param n первое целое число 
/// \param m второе целое число
/// \param n x m размерность матрицы
/// \return процедура ничего не возвращает, просто выводит массив на экран
/// \return Мемоизация
static void Eating_pie(int** a, size_t n, size_t m, int z)
{
	int x = 1, y = 1; string str; string fstr; int k;
	if (z == 0) { Move_Computer(a, n, m, x, y); }
	else { Move_Man(x, y); };
	cout << "X = " << x << "   Y = " << y << endl;
	cout << endl;

	//***Test_Rezult_Eating();
	int rez = Rezult_Eating(a, n, m, x, y, z);
	if (rez == 0) Eating_pie(a, n, m, z);
	else if (rez == 1)
	{
		cout << "Игра закончена." << endl;
		cout << endl;
	}
	else if (rez == 2)
	{
		fstr = ""; k = 0;
		for (size_t i = 1; i <= x; i++) // строк N
		{
			for (size_t j = 1; j <= y; j++) // столбцов M
			{
				if (a[i][j] == 0)
				{
					fstr = fstr + "(" + to_string(i) + "," + to_string(j) + ")" + " ";
					k = k + 1;
					a[i][j] = 1;
				}
			}
		}
		Screen_Array(a, n, m);
		AddInFile(infile, a, n, m, x, y, z);
		AddOutFile(outfile, fstr, k, z);
		if (z == 0) z = 1; else z = 0;
		Eating_pie(a, n, m, z);
	}
}

/// функция освобождение памяти двумерного массива N х М
/// \param a матрица - пирог
/// \param n первое целое число 
/// \param m второе целое число
/// \param n x m размерность матрицы
/// \return процедура ничего не возвращает, просто очищает память массива
static void Del_Array(int** a, size_t n, size_t m)
{
	for (size_t i = 1; i <= n; i++)
	{
		delete[] a[i];
	}
	delete[] a;
}
/// \file String_main.cpp
/// \brief Тело основной программы
/// \author Бурдинская Наталья ВМК-22
/// \date 10.05.2024

#include <iostream> // для работы с потоками ввода-вывода
#include <locale>   // определяет функцию setlocale для установки русской локали
#include "StringLegacy.h" // строковое наследие Legacy
#include "TestStringLegacy.h" // тестирование строковое наследие Legacy

using namespace std;

int main()
{
	// «Rus» локализация произойдёт на русский язык
	setlocale(LC_ALL, "russian");
	cout << endl;
	test();
}

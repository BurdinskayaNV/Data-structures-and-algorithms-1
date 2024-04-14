/// \file Modul_file.h
/// \brief Работа с файлами
/// \author Бурдинская Наталья ВМК-22
/// \date 18.02.2024
#pragma once

#include "Modul_array.h" // вызов заголовочного файла Modul_array

//---процедурa записи в текстовый файл TxtArray.txt
// массив a, size, file_name - формальные параметры
// ничего не возвращает, просто пишет массив в файл
template <typename TArray>
void WriteFile(const string& file_name, const TArray* a, size_t size)
{
	// режим открытия файла дл¤ записи ios::out
	// устанавливаетс¤ при создании файла
	ofstream Fin(file_name, ios::out); //затирает старые и пишет новые данные
	if (!Fin.is_open())	  // Если не открыт файл
	{
		throw runtime_error("Файл не найден");
	}
	// пишем в файл отправленный массив
	for (size_t i = 0; i < size; ++i)
	{
		Fin << a[i] << " " << endl;
	}
	Fin.close(); // функция close() закрывает поток файла
	cout << "Пишем в текстовый файл. Конец записи в файл." << endl;
	cout << "-----------------------------------------------------" << endl;
}

//-----процедурa чтения из текстового файла TxtArray.txt
// массив a, size, file_name - формальные параметры
// возвращает прочитанный массив a из файла
template <typename TArray>
void ReadFile(const string& file_name, TArray* a, size_t size)
{
	ifstream Fout; // объявляем имя Fout для чтения
	//Режим открыть файл для чтения ios::in можно установить при
	//вызове метода open(), необязательно при создании файла(процедура выше)
	Fout.open(file_name, ios::in); //открываем файл для чтения на начале
	//проверяю на наличие файла
	if (!Fout.is_open())	  // Если не открыт файл
	{
		throw runtime_error("Файл не найден");
	}
	if (!Fout.eof()) // делаем пока не конец файла
	{
		for (size_t i = 0; i < size; ++i) { Fout >> a[i]; }
	}
	Fout.close(); // Функция close() закрывает поток файла
	cout << "Читаем из текстового файла. Конец файла." << endl;
}

//---функция поиска количества элементов массива в текстовом файле TxtArray.txt
size_t SizeFile(const string& file_name)
{
	size_t res = 0; // Переменная для счета количества строк
	ifstream file(file_name); // Открытие файла 
	if (!file.is_open()) // Если не открыт файл
	{
		throw runtime_error("Файл не найден!"); // Если что, то в ошибку
	}
	// Цикл счёта количества строк -> количества элементов массива
	while (!file.eof()) // делаем пока не конец файла
	{
		char c;
		file >> c;
		res++; // Цикл будет жить, пока getline делает переходы
	}
	file.close(); // Закрыть файл
	if (res == 0) // Ошибка, если файл пуст
		throw runtime_error("Массив не найден в текстовом файле - файл пуст");
	return res;
}

//---процедурa записи в бинарный файл BinArray.txt // переименовать
//// подробно описать все арг 
template <typename TArray>
void WriteFileBin(const string& file_name, const TArray* arr, size_t size)
{
	ofstream file(file_name, ios::binary);
	// Оператор приведения reinterpret_cast используется для приведения несовместимых типов
	file.write(reinterpret_cast<const char*>(&size), sizeof(size));
	file.write(reinterpret_cast<const char*>(arr), sizeof(TArray) * size);
	file.close();
	cout << "Пишем в бинарный файл. Конец записи в файл." << endl;
	cout << "-----------------------------------------------------" << endl;
}

//-----процедурa чтения из бинарного файла BinArray.txt
template <typename TArray>
void ReadFileBin(const string& file_name, TArray*& arr, size_t& size)
{
	// Оператор приведения reinterpret_cast используется для приведения несовместимых типов
	ifstream file(file_name, ios::binary);
	file.read(reinterpret_cast<char*>(&size), sizeof(size));
	arr = new TArray[size];
	file.read(reinterpret_cast<char*>(arr), sizeof(TArray) * size);
	file.close();
	cout << "Читаем из бинарного файла. Конец файла." << endl;
}

//---тест работы с файлами
/// *** выделен в отдельный тест
void Test_Work_files()
{
	cout << "------- Работа с текстовым файлом -------------------" << endl;
	// выполняем запись массива в текстовый файл TxtArray.txt
	try { WriteFile(fileTxt, Iarr, Asize); }
	catch (const invalid_argument& error) {
		cout << error.what();
	}
	// читаем из текстового файла TxtArray.txt массив и выдаем на консоль
	try   // проверка на исключения
	{
		// Находим количество элементов массива из файла TxtArray.txt
		size_t size_1 = SizeFile(fileTxt);
	}
	catch (const exception& error) // файл TxtArray.txt не открыт или пуст
	{
		// Код, который выполняется при возникновении исключения типа
		// Exception генерируется в блоке try
		cout << error.what() << endl; // Завершить
	}
	// выводим на экран массив введеных коэффициентов
	int* arrtxt = new int[Asize] {0}; // описываем динамический массив Int
	try { ReadFile(fileTxt, arrtxt, Asize); }
	catch (const invalid_argument& error) {
		cout << error.what();
	}
	Screen_array(arrtxt, Asize); // выводим на экран массив введеных коэффициентов
	cout << endl;

	cout << "------- Работа с бинарным файлом --------------------" << endl;
	// выполняем запись массива в текстовый файл TxtArray.txt
	try { WriteFileBin(fileBin, Iarr, Asize); }
	catch (const invalid_argument& error) {
		cout << error.what();
	}
	// выводим на экран массив введеных коэффициентов
	int* arrbin = new int[Asize] {0}; // описываем динамический массив Int
	try { ReadFileBin(fileBin, arrbin, Asize); }
	catch (const invalid_argument& error) {
		cout << error.what();
	}
	Screen_array(arrbin, Asize); // выводим на экран массив введеных коэффициентов
	cout << endl;
	cout << "-----------------------------------------------------" << endl;
	delete[] arrtxt;
	delete[] arrbin;
}
/// \file Modul_array.h
/// \brief Работа с массивами
/// \author Бурдинская Наталья ВМК-22
/// \date 29.03.2024

#pragma once
#include <cstdlib>   // работа с памятью memcpy
#include <string>    // для использования строк
#include <iomanip>   // для setw setprecision
#include <cassert>   // для assert
#include <iostream>  // объявляет cin cout
#include <ctime>     // время для рандомных элементов массива
#include <fstream>   // для работы с файлами
#include <exception> // обработка исключений
#include <locale>    // определ¤ет функцию setlocale для русской локали 
#include "Array.h" 
using namespace std; // пространоство имен std::

// Шаблон тип массива
template <typename Type>
class DinamoArray
{
private:   // указываем поля класса DinamoArray
    Type* arr; // указатель на начало массива тип шаблонный typename Type
    size_t indexLastArr; // индекс последней свободной ячейки
    size_t size;     // размер массива arr
public:

    // Конструктор без параметров, выделить память
    DinamoArray()
    {
        size = 0; indexLastArr = 0; arr = nullptr;
    } // nullptr — описания константы нулевого указателя


    // Конструктор с параметрами
    DinamoArray(size_t _size, const Type& value = 0)
    {
        if (_size > 0)
        {
            size = _size;
            // задаем параметр indexLastArr
            indexLastArr = _size; // индекс равен последнему элементу _size размерности массива arr ///*** 
            arr = new Type[size];
            // задаем сам массив arr
            for (size_t i = 0; i < size; i++)
            {
                arr[i] = value; // value = 0
            }

        }
        else
            throw invalid_argument("Недопустимое значение размера " + to_string(_size));
    }

    ///*** правило пяти 
/*
1. Деструктор.
2. Конструктор копирования.
3. Оператор присваивания копированием.
4. Конструктор перемещения.
5. Оператор присваивания перемещением.
*/

//  1. Деструктор
    ~DinamoArray() {
        if (arr = nullptr)
        {
            delete arr;
        }
        else
        {
            delete[] arr;
        }
    }

    // 2. конструктор копирования
    DinamoArray(const DinamoArray& other) : arr(new Type(*other.arr)), indexLastArr(new size_t(other.indexLastArr)), size(new size_t(other.size)) {}

    // 3. оператор присваивания копированием  ///*** 
    DinamoArray& operator=(const DinamoArray<Type>& other) {
        if (this != &other) {
            *arr = *other.arr; // выделить памятьпо arr и в нее скопировать все эл 
            indexLastArr = other.indexLastArr;
            size = other.size;
        }
        return *this;
    }

    // 4. конструктор перемещения
    DinamoArray(DinamoArray&& other) noexcept : arr(other.arr), indexLastArr(other.indexLastArr), size(other.size) {
        other.arr = nullptr;
        other.indexLastArr = nullptr;
        other.size = nullptr;
    }

    // 5. оператор присваивания перемещением
    DinamoArray& operator=(DinamoArray&& other) noexcept {
        if (this != &other) {
            delete arr;
            arr = other.arr;
            other.arr = nullptr;
            delete indexLastArr;
            indexLastArr = other.indexLastArr;
            other.indexLastArr = nullptr;
            delete size;
            size = other.size;
            other.size = nullptr;
        }
        return *this;
    }

    //***
    // Перегрузка оператора [] для доступа к определенным элементам массива
    // Средний: O(1)
    Type& operator[](size_t index)
    {
        if (index < size)
        {
            return arr[index];
        }
        else
            // исключение, если не index < size
            throw invalid_argument("Недопустимое значение индекса");
    }
    
    // Процедура изменяет размерность массива в большую сторону и меньшую
    // new_size новая размерность массива, (-/+) size
    /// Средний: O(n)
    void Resized(size_t new_size)
    {
        Type* new_arr = new Type[new_size]; // выделяем память на новый массив
        // Копирование элементов из старого массива в новый
        size_t elementsToCopy = min(new_size, size);
        //size_t elementsToCopy = new_size;
        copy(arr, arr + elementsToCopy, new_arr);
        delete[] arr; // Освобождение памяти старого массива
        arr = new_arr; // записываем новые значения в массив
        //indexLastArr = new_size;
        size = new_size; ///---*** убрать и не менять индекс последнего
    }
        
    // Функция длины массива
    // return Возвращает размер массива типа size_t
    /// Средний: O(1)
    size_t lenght() const
    {
        return indexLastArr;
    }
    
    // Процедура добавляет элемент в массив в конец
    // new_element элемент, который нужно добавить в конец массива
    /// Средний: О(1) | Худший: O(n)
    void Add_Back(Type new_element)
    {
        if (indexLastArr < size)
        {
            arr[indexLastArr] = new_element;
            indexLastArr++;
        }
        else
        {
            Resized(indexLastArr);
            arr[indexLastArr] = new_element;
            indexLastArr = indexLastArr + 1;
        }
    }
    
    // Процедура добавляет элемент в массив в начало
    // new_element элемент, который нужно добавить в начало массива
    /// Средний: О(n)
    void Add_Front(Type new_element)
    {
        // если есть место начале, иначе надо увеличить размерность массива сначала
        if (indexLastArr < size)
        {
            // Сдвигаем все элементы "вправо" и освобождаем место
            copy(arr, arr + size - 1, arr + 1);
            arr[0] = new_element; // вставляем новый элемент в начало
            size++; // увеличиваем размерность на 1
            indexLastArr++; // увеличиваем значение последнего индекса на 1
        }
        // иначе надо увеличить размерность массива сначала
        else
        {
            Resized(indexLastArr);
            // Сдвигаем все элементы "вправо"
            copy(arr, arr + size - 1, arr + 1);
            arr[0] = new_element; // вставляем новый элемент в начало
            size++; // увеличиваем размерность на 1
            indexLastArr++; // увеличиваем значение последнего индекса на 1        }
        }
    }

    // Процедура удаляет последний элемент массива
    /// Средний: O(1)
    void Delete_Last()
    {
        if (indexLastArr >= 0) // делаем, если не пусто
        {
            copy(arr, arr - indexLastArr, arr);
            indexLastArr -= 1; // уменьшаем значение последнего индекса на 1 
        }
        else
        {
            throw invalid_argument("Этот массив уже пуст!");
        }
    }

    // Процедура удаляет первый элемент массива
    /// Средний: O(n)
    void Delete_Firts()
    {
        if (indexLastArr >= 0) // делаем, если не пусто
        {
            copy(arr + 1, arr + indexLastArr, arr);
            indexLastArr -= 1; // уменьшаем значение последнего индекса на 1
        }
        else // если массив пустой
        {
            throw invalid_argument("Этот массив уже пуст!");
        }
    }
    
    // Процедура Ищет элемент findThis в массиве с помощью Sequatial_search
    // findThis элемент, который ищем
    // Возращает индекс найденного элемента или -1, если не нашел
    /// Средний: O(n)
    long long Search(Type findThis) const
    {
        return sequential_search(arr, indexLastArr, findThis);
    }

    // Процедура Сортировка массива методом Merge_sort
    /// Средний: O(n log n)
    void Sort()
    {
        // сортировка
        merge_sort(arr, 0, indexLastArr - 1);
    }
    
    // Перезапись оператора приравнивания на оператор копирования
    /// O(n)
    /*DinamoArray&
        operator=(const DinamoArray<Type>& other)
    {
        if (this != &other)
        {
            if (arr != nullptr)
                delete[] arr; // освобождение памяти
            // копирование
            size = other.size;
            indexLastArr = other.indexLastArr;
            arr = new Type[indexLastArr];
            memcpy(arr, other.arr, other.size * sizeof(Type));
        }
        return *this;
    }*/
   
    // Деструктор массива
    /*~DinamoArray()
    {
        if (arr = nullptr)
        { delete arr; }
        else
        { delete[] arr; }
    }*/
};

// Тест Add_Back и Add_Front
void testAdd()
{
    DinamoArray<int> arr(2); // массив из двух элементов = 2
    arr.Add_Back(321);       // + один с хвоста = 3
    arr.Add_Front(123);      // + один с головы = 4
    arr.Add_Back(654);       // + еще один с хвоста = 5
    assert(arr.lenght() == 5);

    assert(arr[0] == 123);
    assert(arr[3] == 321);
    assert(arr[4] == 654);
    cout << "================================================";
    cout << "Тест Add_Back и Add_Front выполнен успешно" << endl;
}

// Тест Resized изменение размерности массива
void testResized()
{
    DinamoArray<int> arr(3);
    arr.Resized(6); // меняем размерность 3 на 6
    assert(arr.lenght() == 6);

    arr[0] = 123;
    arr[1] = 321;
    // Проверка изменения размера на меньшее значение
    arr.Resized(2); // меняем размерность 6 на 2
    assert(arr.lenght() == 2);
    assert(arr[0] == 123); // Проверка, что первый элемент не изменился
    assert(arr[1] == 321); // Проверка, что второй элемент не изменился
    cout << "================================================";
    cout << "Тест Resize выполнен успешно" << endl;
}

// Тест Delete_Firts и Delete_Last
void testDelete()
{
    DinamoArray<int> arr(3);
    arr.Delete_Last();
    assert(arr.lenght() == 2);
    arr.Delete_Firts(); 
    assert(arr.lenght() == 1);
    cout << "================================================";
    cout << "Тест Delete_Firts и Delete_Last выполнен успешно" << endl;
}

// Тест Search
void testSearch()
{
    DinamoArray<int> arr(5); // тип Int
    for (int i = 0; i < 5; i++)
    {
        arr[i] = i;
    }
    assert(arr.Search(3) == 3);  // успешный поиск элемента в массиве
    assert(arr.Search(6) == -1); // нет элемента возвращает -1

    DinamoArray<double> arrD(5); // тип Double
    for (size_t i = 0; i < 5; i++)
    { arrD[i] = i * 1.1; }
    assert(arrD.Search(1.1) == 1); // успешный поиск элемента в массиве [1]

    // Проверим случай, когда элемент находится в середине массива
    DinamoArray<int> middle(5); // тип Int
    middle[0] = 1; middle[1] = 2; middle[2] = 3; middle[3] = 4; middle[4] = 5;
    assert(middle.Search(3) == 2); // успешный поиск элемента в середине массива

    // Проверим случай, когда элемент находится на границе массива
    DinamoArray<int> border(5); // тип Int
    border[0] = 1; border[1] = 2; border[2] = 3; border[3] = 4; border[4] = 5;
    assert(border.Search(5) == 4); // успешный поиск элемента на границе массива
    cout << "================================================";
    cout << "Тест Search выполнен успешно" << endl;
}

// Тест Sort
void testSort()
{
    DinamoArray<int> arr(5);
    arr[0] = 1; arr[1] = 4; arr[2] = 2; arr[3] = 3; arr[4] = 5;
    arr.Sort();
    assert(arr[0] == 1);
    assert(arr[1] == 2);
    assert(arr[2] == 3);
    assert(arr[3] == 4);
    assert(arr[4] == 5);
    // Проверка при сортировке массива с одним элементом
    DinamoArray<int> arrOne(1);
    arrOne[0] = 1000;
    arrOne.Sort();
    assert(arrOne[0] == 1000);
    // Проверка при сортировке массива, где все элементы равны
    DinamoArray<int> arrEqual(3);
    arrEqual[0] = 2;
    arrEqual[1] = 2;
    arrEqual[2] = 2;
    arrEqual.Sort();
    assert(arrEqual[0] == 2);
    assert(arrEqual[1] == 2);
    assert(arrEqual[2] == 2);
    cout << "================================================";
    cout << "Тест Sort выполнен успешно" << endl;
    cout << endl;
}


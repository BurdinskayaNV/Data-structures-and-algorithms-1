#pragma once
/// \file Spisok_one.h
/// \brief Работа с односвязным списком
/// \author Бурдинская Наталья ВМК-22
/// \date 29.03.2024

#include <iostream> //объявляет cin cout
#include <sstream>  //потоковой работы со строчным типом данных
#include <cassert>  //для assert
#include <locale>   //определяет функцию setlocale для установки русской локали

using namespace std;

// Шаблон тип списка 
template <typename Type>
class OneList // Односвязный список
{
public: // указываем поля класса OneList
    Type data; // Данные списка
    OneList<Type>* prev; // Указатель на предыдущей узел в списке
    OneList<Type>* next; // Указатель на следующий узел в списке

    // Конструктор по умолчанию
    OneList() : prev(nullptr), next(nullptr), data(Type()) {}

    // Конструктор с данными и обеими указателями
    /// @param data_ - данные узла
    /// @param prev_ - указатель на предыдущий узел
    /// @param next_ - указатель на следующий узел
    OneList(const Type& data_, OneList<Type>* prev_, OneList<Type>* next_) : data(data_), prev(prev_), next(next_) {}

    /// @brief Конструктор только с данными, указатели prev и next смотрят в null
    /// @param data_ - данные узла
    OneList(const Type& data_) : data(data_), prev(nullptr), next(nullptr) {}

    /// @brief Конструктор копирования
    OneList(const OneList<Type>& other)
        : data(other.data), prev(nullptr), next(nullptr) // пока что nullptr
    {
        if (other.prev != nullptr)
        {   // доступ через указатель, для копирования
            prev = new OneList(other.prev->data);
        }
        if (other.next != nullptr)
        {   // доступ через указатель, для копирования
            next = new OneList(other.next->data);
        }
    }

    /// @brief Конструктор перемещения
/// @param other То, что перемещаем
    OneList(OneList<Type>&& other)
        : data(other.data), prev(other.prev), next(other.next) // перемещаем указатели на пред и след
    {
        // чистим 
        other.prev = nullptr;
        other.next = nullptr;
    }

    /// @brief Оператор копирования
    /// @param other То, что копируем
    OneList<Type>& operator=(const OneList<Type>& other)
    {
        if (this != &other) // Проверка на самоприсваивание
        {
            delete prev;
            delete next;

            // копируем
            data = other.data;
            if (other.prev != nullptr)
            {
                // доступ через указатель, для копирования
                prev = new OneList(other.prev->data);
            }
            if (other.next != nullptr)
            {
                // доступ через указатель, для копирования
                next = new OneList(other.next->data);
            }
        }
        return *this;
    }

    /// @brief Оператор перемещения
    OneList<Type>& operator=(OneList<Type>&& other)
    {
        if (this != &other) // Проверка на самоприсваивание
        {
            data = other.data;
            prev = other.prev;
            next = other.next;

            other.prev = nullptr;
            other.next = nullptr;
        }
        return *this;
    }

    /// @brief Деструктор
    ~OneList()
    {
        /// Удаляем указатели на предыдущий и следующий узлы
        if (prev != nullptr && next != nullptr)
        {
            prev = nullptr;
            next = nullptr;
        }
    }
};

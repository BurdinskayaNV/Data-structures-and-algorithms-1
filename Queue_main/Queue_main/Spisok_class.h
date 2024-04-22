#pragma once
/// \file Spisok_class.h
/// \brief Работа с двусвязным списком
/// \author Бурдинская Наталья ВМК-22
/// \date 29.03.2024

#include "Spisok_one.h"

/// @brief Класс DoublyList есть двусвязный список
/// @tparam Type тип данных двусвязного списка
template <typename Type>
class DoublyList
{
private:
    OneList<Type>* head; // Указатель на голову списка
    OneList<Type>* tail; // Указатель на хвост списка
    size_t size; // Размер списка

public:
    /// @brief Конструктор по умолчанию
    DoublyList()
    {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    /// @brief Создает и заполняет список значениями value
    /// @param n Размер списка
    /// @param value То, чем заполняется список
    DoublyList(size_t n, const Type& value)
    {
        for (size_t i = 0; i < n; i++)
        {
            AddBack(value);
        }
    }

    /// @brief Конструктор копирования
    /// @param other, что копируем
    DoublyList(const DoublyList& other)
    {
        head = nullptr;
        tail = nullptr;
        size = 0;
        // Копируем элементы из другого списка
        copy(other);
    }

    /// @brief Конструктор перемещения
    /// @param other, что перемещам
    DoublyList(DoublyList&& other)
    {
        // Перемещаем элементы из другого списка.
        head = other.head;
        tail = other.tail;
        size = other.size;
        other.Forget();
    }

    /// @brief Оператор присваивания, но копирует
    /// @param other Что копирует
    /// @return Сокпированное
    DoublyList& operator=(const DoublyList& other)
    {
        if (this == &other)
        {
            return *this;
        }
        clearSpisok(); // Очищаем текущий список
        copy(other);   // Копируем элементы из другого списка
        return *this;
    }

    /// @brief Оператор присваивания, но перемещает
    /// @param other Что перемещает
    /// @return Перемещенное
    DoublyList& operator=(DoublyList&& other)
    {
        if (this == &other)
        {
            return *this;
        }
        clearSpisok(); // Очищаем текущий список
        // Перемещаем элементы из другого списка.
        head = other.head;
        tail = other.tail;
        size = other.size;
        other.Forget();
        return *this;
    }

    /// @brief Деструктор
    ~DoublyList()
    {
        clearSpisok();
    }

    /// @brief Глубокое копирование списка
    /// @param other, что копируем
    void copy(const DoublyList<Type>& other)
    {
        clearSpisok();
        // Итерационный узел
        OneList<Type>* current = other.head;
        while (current != nullptr)
        {
            AddBack(current->data);
            current = current->next;
        }
    }

    /// @brief Возвращает размер списка
    /// @return Размер списка
    size_t length() const
    {
        return size;
    }

    /// @brief Выводит список в строку
    /// @return Строку с списком вида
    string to_string() const
    {
        // Создаем строковый поток, для вывода списка
        stringstream spisok_stroka;
        spisok_stroka << "begin ";

        // Создадим узел в голову списка
        OneList<Type>* current = head;
        // Пока список не конец
        while (current != nullptr)
        {
            // вывод информации
            spisok_stroka << current->data;
            // вывод разделителя
            if (current->next != nullptr)
            {
                spisok_stroka << " ";
            }
            current = current->next;
        }
        spisok_stroka << " end";
        // преобразуем поток букв в строку
        return spisok_stroka.str();
    }

    /// @return Узел класса OneList
    OneList<Type>* get_OneList(size_t place)
    {
        if (place < 0 || place >= size)
        {
            throw out_of_range("Неверный индекс");
        }
        OneList<Type>* current = head;
        for (size_t i = 0; i < place; i++)
        {
            current = current->next;
        }
        return current;
    }

    /// @brief Сортировка списка по возрастанию пузырьком
    void sort()
    {
        if (size <= 1) { return; }
        //задаем два узла для сравнения
        OneList<Type>* current = head;
        OneList<Type>* nextNode = nullptr;
        while (current != nullptr)
        {
            nextNode = current->next;
            while (nextNode != nullptr)
            {
                // Сравнение текущего элемента с следующим элементом
                if (current->data > nextNode->data)
                {
                    // Обмен значениями текущего и следующего элементов
                    swap(current->data, nextNode->data);
                }
                // Переходим к след узлу
                nextNode = nextNode->next;
            }
            // Также переходим к след узлу
            current = current->next;
        }
    }

    /// @brief Находит узел с значением value
    /// @param value 
    /// @return Возращает узел со значением value
    OneList<Type>* find(Type value)
    {
        OneList<Type>* current = head;
        while (current != nullptr)
        {
            if (current->data == value)
            {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    /// @brief Чистим список
    void clearSpisok()
    {
        // Удаляем все узлы из списка
        while (head != nullptr)
        {
            OneList<Type>* nextNode = head->next;
            delete head;
            head = nextNode;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    /// @brief Вставка элемента в начало
    /// @param value 
    void AddFront(Type value)
    {
        // Создаем новый узел
        OneList<Type>* newList = new OneList<Type>(value);
        // Если список пустой, то новый узел становится узлом головы
        if (head == nullptr)
        {
            head = tail = newList;
        }
        // Иначе добавляем новый узел в начало списка
        else
        {
            newList->next = head; // в next нового положим head
            head->prev = newList; // в pred головы положим newList
            head = newList;       // переименовали голову
        }
        // Увеличиваем размер на 1
        size++;
    }

    /// @brief Вставка элемента в конец
    /// @param value То, что вставляем
    void AddBack(Type value)
    {
        // Создаем то, что будем вставлять
        OneList<Type>* newList = new OneList<Type>(value);
        // Если список пустой, то новый узел становится головой и хвостом
        if (tail == nullptr)
        {
            head = tail = newList;
        }
        else // Иначе добавляем его в конец списка
        {
            newList->prev = tail; // в предыдущий нового newList положим хвост tail
            tail->next = newList; // в следующий хвоста положим newList
            tail = newList;       // переименуем хвост
        }
        // Увеличиваем размер на 1
        size++;
    }

    /// @brief Вставит новый узел, содержащий value
    /// @param value То, что вставить нада
    /// @param node После чего вставить нада
    void AddInList(Type value, OneList<Type>* node)
    {
        // Если указанный узелок равен nullptr, кидаем его в конец списка
        if (node == nullptr)
        {
            AddBack(value);
            return;
        }
        // Создаем узел
        OneList<Type>* newList = new OneList<Type>(value);
        // Вставляем узелок после указанного
        newList->next = node->next;
        if (node->next != nullptr)
        {
            node->next->prev = newList;
        }
        else { tail = newList; }
        node->next = newList;
        newList->prev = node;
        // Увеличиваем размер списка на 1
        size++;
    }

    /// @brief Удаляет узел списка с его начала
    void DelFront()
    {
        // Если список пуст, то ошибка
        if (head == nullptr)
        {
            throw out_of_range("Список пуст!");
            return;
        }
        // временному узлу temp присваиваем голову head
        OneList<Type>* temp = head;
        // Меняем голову
        head = head->next;
        if (head != nullptr)
        {
            head->prev = nullptr;
        }
        else { tail = nullptr; }
        delete temp;
        // уменьшаем список на 1
        size--;
    }

    /// @brief Удаляет узел node из списка вашего
    /// @param node То, что надо удалить
    void DelInList(Type value)
    {
        if (head == nullptr)
        {
            throw out_of_range("Список пуст!");
            return;
        }
        // Временный узел
        OneList<Type>* temp = this->find(value);
        // Если временный узел пуст
        if (temp != nullptr)
        {
            // Смотрим, если голова, удаляем голову
            if (temp == head)
            {
                this->DelFront();
            }
            // Смотрим, если хвост, удаляем хвост
            else if (temp == tail)
            {
                this->DelBack();
            }
            else
            {
                // Иначе удаляем указанный узел из середины списка
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
        }
        else
        {
            throw invalid_argument("В этом списке нет этого значения!");
        }
        // Уменьшаем
        size--;
    }

    /// @brief Удаляет узел списка с его конца
    void DelBack()
    {
        // Если список пуст, ошибка
        if (tail == nullptr)
        {
            throw out_of_range("Список пуст!");
            return;
        }
        // Хвост временно запоминаем
        OneList<Type>* temp = tail;
        // Меняем хвост
        tail = tail->prev;
        if (tail != nullptr)
        {
            tail->next = nullptr;
        }
        else { head = nullptr; }
        delete temp;
        size--;
    }

    void ConcatenateLists(DoublyList<Type> other)
    {
        // Проверяем, является ли список "other" пустым
        if (other.head == nullptr)
        {
            return;
        } // Если список "other" пуст, выходим из функции
      // Если текущий список пуст, присваиваем ему значения из списка "other"
        if (head == nullptr)
        {
            head = other.head;
            tail = other.tail;
        }
        else
        {
            // Если текущий список не пуст, добавляем элементы из "other" в конец текущего списка
            tail->next = other.head; // Устанавливаем указатель на следующий элемент последнего элемента текущего списка
            other.head->prev = tail; // Устанавливаем указатель на предыдущий элемент первого элемента списка "other"
            tail = other.tail;       // Обновляем указатель на хвост текущего списка
        }
        size += other.size; // Увеличиваем размер текущего списка на размер списка "other"
        // Обнуляем указатели и размер списка "other" 
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }
};

/// \file StringLegacy.h
/// \brief Работа с классом строк
/// \author Бурдинская Наталья ВМК-22
/// \date 10.05.2024

#pragma once
#include <string.h>   // для работы с C-строками, такие как strcpy, strcat и т.п.
#include <memory>     // для работы с динамическим выделением памяти
#include <string>     // для строковых переменных C++
#include <vector>     // Для работы с вектором
#include <stdexcept>  // для сообщения об исключениях
#include <iostream>   // для работы с потоками ввода-вывода
#include <fstream>    // для создания файлов и записи информации в них.
#include <cassert>    // Для применения макроса assert()
#include <assert.h>   // объявляется макрос препроцессора языка С assert()

using namespace std;
class StringLegacy {
private: 
    char* str_;     // массив
    size_t length_; // Длина строки

    // Функция построения таблицы префиксов
    size_t* build_prefix_table(const StringLegacy& pattern) const
    {
       size_t* prefix_table = new size_t[pattern.length_];
       // Инициализация первого элемента таблицы
       prefix_table[0] = 0;
       // Инициализация индексов
       size_t i = 1;
       size_t j = 0;
       // Построение таблицы префиксов
       while (i < pattern.length_) {
          if (pattern.str_[i] == pattern.str_[j]) {
             prefix_table[i] = j + 1;
             i++; j++; }
          else {
             if (j > 0) { j = prefix_table[j - 1]; }
             else { prefix_table[i] = 0; i++; }
          }
       }
       return prefix_table; }

public:
    StringLegacy() : str_(_strdup("")), length_(0) {} 
    // Функция strdup() путем обращения к функции malloc() выделяет память, достаточную для хранения дубликата строки,
    // на которую указывает str, а затем производит копирование этой строки в выделенную область и возвращает указатель на нее. 
    
    // Конструктор по умолчанию
    StringLegacy(const char* str) : str_(_strdup(str)), length_(strlen(str)) {}
    // Конструктор по умолчанию
    StringLegacy(size_t length) : str_(_strdup("")), length_(length) {}
    //Конструктор со string
    StringLegacy(const string& str) : str_(_strdup(str.c_str())), length_(str.length()) {}

    // Конструктор копирования
    StringLegacy(const StringLegacy& other) : str_(_strdup(other.str_)), length_(other.length_) {}

    // Конструктор перемещения
    StringLegacy(StringLegacy&& other) noexcept : str_(other.str_), length_(other.length_) {
        other.str_ = nullptr;
        other.length_ = 0; }

    // Деструктор
    ~StringLegacy() { delete[] str_; }

    // Оператор присваивания копированием
    StringLegacy& operator=(const StringLegacy& other) {
        if (this != &other) {
            delete[] str_;
            str_ = _strdup(other.str_);
            length_ = other.length_; }
        return *this; }

    StringLegacy& operator=(const string& str) {
        delete[] str_;
        str_ = _strdup(str.c_str());
        length_ = str.length();
        return *this; }

    // Оператор присваивания перемещением
    StringLegacy& operator=(StringLegacy&& other) noexcept {
        if (this != &other) {
            delete[] str_;
            str_ = other.str_;
            length_ = other.length_;
            other.str_ = nullptr;
            other.length_ = 0; }
        return *this; }

    // Доступ к элементам строки по индексу
    char& operator[](size_t index) {
        if (index >= length_) {
            throw out_of_range("Индекс вне диапазона"); }
        return str_[index]; }

    // Доступ к длине строки
    size_t length() const { return length_; }

    // Проверка на пустоту строки
    bool empty() const { return length_ == 0; }

    // Очистка строки
    void clear() {
        free(str_);
        str_ = nullptr;
        length_ = 0; }

    // Сравнения реализованы на сравнении каждого символа,
    // то есть, в алфавитном порядке, не по длине
    
 // 1. Сравнение с StringLegacy " > "
    bool operator>(const StringLegacy& s) const {
        size_t i = 0;
        while (i < length_ && i < s.length_) {
            if (str_[i] > s.str_[i]) { return true; }
            else if (str_[i] < s.str_[i]) { return false; }
            i++; }
        return length_ > s.length_; }

    //Сравнение с char*
    bool operator>(char* s) const {
        size_t i = 0;
        while (i < length_ && s[i] != '\0') {
            if (str_[i] > s[i]) { return true; }
            else if (str_[i] < s[i]) { return false; }
            i++; }
        return length_ > strlen(s); }

    //Сравнение с char*
    bool operator>(const char* s) const {
        size_t i = 0;
        while (i < length_ && s[i] != '\0') {
            if (str_[i] > s[i]) { return true; }
            else if (str_[i] < s[i]) { return false; }
            i++; }
        return length_ > strlen(s); }

    //Friend-функция для сравнения с char* и StringLegacy
    friend bool operator>(char* str, const StringLegacy& s) {
        size_t i = 0;
        while (str[i] != '\0' && i < s.length_) {
            if (str[i] > s.str_[i]) { return true; }
            else if (str[i] < s.str_[i]) { return false; }
            i++;  }
        return strlen(str) > s.length_; }

    //Friend-функция для сравнения с string и StringLegacy
    friend bool operator>(const string& str, const StringLegacy& s) {
        size_t i = 0;
        while (i < str.length() && i < s.length_) {
            if (str[i] > s.str_[i]) { return true; }
            else if (str[i] < s.str_[i]) { return false; }
            i++; }
        return str.length() > s.length_; }

    //Сравнение с string
    bool operator>(const string& s) const {
        size_t i = 0;
        while (i < length_ && i < s.length()) {
            if (str_[i] > s[i]) { return true; }
            else if (str_[i] < s[i]) { return false; }
            i++; }
        return length_ > s.length(); }
    
 // 2. Сравнение с StringLegacy " < "
    bool operator<(const StringLegacy& s) const {
        size_t i = 0;
        while (i < length_ && i < s.length_) {
            if (str_[i] < s.str_[i]) { return true; }
            else if (str_[i] > s.str_[i]) { return false; }
            i++; }
        return length_ < s.length_; }

    //Сравнение с char*
    bool operator<(char* s) const {
        size_t i = 0;
        while (i < length_ && s[i] != '\0') {
            if (str_[i] < s[i]) { return true; }
            else if (str_[i] > s[i]) { return false; }
            i++; }
        return length_ < strlen(s); }

    bool operator<(const char* s) const {
        size_t i = 0;
        while (i < length_ && s[i] != '\0') {
            if (str_[i] < s[i]) { return true; }
            else if (str_[i] > s[i]) { return false; }
            i++; }
        return length_ < strlen(s); }

    //Friend-функция для сравнения с char* и StringLegacy
    friend bool operator<(char* str, const StringLegacy& s) {
        size_t i = 0;
        while (str[i] != '\0' && i < s.length_) {
            if (str[i] < s.str_[i]) { return true; }
            else if (str[i] > s.str_[i]) { return false; }
            i++; }
        return strlen(str) < s.length_; }

    //Friend-функция для сравнения с string и StringLegacy
    friend bool operator<(const std::string& str, const StringLegacy& s) {
        size_t i = 0;
        while (i < str.length() && i < s.length_) {
            if (str[i] < s.str_[i]) { return true; }
            else if (str[i] > s.str_[i]) { return false; }
            i++; }
        return str.length() < s.length_; }

    //Сравнение с string
    bool operator<(const std::string& s) const {
        size_t i = 0;
        while (i < length_ && i < s.length()) {
            if (str_[i] < s[i]) { return true; }
            else if (str_[i] > s[i]) { return false; }
            i++; }
        return length_ < s.length(); }
   
 // 3. Сравнение с StringLegacy " == "
    bool operator==(const StringLegacy& s) const {
        if (length_ != s.length_) { return false; }
        for (size_t i = 0; i < length_; i++) {
            if (str_[i] != s.str_[i]) { return false; }
        }
        return true; }

    //Сравнение с char*
    bool operator==(char* s) const {
        size_t i = 0;
        while (str_[i] != '\0' && s[i] != '\0') {
            if (str_[i] != s[i]) { return false; }
            i++; }
        return str_[i] == '\0' && s[i] == '\0'; }

    //Сравнение с char*
    bool operator==(const char* s) const {
        size_t i = 0;
        while (str_[i] != '\0' && s[i] != '\0') {
            if (str_[i] != s[i]) { return false; }
            i++; }
        return str_[i] == '\0' && s[i] == '\0'; }

    //Friend-функция для сравнения с char* и StringLegacy
    friend bool operator==(char* str, const StringLegacy& s) {
        size_t i = 0;
        while (str[i] != '\0' && s.str_[i] != '\0') {
            if (str[i] != s.str_[i]) { return false; }
            i++; }
        return str[i] == '\0' && s.str_[i] == '\0'; }

    //Friend-функция для сравнения с string и StringLegacy
    friend bool operator==(const std::string& str, const StringLegacy& s) {
        if (str.length() != s.length_) { return false; }
        for (size_t i = 0; i < str.length(); i++) {
            if (str[i] != s.str_[i]) { return false; }
        }
        return true; }

    //Сравнение с string
    bool operator==(const std::string& s) const {
        if (length_ != s.length()) { return false; }
        for (size_t i = 0; i < length_; i++) {
            if (str_[i] != s[i]) { return false; }
        }
        return true; }

// 4. Сравнение с StringLegacy " != "
    bool operator!=(const StringLegacy& s) const {
        if (length_ != s.length_) { return true; }
        for (size_t i = 0; i < length_; i++) {
            if (str_[i] != s.str_[i]) { return true; }
        }
        return false; }

    //Сравнение с char*
    bool operator!=(char* s) const {
        size_t i = 0;
        while (str_[i] != '\0' && s[i] != '\0') {
            if (str_[i] != s[i]) { return true; }
            i++; }
        return !(str_[i] == '\0' && s[i] == '\0'); }

    //Сравнение с char*
    bool operator!=(const char* s) const {
        size_t i = 0;
        while (str_[i] != '\0' && s[i] != '\0') {
            if (str_[i] != s[i]) { return true; }
            i++; }
        return !(str_[i] == '\0' && s[i] == '\0'); }

    //Friend-функция для сравнения с char* и StringLegacy
    friend bool operator!=(char* str, const StringLegacy& s) {
        size_t i = 0;
        while (str[i] != '\0' && s.str_[i] != '\0') {
            if (str[i] != s.str_[i]) { return true; }
            i++; }
        return !(str[i] == '\0' && s.str_[i] == '\0'); }

    //Friend-функция для сравнения с string и StringLegacy
    friend bool operator!=(const std::string& str, const StringLegacy& s) {
        if (str.length() != s.length_) { return true; }
        for (size_t i = 0; i < str.length(); i++) {
            if (str[i] != s.str_[i]) { return true; }
        }
        return false; }

    //Сравнение с string
    bool operator!=(const std::string& s) const {
        if (length_ != s.length()) { return true; }
        for (size_t i = 0; i < length_; i++) {
            if (str_[i] != s[i]) { return true; }
        }
        return false; }

// 5. Сравнение с StringLegacy " <= "
    bool operator<=(const StringLegacy& s) const {
        size_t i = 0;
        while (i < length_ && i < s.length_) {
            if (str_[i] < s.str_[i]) { return true; }
            else if (str_[i] > s.str_[i]) { return false; }
            i++; }
        return length_ <= s.length_; }

    //Сравнение с char*
    bool operator<=(char* s) const {
        size_t i = 0;
        while (i < length_ && s[i] != '\0') {
            if (str_[i] < s[i]) { return true; }
            else if (str_[i] > s[i]) { return false; }
            i++; }
        return length_ <= strlen(s); }

    //Сравнение с char*
    bool operator<=(const char* s) const {
        size_t i = 0;
        while (i < length_ && s[i] != '\0') {
            if (str_[i] < s[i]) { return true; }
            else if (str_[i] > s[i]) { return false; }
            i++; }
        return length_ <= strlen(s); }

    //Friend-функция для сравнения с char* и StringLegacy
    friend bool operator<=(char* str, const StringLegacy& s) {
        size_t i = 0;
        while (str[i] != '\0' && i < s.length_) {
            if (str[i] < s.str_[i]) { return true; }
            else if (str[i] > s.str_[i]) { return false; }
            i++; }
        return strlen(str) <= s.length_; }

    //Friend-функция для сравнения с string и StringLegacy
    friend bool operator<=(const std::string& str, const StringLegacy& s) {
        size_t i = 0;
        while (i < str.length() && i < s.length_) {
            if (str[i] < s.str_[i]) { return true; }
            else if (str[i] > s.str_[i]) { return false; }
            i++; }
        return str.length() <= s.length_; }

    //Сравнение с string
    bool operator<=(const std::string& s) const {
        size_t i = 0;
        while (i < length_ && i < s.length()) {
            if (str_[i] < s[i]) { return true; }
            else if (str_[i] > s[i]) { return false; }
            i++; }
        return length_ <= s.length(); }

 // 6. Сравнение с StringLegacy " >= "
    bool operator>=(const StringLegacy& s) const {
        size_t i = 0;
        while (i < length_ && i < s.length_) {
            if (str_[i] > s.str_[i]) { return true; }
            else if (str_[i] < s.str_[i]) { return false; }
            i++; }
        return length_ >= s.length_; }

    //Сравнение с char*
    bool operator>=(char* s) const {
        size_t i = 0;
        while (i < length_ && s[i] != '\0') {
            if (str_[i] > s[i]) { return true; }
            else if (str_[i] < s[i]) { return false; }
            i++; }
        return length_ >= strlen(s); }

    //Сравнение с char*
    bool operator>=(const char* s) const {
        size_t i = 0;
        while (i < length_ && s[i] != '\0') {
            if (str_[i] > s[i]) { return true; }
            else if (str_[i] < s[i]) { return false; }
            i++; }
        return length_ >= strlen(s); }

    //Friend-функция для сравнения с char* и StringLegacy
    friend bool operator>=(char* str, const StringLegacy& s) {
        size_t i = 0;
        while (str[i] != '\0' && i < s.length_) {
            if (str[i] > s.str_[i]) { return true; }
            else if (str[i] < s.str_[i]) { return false; }
            i++; }
        return strlen(str) >= s.length_; }

    //Friend-функция для сравнения с string и StringLegacy
    friend bool operator>=(const std::string& str, const StringLegacy& s) {
        size_t i = 0;
        while (i < str.length() && i < s.length_) {
            if (str[i] > s.str_[i]) { return true; }
            else if (str[i] < s.str_[i]) { return false; }
            i++; }
        return str.length() >= s.length_; }

    //Сравнение с string
    bool operator>=(const std::string& s) const {
        size_t i = 0;
        while (i < length_ && i < s.length()) {
            if (str_[i] > s[i]) { return true; }
            else if (str_[i] < s[i]) { return false; }
            i++; }
        return length_ >= s.length(); }

 // 7. Конкатенация с StringLegacy " + "
    StringLegacy operator+(const StringLegacy& s) const {
        StringLegacy result;
        result.length_ = length_ + s.length_;
        result.str_ = new char[result.length_ + 1];
        copy_n(str_, length_, result.str_);
        copy_n(s.str_, s.length_, result.str_ + length_);
        result.str_[result.length_] = '\0';
        return result;
    }

    //Конкатенация с char*
    StringLegacy operator+(char* s) const {
        StringLegacy result;
        result.length_ = length_ + strlen(s);
        result.str_ = new char[result.length_ + 1];
        copy_n(str_, length_, result.str_);
        copy_n(s, strlen(s), result.str_ + length_);
        result.str_[result.length_] = '\0';
        return result;
    }

    //Friend-функция конкатенации char* и  StringLegacy
    friend StringLegacy operator+(char* str, const StringLegacy& s) {
        StringLegacy result;
        result.length_ = strlen(str) + s.length_;
        result.str_ = new char[result.length_ + 1];
        copy_n(str, strlen(str), result.str_);
        copy_n(s.str_, s.length_, result.str_ + strlen(str));
        result.str_[result.length_] = '\0';
        return result;
    }

    //Friend-функция конкатенации string и  StringLegacy
    friend StringLegacy operator+(const std::string& str, const StringLegacy& s) {
        StringLegacy result;
        result.length_ = str.length() + s.length_;
        result.str_ = new char[result.length_ + 1];
        copy_n(str.c_str(), str.length(), result.str_);
        copy_n(s.str_, s.length_, result.str_ + str.length());
        result.str_[result.length_] = '\0';
        return result;
    }

    //Конкатенация с string
    StringLegacy operator+(const std::string& s) const {
        StringLegacy result;
        result.length_ = length_ + s.length();
        result.str_ = new char[result.length_ + 1];
        copy_n(str_, length_, result.str_);
        copy_n(s.c_str(), s.length(), result.str_ + length_);
        result.str_[result.length_] = '\0';
        return result;
    }
    
 // 8. Функции поиска, вставки, удаления, преобразования
    // Функция поиска последнего вхождения символа.
    // Возвращает длину строки +1, если не найден символ
    size_t seek_last(char ch) const {
        for (size_t i = length_ - 1; i >= 1; i--) {
            if (str_[i] == ch) { return i; }
        }
        return length_ + 1; }

    // Функция вставки строки в позицию
    void insert(size_t pos, const char* str) {
        size_t str_len = strlen(str);
        size_t new_length = length_ + str_len;

        char* new_str = new char[new_length + 1];
        copy_n(str_, pos, new_str);
        copy_n(str, str_len, new_str + pos);
        copy_n(str_ + pos, length_ - pos, new_str + pos + str_len);
        new_str[new_length] = '\0';

        delete[] str_;
        str_ = new_str;
        length_ = new_length; }

    // Функция вставки строки в позицию (StringLegacy)
    void insert(size_t pos, const StringLegacy& str) {
        insert(pos, str.str_); }

    // Функция вставки строки в позицию (std::string)
    void insert(size_t pos, const std::string& str) {
        insert(pos, str.c_str()); }

    // Функция удаления count символов по индексу
    void erase(size_t index, size_t count) {
        if (index >= length_ || count == 0) { return; }

        size_t new_length = length_ - count;
        char* new_str = new char[new_length + 1];

        copy_n(str_, index, new_str);
        copy_n(str_ + index + count, new_length - index, new_str + index);
        new_str[new_length] = '\0';

        delete[] str_;
        str_ = new_str;
        length_ = new_length; }

    // Оператор преобразования в char*
    operator char* () const { return str_; }
  
    // Оператор преобразования в std::string
    operator std::string() const { return std::string(str_); }

    // Алгоритм поиска подстроки КМП. Если не найдет, возвращает длину + 1
    size_t kmp_search(const StringLegacy& pattern) const {
        // Создание таблицы префиксов
        size_t* prefix_table = build_prefix_table(pattern);
        // Инициализация индексов
        size_t i = 0; // Индекс текста
        size_t j = 0; // Индекс образца
        // Поиск образца в тексте
        while (i < length_ && j < pattern.length_) {
            if (str_[i] == pattern.str_[j]) { i++; j++; }
            else {
                // Если символы не совпадают, сдвигаем индекс образца
                // на основе таблицы префиксов
                if (j > 0) { j = prefix_table[j - 1]; }
                else { i++; }
            }
        }
        // Освобождение памяти
        delete[] prefix_table;
        // Возврат индекса начала образца, если он найден
        if (j == pattern.length_) { return i - j; }
        else { return length_ + 1; }
    }

    // Последовательный поиск подстроки с проверкой первого и последнего элемента. Если не найдет, возвращает длину + 1
    size_t search(const StringLegacy& pattern) const {
        size_t text_len = length_;
        size_t pattern_len = pattern.length_;
        // Итерация по тексту
        for (size_t i = 0; i <= text_len - pattern_len; i++) {
            // Проверка первого элемента
            if (str_[i] != pattern.str_[0]) { continue; }
            // Проверка последнего элемента
            if (str_[i + pattern_len - 1] != pattern.str_[pattern_len - 1]) { continue; }
            // Полная проверка образца
            size_t j = 0;
            while (j < pattern_len && str_[i + j] == pattern.str_[j]) { j++; }
            // Проверка, найден ли образец
            if (j == pattern_len) { return i; }
        }
        // Образец не найден
        return length_ + 1; }

    // Процедура, которая генерирует строку случайных символов заданной последовательности
    static StringLegacy generate_random_string(size_t length, const std::string& charset) {
        StringLegacy random_string(length);
        for (size_t i = 0; i < length; i++) {
            random_string.str_[i] = charset[rand() % charset.length()];
        }
        return random_string; }

    // Процедура, которая читает строки из текстового файла
    static vector<StringLegacy> read_lines_from_file(const string& filename) {
        ifstream file(filename);
        vector<StringLegacy> lines;
        if (file.is_open()) { string line;
           while (getline(file, line)) {
             lines.push_back(StringLegacy(line));
           }
           file.close();
        }
        else { cerr << "Error opening file: " << filename << endl; }
        return lines; }
};

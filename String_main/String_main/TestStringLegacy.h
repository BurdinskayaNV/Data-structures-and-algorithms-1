/// \file TestStringLegacy.h
/// \brief Работа с тестом класса строк
/// \author Бурдинская Наталья ВМК-22
/// \date 10.05.2024

#include <cassert>    // Для применения макроса assert()
#include <assert.h>   // объявляется макрос препроцессора языка С assert()
#include "StringLegacy.h" // строковое наследие Legacy


static void test() {
    StringLegacy emptyString; // пустой
    assert(emptyString.length() == 0);
    assert(emptyString == "");

    StringLegacy str(10);
    assert(str.length() == 10);
    assert(str == "");

    StringLegacy str1("Hello, Natasha!");
    assert(str1.length() == 15);
    assert(str1 == "Hello, Natasha!");

    std::string stdStr = "Hello, Natasha!";
    StringLegacy str2(stdStr);
    assert(str2.length() == 15);
    assert(str2 == "Hello, Natasha!");

    StringLegacy str3(str1);
    assert(str3.length() == str1.length());
    assert(str1 == str3);
    str3 = "Goodbye, Natasha!";
    assert(str3 != str1);

    StringLegacy str4(std::move(str1));
    assert(str4.length() == 15);
    assert(str4 == "Hello, Natasha!");
    assert(str1.length() == 0);
   
    StringLegacy* str5 = new StringLegacy("Hello, Natasha!");
    delete str5;
   
    StringLegacy str6;
    str6 = "Hello, Natasha!";
    assert(str6.length() == 15);
    
    StringLegacy str7;
    stdStr = "Hello, Natasha!";
    str7 = stdStr;
    assert(str7.length() == 15);
    assert(strcmp(str7, "Hello, Natasha!") == 0);

    StringLegacy str8("Hello, Natasha!");
    StringLegacy str9;
    str9 = std::move(str8);
    assert(str9.length() == 15);
    assert(str8.length() == 0);
   
    StringLegacy str10("Hello, Natasha!");
    assert(str10[0] == 'H');
    assert(str10[6] == ' ');
    assert(str10[14] == '!');

    StringLegacy str11("Hello, Natasha!");
    assert(str11.length() == 15);

    StringLegacy emptyString2;
    assert(emptyString2.empty());
    StringLegacy str12("Hello, Natasha!");
    assert(!str12.empty());

    StringLegacy str13("Hello, Natasha!");
    str13.clear();
    assert(str13.length() == 0);
    
    StringLegacy str14("Hello, Natasha!");
    StringLegacy str15("Hello, Natasha!");
    StringLegacy str16("Hello, Natasha!1");
    assert(!(str14 > "Hello, Natasha!"));
    assert(!(str15 > "Hello, Natasha!1"));
    assert(str16 > "Hello, Natasha!");

    StringLegacy str17("Hello, Natasha!");
    StringLegacy str18("Hello, Natasha!");
    StringLegacy str19("Hello, Natasha!1");
    assert(!(str17 < "Hello, Natasha!"));
    assert(str18 < "Hello, Natasha!1");
    assert(!(str19 < "Hello, Natasha!"));

    StringLegacy str20("Hello, Natasha!");
    StringLegacy str21("Hello, Natasha!");
    StringLegacy str22("Hello, Natasha!1");
    assert(str20 >= "Hello, Natasha!");
    assert(!(str21 >= "Hello, Natasha!1"));
    assert(str22 >= "Hello, Natasha!");

    StringLegacy str23("Hello, Natasha!");
    StringLegacy str24("Hello, Natasha!");
    StringLegacy str25("Hello, Natasha!1");
    assert(str23 <= "Hello, Natasha!");
    assert(str24 <= "Hello, Natasha!1");
    assert(!(str25 <= "Hello, Natasha!"));

    StringLegacy str26("Hello, Natasha!");
    assert(str26 == "Hello, Natasha!");
    assert(str26 != "Hello, Natasha!1");

    StringLegacy str27("Hello, Natasha!");
    stdStr = "Hello, Natasha!";
    assert(str27 == stdStr);
    stdStr = "Hello, Natasha!1";
    assert(str27 != stdStr);

    StringLegacy str28("Hello, Natasha!");
    StringLegacy str29("Hello, Natasha!");
    StringLegacy str30("Hello, Natasha!1");

    assert(str28 != str30);

    StringLegacy str31("Hello, Natasha!");
    stdStr = "Hello, Natasha!";
    assert(str31 == stdStr);
    stdStr = "Hello, Natasha!1";
    assert(str31 != stdStr);
    cout << "--- Тестирование выполнено успешно ---" << endl;
}
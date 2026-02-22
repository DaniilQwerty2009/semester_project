// Пространство алгоритмнов для School
#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <cstddef>


namespace SchoolAlg 
{
    // Алгоритм поиска в контейнере
    template<typename Iterator, typename Compare, typename Attribute>
        Iterator search(const Iterator& first_iterator,                 // Левая граница поиска. Включена в поиск
                        const Iterator& last_iterator,                  // Правая границв поиска. Не включена в поиск
                        Compare compare,                                // Компаратор: Students:: или Groups::
                        Attribute attribute)                            // Атрибут поиска
        {       
            Iterator iter = first_iterator;

            while(iter && first_iterator != last_iterator)
            {
                if( !compare(*iter, attribute) && !compare(attribute, *iter))
                    return iter;

                iter++;
            }

            return iter;
        }
  
    // Алгоритм для корректной обрезки кириллической строки нуль-терминатором.
    // Возвращаемое значение - корректное место для '\0'
    size_t safe_cyrillic_prefix(const char* str,                    // Строка
                                const size_t& maxBitesWithNull);    // Макстмальный размер корректной строки 
    

}

#endif
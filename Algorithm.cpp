#include "Algorithm.h"


    size_t SchoolAlg::safe_cyrillic_prefix(const char* str, const size_t& maxBitesWithNull)
    {
        if(!str || maxBitesWithNull == 0)
            return 0;

        size_t safeBites = 0;   // сколько байт-символов целиком поместились в границу
        short bites = 0;        // размер очередного символа

        // Пока очередной символ помещается в оставшееся место
        while((safeBites + bites) < maxBitesWithNull)
        {
            safeBites += bites;

            // Проверка маской первых четырех битов первого байта лчередного символа - это кол-во занимаемых символом байтов
            if((str[safeBites] & 0b10000000) == 0b00000000)
                    bites = 1;
            else if
                ((str[safeBites] & 0b11000000) == 0b11000000)
                    bites = 2;
            else if
                ((str[safeBites] & 0b11100000) == 0b11100000)
                    bites = 3;
            else if
                ((str[safeBites] & 0b11110000) == 0b11110000)
                    bites = 4;
        }

        return safeBites;
    }
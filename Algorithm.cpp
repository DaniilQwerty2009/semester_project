#include "Algorithm.h"


    size_t SchoolAlg::safeStrPrefix(const char* str, const size_t& maxBitesWithNull)
    {
        if(!str || maxBitesWithNull == 0)
            return 0;

        size_t safeBites = 0;
        short bites = 0;

        while((safeBites + bites) < maxBitesWithNull)
        {
            safeBites += bites;

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
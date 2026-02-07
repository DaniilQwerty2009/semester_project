#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <cstddef>


namespace SchoolAlg 
{
    template<typename Iterator, typename Compare, typename Attribute>
        bool search(Iterator& iterator, Compare compare, Attribute attribute)
        {
            while(iterator)
            {
                if( !compare(*iterator, attribute) && !compare(attribute, *iterator))
                    return iterator;

                iterator++;
            }

            return iterator;
        }



    size_t safeStrPrefix(const char* str, const size_t& maxBitesWithNull);
    

    
    // template<typename Iterator, typename Compare>
    //     bool search(Iterator& iterator, Compare compare, const char* attribute)
    // {
    //     while(iterator)
    //     {
    //         if( !compare(&(*iterator), attribute) && !compare(attribute, &(*iterator)))
    //             return iterator;

    //         iterator++;
    //     }

    //     return iterator;
    // }
}

#endif
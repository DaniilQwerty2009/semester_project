#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <cstddef>


namespace SchoolAlg 
{
    template<typename Iterator, typename Compare, typename Attribute>
        Iterator search(Iterator& first_iterator, Iterator& last_iterator, Compare compare, Attribute attribute)
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

    template<typename Iterator, typename Compare, typename Attribute>
        Iterator search(Iterator& first_iterator, Compare compare, Attribute attribute)
        {
            Iterator iter = first_iterator;

            while(iter)
            {
                if( !compare(*iter, attribute) && !compare(attribute, *iter))
                    return iter;

                iter++;
            }

            return iter;
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
#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <cstddef>


namespace SchoolAlg 
{
    template<typename Iterator, typename Compare, typename Attribute>
        Iterator search(const Iterator& first_iterator, const Iterator& last_iterator, Compare compare, Attribute attribute)
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
  

    size_t safe_cyrillic_prefix(const char* str, const size_t& maxBitesWithNull);
    

}

#endif
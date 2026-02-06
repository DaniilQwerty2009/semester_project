

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
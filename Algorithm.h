

namespace SchoolAlg
{
    template<typename Iterator, typename EqualBy>
        void search(Iterator& iterator, EqualBy compare, const unsigned& attribute)
    {
        while(*iterator != nullptr)
        {
            if(compare(iterator, attribute))
                return;

            iterator++;
        }

    }

    template<typename Iterator, typename EqualBy>
        void search(Iterator& iterator, EqualBy compare, const char* attribute)
    {
        while(*iterator != nullptr)
        {
            if(compare(iterator, attribute))
                return;

            iterator++;
        }

    }
}
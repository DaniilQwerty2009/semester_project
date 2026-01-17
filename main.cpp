#include <iostream>

#include "School.h"

using std::cout;
using std::endl;

int main()
{
    School* ourSchool = new School;

    
    ourSchool->push_back(1, "LastName111", 12);
    ourSchool->push_back(2, "LastName222", 13);
    ourSchool->push_back(2, "LastName333", 13);
    
    

    School::iterator iterator;
    School::iterator iterator2(ourSchool->begin());
    
    iterator = ourSchool->begin();

    std::cout << *iterator << std::endl;

    while(iterator != ourSchool->end())
    {
        std::cout << iterator.getLastname() << std::endl;
        ++iterator;
    }
    iterator2 = iterator++;

    

    return 0;
}
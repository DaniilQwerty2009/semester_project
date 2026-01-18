#include <iostream>

#include "School.h"

using std::cout;
using std::endl;

int main()
{
    School* ourSchool = new School;

    
    ourSchool->push_back(1, "Петров", 0);
    ourSchool->push_back(2, "Иванов", 1);
    ourSchool->push_back(3, "Сидоров", 1);
    
    

    School::iterator iterator;
    
    iterator = ourSchool->begin();

    std::cout << *iterator << std::endl;

    while(iterator != ourSchool->end())
    {
        iterator.printInfo();
        ++iterator;
    }



    std::cout << "=================================" << std::endl;

    ourSchool->pop(2);

    iterator = ourSchool->begin();

    while(iterator != ourSchool->end())
    {
        std::cout << iterator.getLastname() << std::endl;
        ++iterator;
    }

    std::cout << "=================================" << std::endl;

    iterator = ourSchool->begin();

    ourSchool->addVisit(iterator, 11);
    ourSchool->addVisit(iterator, 12);
    ourSchool->addVisit(3, 13);

    while(iterator != ourSchool->end())
    {
        std::cout << iterator.getLastname() << std::endl;
        ++iterator;
    }

    std::cout << "=================================" << std::endl;

    iterator = ourSchool->begin();
    const unsigned* days1 =  iterator.getDates();
    ++iterator;
    const unsigned* days2 = iterator.getDates();

    
    iterator = ourSchool->begin();
    for(int i = 0; i < iterator.getVisits(); ++i)
        std::cout << days1[i] << std::endl;

    std::cout << days2[0] << std::endl;

    
    
    
    return 0;
}
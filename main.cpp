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
    ourSchool->push_back(4, "Васечкин", 2);

    for(School::iterator iter = ourSchool->begin(); iter != ourSchool->end(); ++iter)
        ourSchool->addVisit(iter, 1);
    
    ourSchool->addGroupVisit(1, 2);
    ourSchool->addGroupVisit(1, 3);
    ourSchool->addGroupVisit(2, 2);
    
    School::iterator iterator = ourSchool->begin();
    size_t visits;
    const unsigned* dates;


    School::ByLastname comparator;
    ourSchool->sort(comparator);

    while(iterator != ourSchool->end())
    {
        iterator.printInfo();


        visits = iterator.getVisits();
        dates = iterator.getDates();
        for(size_t i = 0; i < visits; ++i)
            std::cout << dates[i] << ((i < visits -1 )? "; ": "\n");

        if(iterator != ourSchool->end())
        std::cout << "------------------" << std::endl;



        iterator++;
    }
    
    
    
    

    std::cout << "=================================" << std::endl;

    

    
    
    
    return 0;
}
#include <iostream>

#include "School.h"

using std::cout;
using std::endl;

int main()
{
    School* ourSchool = new School;

    
    ourSchool->push_back(1, "Иетров", 0);
    ourSchool->push_back(2, "Аванов", 1);
    ourSchool->push_back(3, "Гуськов", 3);
    ourSchool->push_back(4, "Абдоров", 1);
    ourSchool->push_back(5, "Васечкин", 2);
    ourSchool->push_back(6, "Бечорин", 5);

    for(int i = 1; i < 6; ++i)
    {  
        ourSchool->addVisit(i, 1);
    }

    ourSchool->addGroupVisit(1, 4);
    ourSchool->addGroupVisit(1, 2);
    ourSchool->addGroupVisit(2, 3);

    
    
    School::iterator iterator = ourSchool->begin();

    // добавим Петрову посещений
    for(int i = 0; i < 10; ++i)
        ourSchool->addVisit(1, 99);

    for(int i = 0; i < 5; ++i)
        ourSchool->addVisit(4, 99);

    size_t visits;
    const unsigned* dates;
    iterator = ourSchool->begin();    

    while(iterator != ourSchool->end())
    {
        dates = (*iterator).dates.datesArray;
        visits = (*iterator).dates.elementsQty;

        ourSchool->printStudentInfo((*iterator).ID);
        cout << endl;
        
        for(size_t i = 0; i < visits; ++i)
            std::cout << dates[i] << ((i < visits -1 )? "; ": "\n");

        if(iterator != ourSchool->end())
        std::cout << "------------------" << std::endl;

        iterator++;
    }
    

    std::cout << "=================================" << std::endl;

    School::ByLastname comparator;
    ourSchool->sort(comparator);

    iterator = ourSchool->begin();
    while(iterator != ourSchool->end())
    {
        dates = (*iterator).dates.datesArray;
        visits = (*iterator).dates.elementsQty;
        
        ourSchool->printStudentInfo((*iterator).ID);
        cout << endl;

        for(size_t i = 0; i < visits; ++i)
            std::cout << dates[i] << ((i < visits -1 )? "; ": "\n");

        if(iterator != ourSchool->end())
        std::cout << "------------------" << std::endl;

        iterator++;
    }
    

    
    
    
    return 0;
}
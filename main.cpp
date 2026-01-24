#include <iostream>

#include "School.h"

using std::cout;
using std::endl;

int main()
{
    School* ourSchool = new School;

    School::iterator iter = ourSchool->begin();
    
    ourSchool->push_back(1, "Иванов", 0);
    ourSchool->push_back(2, "Петров", 1);
    

    ourSchool->addVisit(1,1);
    ourSchool->addVisit(1,2);
    ourSchool->addVisit(1,3);

    ourSchool->addVisit(2,1);
    ourSchool->addVisit(2,2);
    ourSchool->addVisit(2,3);

    ourSchool->writeToBin("Test.txt");
    
    return 0;
}
#include <iostream>

#include "School.h"
#include "IDGenerator.h"

using std::cout;
using std::endl;

int main()
{
    School* ourSchool = new School;

    School::iterator iter = ourSchool->begin();
    IDGenerator generatorID;
    


    ourSchool->push_back(2, "Петров", 9);
    

    ourSchool->addVisit(2,1);
    ourSchool->addVisit(2,2);
    ourSchool->addVisit(2,3);

    cout << sizeof((*iter).ID) << endl;
    cout << strlen("Ivanov") + 1 << endl;
    cout << sizeof((*iter).groupID) << endl;
    cout << sizeof((*iter).visits) << endl;
    cout << sizeof((*iter).dates.elementsQty) << endl;

    ourSchool->writeToBin("Test.txt");
    ourSchool->readFromBIn("Test.txt", generatorID);
    
    return 0;
}
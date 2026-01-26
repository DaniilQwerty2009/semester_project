#include <iostream>

#include "School.h"
#include "IDGenerator.h"

using std::cout;
using std::endl;

int main()
{
    School* ourSchool = new School;

    
    IDGenerator generatorID;
    


    ourSchool->push_back(2, "Иванов", 11);
    

    ourSchool->addVisit(2,1);
    ourSchool->addVisit(2,2);
    ourSchool->addVisit(2,3);

    

    ourSchool->writeToBin("Test.txt");
    ourSchool->readFromBIn("Test.txt", generatorID);

    School::iterator iter = ourSchool->begin();
    ++iter;
    
    cout << (*iter).ID << endl;
    cout << (*iter).lastname << endl;
    cout << (*iter).groupID<< endl;
    cout << (*iter).visits << endl;
    cout << (*iter).dates.elementsQty << endl;

    return 0;
}
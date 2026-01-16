#include <iostream>

#include "School.h"

using std::cout;
using std::endl;

int main()
{
    School ourSchool;

    Student testPerson(1, "LastName111", 12);
    
    ourSchool.addStudent(1, "LastName111", 12);
    ourSchool.addStudent(2, "LastName222", 13);
    
    ourSchool.printList();

    School::iterator iterator;
    
    iterator = ourSchool.begin();
    
    std::cout << iterator.getLastname() << std::endl;

    return 0;
}
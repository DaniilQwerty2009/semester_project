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
    ourSchool->push_back(3, "Гуськов", 1);
    ourSchool->push_back(4, "Задорнов", 2);
    ourSchool->push_back(5, "Васечкин", 2);
    ourSchool->push_back(6, "Печорин", 5);

    School::ByLastname comporator;
    ourSchool->sort(comporator);
    ourSchool->push_sorted(comporator, 7, "Абасов", 2);


    ourSchool->addVisit(1, 1);
    ourSchool->addVisit(1, 2);
    ourSchool->addVisit(1, 3);


    ourSchool->addVisit(1, 32);
    ourSchool->addVisit(1, 33);

    ourSchool->addVisit(1, 34);

    ourSchool->addVisit(2, 32);
    ourSchool->addVisit(2, 33);
    ourSchool->addVisit(2, 34);


    ourSchool->addGroupVisit(1, 10);
    ourSchool->addGroupVisit(1, 100);
    ourSchool->addGroupVisit(1, 300);

    ourSchool->addGroupVisit(2, 20);
    ourSchool->addGroupVisit(2, 120);
    ourSchool->addGroupVisit(2, 320);

    cout << "'1/01'" << endl;
    ourSchool->printVisitsInDate(1, 1);
    cout << "'2/01'" << endl;
    ourSchool->printVisitsInDate(2, 1);
    cout << "'3/01'" << endl;
    ourSchool->printVisitsInDate(3, 1);

    std::cout << "======================================" << std::endl;

    cout << "'32'" << endl;
    ourSchool->printVisitsInDate(32);
    cout << "'33'" << endl;
    ourSchool->printVisitsInDate(33);
    cout << "'34'" << endl;
    ourSchool->printVisitsInDate(34);

    std::cout << "======================================" << std::endl;

    cout << "'10'" << endl;
    ourSchool->printVisitsInDate(10);
    cout << "'100'" << endl;
    ourSchool->printVisitsInDate(100);
    cout << "'300'" << endl;
    ourSchool->printVisitsInDate(300);
    

    std::cout << "======================================" << std::endl;
    
    cout << "'20'" << endl;
    ourSchool->printVisitsInDate(20);
    cout << "'120'" << endl;
    ourSchool->printVisitsInDate(120);
    cout << "'320'" << endl;
    ourSchool->printVisitsInDate(320);


    
    
    return 0;
}
#ifndef MENU_H
#define MENU_H

#include <iostream>

#include "School.h"
#include "Algorithm.h"


using std::cout;
using std::endl;
using std::cin;

class menu
{
private:
    School* school;

    DateConverter       dateConventer;
public:
    menu(): school()
        {   }

    // Главное окно
    void init(School* school);

    // вкладки
    void inStudents();

    Students::iterator StudentsSearch(const Students::iterator& first, const Students::iterator& last);
    void StudentsEdit(Students::iterator& sIter);
    void StudentsEditLastname(Students::iterator& sIter);
    bool StudentsEditGroup(Students::iterator& sIter);
    void inStudentsList();
    unsigned StudentsAdd();
    unsigned SudentAddSorted();
    void StudentsExclude(Students::iterator& sIter);
    // единое форматирование - ширина полей, выравнивание, заполнитель, разделитель...
    void StudentFormatPrint(Students::iterator& sIter) const;

// ======================================================================= //

void     inGroup();

unsigned createGroup();
bool     deleteGroup();

void     GroupFormatPrint() const;

// ======================================================================= //

    void inVisits();

    unsigned inputVisitDay();
    void InPersonalVisitAdd();
    bool GroupVisitAdd();

    void VisitsFormatShow(const unsigned& day) const;





    


};



#endif
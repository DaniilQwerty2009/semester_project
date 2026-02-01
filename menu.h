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
    // unsigned inputValue;

    School* school;

    School::ByStudentID IDCompare;
    School::ByLastname  lastnameCompare;
    School::ByVisits    visitsCompare;
    DateConverter       dateConventer;
public:
    menu(): school()
        {   }

    // Главное окно
    void init(School* school);

    // вкладки
    void inStudents();

    bool StudentsSearch(School::iterator& iter);
    void StudentsEdit(School::iterator& iter);
    void StudentsEditLastname(School::iterator& iter);
    void StudentsEditGroup(School::iterator& iter);
    void inStudentsList();
    void StudentsAdd();
    void StudentsExclude(School::iterator& iter);
    // единое форматирование - ширина полей, выравнивание, заполнитель, разделитель...
    void StudentsFormatShow() const;

// ======================================================================= //

    void inVisits();

    bool VisitsInputDate(unsigned& day, unsigned& mounth);
    void InPersonalVisitAdd();
    void VisitsFormatShow(const unsigned& day) const;





    void GroupFormatShow();


};



#endif
#ifndef MENU_H
#define MENU_H

#include "iostream"

#include "School.h"

using std::cout;
using std::endl;

class menu
{
private:
    unsigned inputValue;

    School school;
public:
    menu(): school()
        {   }

    // Главное окно
    void init();

    // вкладки
    void inStudents();

    void StudentsEdit();
    void StudentsEditLastname();

    void StudentsAdd();
    
    // единое форматирование - ширина полей, выравнивание, заполнитель, разделитель...
    void StudentsFormatShow();

};




#endif
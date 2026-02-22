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

    // Вкладка Студенты: список, поиск, добавление, исключение
    void in_Students();

    // Поиск студента: ввод внутри функции, параметры - диапазон поиска [first; last)
    Students::iterator  Student_search(const Students::iterator& first, const Students::iterator& last);

    // Редактирование студента: фамилия, группа
    void                Student_edit(Students::iterator& sIter);

    // Редактирование фамилии
    void                Student_edit_lastname(Students::iterator& sIter);

    // Редактирование группы
    bool                Student_edit_group(Students::iterator& sIter);

    // Вкладка список студентов: вывод списка, сортировка
    void                in_Students_list();

    // Добавление студента
    unsigned            Student_add();

    // Добавление с сохранением порядка
    unsigned            Student_add_sorted();

    // Исключение студента
    void                Students_exclude(Students::iterator& sIter);

    // Вывод инофрмации о студенете в терминал
    void                Student_format_print(Students::iterator& sIter) const;

// ======================================================================= //
    // Вкладка Группы: список, создание, удаление
    void     in_Groups();

    // Сохдать группу
    unsigned create_Group();

    // Удалить группу
    void     delete_Group();

    // Вывод инормации о группе в терминал
    void     Group_format_print() const;

// ======================================================================= //
    // Вкладка посещения: отметить студента, отметить группу, посещения по дате
    void in_Visits();

    // Ввод число:месяц внутри функции, возврат дня с начала года или 0 при отмене
    unsigned input_visit_day();

    // Вкладка отметки студентов: список студентов, отметить студента
    void in_personal_visit_add();

    // Отметить группу
    bool group_visit_add();

    // Вывод номеров и фамилий студентов, посещавших занятия в day
    void Visits_format_print(const unsigned& day) const;
};



#endif
#ifndef SCHOOL_EXEPTIONS_H
#define SCHOOL_EXEPTIONS_H

#include <iostream>
#include <stdexcept>



class SchoolExeptions : public std::exception
{
protected:
    const char* msg;
public:
    SchoolExeptions(const char* msg): msg(msg)
        {   }
    SchoolExeptions(SchoolExeptions& other): msg(other.msg)
        {   }

    virtual const char* what()
    {
        return msg;
    }
};


class AlreadyExist : public SchoolExeptions
{
public:
    AlreadyExist() : SchoolExeptions("Такой объект уже существует")
        {   }
};

class NotEmpty : public SchoolExeptions
{
public:
    NotEmpty() : SchoolExeptions("Не пустая структура данных")
        {   }
};

class EmptyStr : public SchoolExeptions
{
public:
    EmptyStr() : SchoolExeptions("Передача нулевого указателя на строку")
        {   }
};

class WrongDate : public SchoolExeptions
{
public:
    WrongDate() : SchoolExeptions("Неверный формат или диапазон даты")
        {   }
};

#endif
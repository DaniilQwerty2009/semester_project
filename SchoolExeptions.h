#ifndef SCHOOL_EXEPTIONS_H
#define SCHOOL_EXEPTIONS_H

#include <iostream>
#include <stdexcept>



class SchoolExeptions : public std::exception
{
protected:
    const char* msg;
public:
    SchoolExeptions(char* msg): msg(msg)
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



#endif
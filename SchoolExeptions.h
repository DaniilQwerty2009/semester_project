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


// Groups =======================================================

class CantCreateGroup : public SchoolExeptions
{
protected:
    const char* msg;
public:
    CantCreateGroup(): SchoolExeptions("Не удалось создать группу.")
        {   }

    virtual const char* why() = 0;
};

class HasSameGroup : public CantCreateGroup
{
protected:
    const char* reason;
public:
    HasSameGroup(): reason("Такая группа уже существует.")
        {   }
    
    virtual const char* why()
    {
        return reason;
    }
};
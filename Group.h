#ifndef GROUP_H
#define GROUP_H

#include <iostream>

#include "Student.h"

class Group
{
private:
    unsigned short ID;

    struct Node
    {
        Student student;

        Node* prev  = nullptr;
        Node* next = nullptr;
    };

    Node* head = nullptr;

public:
   

};




#endif
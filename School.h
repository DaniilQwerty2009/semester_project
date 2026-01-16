#ifndef SCHOOL_H
#define SCHOOL_H

#include <iostream>

#include "Student.h"

class School
{
private:
    struct Node
    {
        Student studentInfo;

        Node* prev = nullptr;
        Node* next = nullptr;

        Node(unsigned studentID, const char* lastname, unsigned groupID = 0)
        :studentInfo(studentID, lastname, groupID)
            {   }
    };

    Node* head = nullptr;
    Node* tail = nullptr;

    const Node* getHead()
        { return head; }

public:

    class iterator
        {
        private:
            Node* pointer;
        public:
            iterator()
                {   }   
            
            Node* operator=(Node* nodePtr)
            {
                pointer = nodePtr;
            }

            
            

        };

    School()
        {   }
 

    void addStudent(unsigned studentID, const char* lastname, unsigned groupID = 0)
    {
        if(!head)
        {
            head = new Node(studentID, lastname, groupID);
            tail = head;
        }
        else
        {
            tail->next = new Node(studentID, lastname, groupID);
            Node* oldTail = tail;
            tail = tail->next;
            tail->prev = oldTail;
        }
    }

    void printList() const
    {
        Node* iterator = head;

        while(iterator)
        {
            iterator->studentInfo.printInfo();
            iterator = iterator->next;
        }
    }

    inline Node* begin() const
    {
        return head;
    }
};








#endif
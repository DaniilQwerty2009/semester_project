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

public:

    class iterator
        {
        private:
            Node* pointer;
        public:
            iterator():pointer(nullptr)
            {   }   
            
            void operator=(Node* nodePtr);

            Student* operator*();

            const char*           getLastname() const; 

            const unsigned&       getID() const; 

            const unsigned&       getVisits() const; 

            const unsigned short* getVisitsDates() const; 

            const unsigned&       getGroup() const; 

            void                  printInfo() const;
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

    inline Node* end() const
    {
        return tail;
    }

    


};








#endif
#ifndef STUDENT_H
#define STUDENT_H


struct Student
{
private:
    const long* const studentID;
    const char* name;
    const char* lastname;

    const unsigned short* groupID;

    unsigned visits;

public:
    Student(const long* studenID, const char* name, const char* lastname, const unsigned short* groupID = 0, unsigned visits = 0)
        :studentID(studenID),
        name(name),
        lastname(lastname),
        groupID(groupID),
        visits(visits)
        {   }
    
    // для деструктора определить freeID для studentID
};










#endif
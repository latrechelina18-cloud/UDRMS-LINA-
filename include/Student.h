#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include <string>
using namespace std;

class Student : public Person {
private:
    int academicYear;
    string dormitoryName;
    string roomNumber;

public:
    // Constructor
    Student(string id, string fullName, string email, 
            string password, int academicYear);

    // Getters
    int getAcademicYear() const;
    string getDormitoryName() const;
    string getRoomNumber() const;

    // Setters
    void setAcademicYear(int year);
    void setDormitoryName(string dorm);
    void setRoomNumber(string room);

    // Check if assigned to a room
    bool isAssigned() const;

    // Operator overloading (compare students by ID)
    bool operator==(const Student& other) const;

    // Override pure virtual
    void displayInfo() const override;
};

#endif
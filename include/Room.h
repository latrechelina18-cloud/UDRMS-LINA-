#ifndef ROOM_H
#define ROOM_H

#include "Student.h"
#include <vector>
#include <string>
using namespace std;

class Room {
private:
    string roomNumber;
    int capacity;
    vector<Student*> students;

public:
    Room(string roomNumber, int capacity);

    // Getters
    string getRoomNumber() const;
    int getCapacity() const;
    int getCurrentOccupancy() const;
    vector<Student*> getStudents() const;

    // Operations
    bool isFull() const;
    bool addStudent(Student* student);
    bool removeStudent(string studentId);
    bool hasStudent(string studentId) const;

    void displayInfo() const;
};

#endif
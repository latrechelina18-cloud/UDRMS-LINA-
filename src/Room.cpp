#include "Room.h"
#include <iostream>
using namespace std;

Room::Room(string roomNumber, int capacity) {
    this->roomNumber = roomNumber;
    this->capacity   = capacity;
}

string Room::getRoomNumber() const { return roomNumber; }
int Room::getCapacity() const { return capacity; }
int Room::getCurrentOccupancy() const { return students.size(); }
vector<Student*> Room::getStudents() const { return students; }

bool Room::isFull() const {
    return (int)students.size() >= capacity;
}

bool Room::addStudent(Student* student) {
    if (isFull()) {
        throw runtime_error("Room " + roomNumber + " is full!");
    }
    students.push_back(student);
    student->setRoomNumber(roomNumber);
    return true;
}

bool Room::removeStudent(string studentId) {
    for (int i = 0; i < (int)students.size(); i++) {
        if (students[i]->getId() == studentId) {
            students[i]->setRoomNumber("");
            students.erase(students.begin() + i);
            return true;
        }
    }
    return false;
}

bool Room::hasStudent(string studentId) const {
    for (Student* s : students) {
        if (s->getId() == studentId) return true;
    }
    return false;
}

void Room::displayInfo() const {
    cout << "Room " << roomNumber
         << " [" << students.size() << "/" << capacity << "]" << endl;
    for (Student* s : students) {
        cout << "  - " << s->getFullName() << endl;
    }
}
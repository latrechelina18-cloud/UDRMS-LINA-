#include "Student.h"
#include <iostream>
using namespace std;

Student::Student(string id, string fullName, string email,
                 string password, int academicYear)
    : Person(id, fullName, email, password) {
    this->academicYear  = academicYear;
    this->dormitoryName = "";
    this->roomNumber    = "";
}

// Getters
int Student::getAcademicYear() const {
    return academicYear;
}

string Student::getDormitoryName() const {
    return dormitoryName;
}

string Student::getRoomNumber() const {
    return roomNumber;
}

// Setters
void Student::setAcademicYear(int year) {
    this->academicYear = year;
}

void Student::setDormitoryName(string dorm) {
    this->dormitoryName = dorm;
}

void Student::setRoomNumber(string room) {
    this->roomNumber = room;
}

// Check if assigned
bool Student::isAssigned() const {
    return dormitoryName != "" && roomNumber != "";
}

// Operator == (compare by ID)
bool Student::operator==(const Student& other) const {
    return this->id == other.id;
}

// displayInfo
void Student::displayInfo() const {
    cout << "--- Student Info ---" << endl;
    cout << "ID:            " << id << endl;
    cout << "Name:          " << fullName << endl;
    cout << "Email:         " << email << endl;
    cout << "Academic Year: " << academicYear << endl;
    if (isAssigned()) {
        cout << "Dormitory:     " << dormitoryName << endl;
        cout << "Room:          " << roomNumber << endl;
    } else {
        cout << "Status:        Not assigned to any room" << endl;
    }
}
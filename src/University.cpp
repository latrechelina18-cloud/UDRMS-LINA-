#include "University.h"
#include <iostream>
using namespace std;

University::University(string name) {
    this->name = name;
}

string University::getName() const { return name; }
vector<Student>& University::getStudents() { return students; }
vector<Dormitory>& University::getDormitories() { return dormitories; }

void University::addStudent(Student student) {
    students.push_back(student);
}

bool University::removeStudent(string studentId) {
    for (int i = 0; i < (int)students.size(); i++) {
        if (students[i].getId() == studentId) {
            students.erase(students.begin() + i);
            return true;
        }
    }
    return false;
}

Student* University::findStudent(string studentId) {
    for (Student& s : students) {
        if (s.getId() == studentId) return &s;
    }
    return nullptr;
}

Student* University::findStudentByEmail(string email) {
    for (Student& s : students) {
        if (s.getEmail() == email) return &s;
    }
    return nullptr;
}

void University::addDormitory(Dormitory dorm) {
    dormitories.push_back(dorm);
}

Dormitory* University::findDormitory(string name) {
    for (Dormitory& d : dormitories) {
        if (d.getName() == name) return &d;
    }
    return nullptr;
}

void University::displayInfo() const {
    cout << "=== " << name << " ===" << endl;
    cout << "Students: " << students.size() << endl;
    cout << "Dormitories: " << dormitories.size() << endl;
    for (const Dormitory& d : dormitories) d.displayInfo();
}
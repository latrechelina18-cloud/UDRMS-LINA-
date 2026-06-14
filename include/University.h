#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include "Dormitory.h"
#include <vector>
#include <string>
using namespace std;

class University {
private:
    string name;
    vector<Student> students;
    vector<Dormitory> dormitories;

public:
    University(string name);

    // Getters
    string getName() const;
    vector<Student>& getStudents();
    vector<Dormitory>& getDormitories();

    // Student operations
    void addStudent(Student student);
    bool removeStudent(string studentId);
    Student* findStudent(string studentId);
    Student* findStudentByEmail(string email);

    // Dormitory operations
    void addDormitory(Dormitory dorm);
    Dormitory* findDormitory(string name);

    // Search (uses template)
    template<typename T>
    T* findById(vector<T>& list, string id);

    void displayInfo() const;
};

#endif
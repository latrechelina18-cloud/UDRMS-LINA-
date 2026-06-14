#include "Staff.h"
#include <iostream>
using namespace std;

Staff::Staff(string id, string fullName, string email,
             string password, string role, double salary)
    : Person(id, fullName, email, password) {
    this->role   = role;
    this->salary = salary;
}

string Staff::getRole() const {
    return role;
}

double Staff::getSalary() const {
    return salary;
}

void Staff::setRole(string role) {
    this->role = role;
}

void Staff::setSalary(double salary) {
    this->salary = salary;
}

void Staff::displayInfo() const {
    cout << "--- Staff Info ---" << endl;
    cout << "ID:     " << id << endl;
    cout << "Name:   " << fullName << endl;
    cout << "Email:  " << email << endl;
    cout << "Role:   " << role << endl;
    cout << "Salary: " << salary << " DA" << endl;
}
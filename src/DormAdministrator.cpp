#include "DormAdministrator.h"
#include <iostream>
using namespace std;

DormAdministrator::DormAdministrator(string id, string fullName,
    string email, string password, double salary, string managedDormitory)
    : Staff(id, fullName, email, password, "Dorm Administrator", salary) {
    this->managedDormitory = managedDormitory;
}

string DormAdministrator::getManagedDormitory() const {
    return managedDormitory;
}

void DormAdministrator::setManagedDormitory(string dorm) {
    this->managedDormitory = dorm;
}

void DormAdministrator::performDuty() const {
    cout << fullName << " is managing dormitory: " 
         << managedDormitory << endl;
}

void DormAdministrator::displayInfo() const {
    Staff::displayInfo();
    cout << "Manages: " << managedDormitory << endl;
}
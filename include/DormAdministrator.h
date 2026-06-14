#ifndef DORMADMINISTRATOR_H
#define DORMADMINISTRATOR_H

#include "Staff.h"
using namespace std;

class DormAdministrator : public Staff {
private:
    string managedDormitory;

public:
    DormAdministrator(string id, string fullName, string email,
                      string password, double salary,
                      string managedDormitory);

    string getManagedDormitory() const;
    void setManagedDormitory(string dorm);

    void performDuty() const override;
    void displayInfo() const override;
};

#endif
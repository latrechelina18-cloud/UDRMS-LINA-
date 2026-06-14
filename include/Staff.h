#ifndef STAFF_H
#define STAFF_H

#include "Person.h"
#include <string>
using namespace std;

class Staff : public Person {
protected:
    string role;
    double salary;

public:
    // Constructor
    Staff(string id, string fullName, string email,
          string password, string role, double salary);

    // Getters
    string getRole() const;
    double getSalary() const;

    // Setters
    void setRole(string role);
    void setSalary(double salary);

    // Pure virtual → Staff is also abstract
    virtual void performDuty() const = 0;

    // Override Person's pure virtual
    void displayInfo() const override;

    virtual ~Staff() {}
};

#endif
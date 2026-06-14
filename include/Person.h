#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;

class Person {
protected:
    string id;
    string fullName;
    string email;
    string password;

public:
    // Constructor
    Person(string id, string fullName, string email, string password);

    // Getters
    string getId() const;
    string getFullName() const;
    string getEmail() const;
    string getPassword() const;

    // Setters
    void setFullName(string name);
    void setEmail(string email);
    void setPassword(string password);

    // Pure virtual → makes Person abstract
    virtual void displayInfo() const = 0;

    // Virtual destructor (always needed with inheritance)
    virtual ~Person();
};

#endif
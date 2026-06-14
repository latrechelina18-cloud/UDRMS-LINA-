#include "Person.h"
#include <iostream>
using namespace std;

// Constructor
Person::Person(string id, string fullName, string email, string password) {
    this->id       = id;
    this->fullName = fullName;
    this->email    = email;
    this->password = password;
}

// Getters
string Person::getId() const {
    return id;
}

string Person::getFullName() const {
    return fullName;
}

string Person::getEmail() const {
    return email;
}

string Person::getPassword() const {
    return password;
}

// Setters
void Person::setFullName(string name) {
    this->fullName = name;
}

void Person::setEmail(string email) {
    this->email = email;
}

void Person::setPassword(string password) {
    this->password = password;
}

// Destructor
Person::~Person() {}
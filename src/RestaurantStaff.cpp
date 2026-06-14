#include "RestaurantStaff.h"
#include <iostream>
using namespace std;

RestaurantStaff::RestaurantStaff(string id, string fullName,
    string email, string password, double salary,
    string assignedRestaurant)
    : Staff(id, fullName, email, password, "Restaurant Staff", salary) {
    this->assignedRestaurant = assignedRestaurant;
}

string RestaurantStaff::getAssignedRestaurant() const {
    return assignedRestaurant;
}

void RestaurantStaff::setAssignedRestaurant(string restaurant) {
    this->assignedRestaurant = restaurant;
}

void RestaurantStaff::performDuty() const {
    cout << fullName << " is managing restaurant: "
         << assignedRestaurant << endl;
}

void RestaurantStaff::displayInfo() const {
    Staff::displayInfo();
    cout << "Restaurant: " << assignedRestaurant << endl;
}
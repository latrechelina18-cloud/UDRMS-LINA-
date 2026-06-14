#ifndef RESTAURANTSTAFF_H
#define RESTAURANTSTAFF_H

#include "Staff.h"
using namespace std;

class RestaurantStaff : public Staff {
private:
    string assignedRestaurant;

public:
    RestaurantStaff(string id, string fullName, string email,
                    string password, double salary,
                    string assignedRestaurant);

    string getAssignedRestaurant() const;
    void setAssignedRestaurant(string restaurant);

    void performDuty() const override;
    void displayInfo() const override;
};

#endif
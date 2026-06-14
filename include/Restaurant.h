#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <string>
using namespace std;

class Restaurant {
private:
    string name;
    string breakfast;
    string lunch;
    string dinner;
    int mealsServedToday;

public:
    Restaurant(string name = "University Restaurant");

    // Getters
    string getName() const;
    string getBreakfast() const;
    string getLunch() const;
    string getDinner() const;
    int getMealsServedToday() const;

    // Setters
    void setName(string name);
    void setBreakfast(string meal);
    void setLunch(string meal);
    void setDinner(string meal);

    // Operations
    void updateMenu(string breakfast, string lunch, string dinner);
    void serveMeal();
    void resetDailyCount();
    void displayMenu() const;
};

#endif
#ifndef DORMITORY_H
#define DORMITORY_H

#include "Room.h"
#include "Restaurant.h"
#include <vector>
#include <string>
using namespace std;

class Dormitory {
private:
    string name;
    string location;
    Restaurant restaurant;
    vector<Room> rooms;

public:
    Dormitory(string name, string location);

    // Getters
    string getName() const;
    string getLocation() const;
    Restaurant& getRestaurant();
    vector<Room>& getRooms();

    // Room operations
    void addRoom(string roomNumber, int capacity);
    bool assignStudent(Student* student, string roomNumber);
    bool removeStudent(string studentId);
    Room* findRoom(string roomNumber);
    Student* findStudent(string studentId);

    int getTotalCapacity() const;
    int getTotalOccupancy() const;

    void displayInfo() const;
};

#endif
#include "Dormitory.h"
#include <iostream>
using namespace std;

Dormitory::Dormitory(string name, string location)
    : restaurant(name + " Restaurant") {
    this->name     = name;
    this->location = location;
}

string Dormitory::getName() const { return name; }
string Dormitory::getLocation() const { return location; }
Restaurant& Dormitory::getRestaurant() { return restaurant; }
vector<Room>& Dormitory::getRooms() { return rooms; }

void Dormitory::addRoom(string roomNumber, int capacity) {
    rooms.push_back(Room(roomNumber, capacity));
}

bool Dormitory::assignStudent(Student* student, string roomNumber) {
    Room* room = findRoom(roomNumber);
    if (room == nullptr) {
        throw runtime_error("Room " + roomNumber + " not found!");
    }
    room->addStudent(student);
    student->setDormitoryName(name);
    return true;
}

bool Dormitory::removeStudent(string studentId) {
    for (Room& room : rooms) {
        if (room.removeStudent(studentId)) return true;
    }
    return false;
}

Room* Dormitory::findRoom(string roomNumber) {
    for (Room& room : rooms) {
        if (room.getRoomNumber() == roomNumber) return &room;
    }
    return nullptr;
}

Student* Dormitory::findStudent(string studentId) {
    for (Room& room : rooms) {
        for (Student* s : room.getStudents()) {
            if (s->getId() == studentId) return s;
        }
    }
    return nullptr;
}

int Dormitory::getTotalCapacity() const {
    int total = 0;
    for (const Room& room : rooms) total += room.getCapacity();
    return total;
}

int Dormitory::getTotalOccupancy() const {
    int total = 0;
    for (const Room& room : rooms) total += room.getCurrentOccupancy();
    return total;
}

void Dormitory::displayInfo() const {
    cout << "=== Dormitory: " << name << " ===" << endl;
    cout << "Location: " << location << endl;
    cout << "Rooms: " << rooms.size() << endl;
    for (const Room& room : rooms) room.displayInfo();
    restaurant.displayMenu();
}
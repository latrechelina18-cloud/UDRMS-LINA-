#include "DataManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// ─── SAVE ───────────────────────────────────────────

void DataManager::saveData(University& university, string path) {
    saveStudents(university, path);
    saveDormitories(university, path);
    cout << "All data saved." << endl;
}

void DataManager::saveStudents(University& university, string path) {
    ofstream file(path + "students.csv");
    if (!file.is_open()) {
        cerr << "Could not open students.csv for writing." << endl;
        return;
    }
    // Header
    file << "id,fullName,email,password,academicYear,dormitory,room\n";
    for (Student& s : university.getStudents()) {
        file << s.getId()           << ","
             << s.getFullName()     << ","
             << s.getEmail()        << ","
             << s.getPassword()     << ","
             << s.getAcademicYear() << ","
             << s.getDormitoryName()<< ","
             << s.getRoomNumber()   << "\n";
    }
    file.close();
}

void DataManager::saveDormitories(University& university, string path) {
    ofstream file(path + "dormitories.csv");
    if (!file.is_open()) {
        cerr << "Could not open dormitories.csv for writing." << endl;
        return;
    }
    file << "dormName,location,roomNumber,capacity\n";
    for (Dormitory& d : university.getDormitories()) {
        for (Room& r : d.getRooms()) {
            file << d.getName()        << ","
                 << d.getLocation()    << ","
                 << r.getRoomNumber()  << ","
                 << r.getCapacity()    << "\n";
        }
        // Save restaurant menu
    }
    file.close();

    // Save restaurant menus separately
    ofstream menuFile(path + "menus.csv");
    menuFile << "dormName,breakfast,lunch,dinner\n";
    for (Dormitory& d : university.getDormitories()) {
        Restaurant& r = d.getRestaurant();
        menuFile << d.getName()      << ","
                 << r.getBreakfast() << ","
                 << r.getLunch()     << ","
                 << r.getDinner()    << "\n";
    }
    menuFile.close();
}

// ─── LOAD ───────────────────────────────────────────

void DataManager::loadData(University& university, string path) {
    loadDormitories(university, path);
    loadStudents(university, path);
    cout << "All data loaded." << endl;
}

void DataManager::loadStudents(University& university, string path) {
    ifstream file(path + "students.csv");
    if (!file.is_open()) return;

    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, name, email, password, yearStr, dorm, room;

        getline(ss, id,       ',');
        getline(ss, name,     ',');
        getline(ss, email,    ',');
        getline(ss, password, ',');
        getline(ss, yearStr,  ',');
        getline(ss, dorm,     ',');
        getline(ss, room,     ',');

        Student s(id, name, email, password, stoi(yearStr));
        s.setDormitoryName(dorm);
        s.setRoomNumber(room);
        university.addStudent(s);
    }
    file.close();
}

void DataManager::loadDormitories(University& university, string path) {
    // Load dorms and rooms
    ifstream file(path + "dormitories.csv");
    if (!file.is_open()) return;

    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string dormName, location, roomNumber, capacityStr;

        getline(ss, dormName,    ',');
        getline(ss, location,    ',');
        getline(ss, roomNumber,  ',');
        getline(ss, capacityStr, ',');

        // Find or create dormitory
        Dormitory* existing = university.findDormitory(dormName);
        if (existing == nullptr) {
            university.addDormitory(Dormitory(dormName, location));
            existing = university.findDormitory(dormName);
        }
        if (existing && !roomNumber.empty()) {
            existing->addRoom(roomNumber, stoi(capacityStr));
        }
    }
    file.close();

    // Load menus
    ifstream menuFile(path + "menus.csv");
    if (!menuFile.is_open()) return;

    getline(menuFile, line); // skip header
    while (getline(menuFile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string dormName, breakfast, lunch, dinner;

        getline(ss, dormName,  ',');
        getline(ss, breakfast, ',');
        getline(ss, lunch,     ',');
        getline(ss, dinner,    ',');

        Dormitory* d = university.findDormitory(dormName);
        if (d) d->getRestaurant().updateMenu(breakfast, lunch, dinner);
    }
    menuFile.close();
}
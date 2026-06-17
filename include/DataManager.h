#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "University.h"
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class DataManager {
public:
    static void saveData(University& university, string path = "data/");
    static void loadData(University& university, string path = "data/");

private:
    static void saveStudents(University& university, string path);
    static void saveDormitories(University& university, string path);
    static void loadStudents(University& university, string path);
    static void loadDormitories(University& university, string path);
};

#endif
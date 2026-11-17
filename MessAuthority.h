#pragma once
#include <string>
#include <vector>
#include <memory>
#include "student.h"
#include "menu.h"
using namespace std;

class MessAuthority {
    string authorityName;
    string authorityID;
    vector<unique_ptr<student>> students;   // base pointers: holds all student types
    menu messMenu;

public:
    MessAuthority(string name, string id, int menuId);
    student* findStudent(long int enrollment);
    menu& getMenu();
    void addMeal();
    void removeMeal();
    void updateMeal();
    void viewMenu();
    void addStudents();
    void removeStudents();
    void viewStudents();
    void viewFeedback();
    void generateWasteReport();
    void generateStudentsReport();
    void generateFinancialReport();
    void generateAllReports();
};

#pragma once
#include <string>
#include <vector>
#include "student.h"
#include "menu.h"
using namespace std;

class MessAuthority {
    string authorityName;
    string authorityID;
    vector<student> students;
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
};
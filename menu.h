#pragma once
#include <vector>
#include <string>
#include <utility>
#include "meal.h" // Menu needs to know what a meal is
using namespace std;

class MessAuthority;

class menu {
    int menuID;
    vector<pair<string, vector<meal>>> weeklySchedule;
    friend class MessAuthority;

public:
    menu(int id);
    void setMealsForDay();
    const vector<pair<string, vector<meal>>>& getWeeklySchedule() const;
    vector<meal>* getMealsForDay(const string& day);
};
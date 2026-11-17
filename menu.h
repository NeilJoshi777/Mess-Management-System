#pragma once
#include <vector>
#include <string>
#include <utility>
#include <memory>
#include "meal.h" // Menu needs to know what a meal is
using namespace std;

class MessAuthority;

// The menu stores meal POINTERS (base class), so one list can hold
// Breakfast, Lunch, Dinner and SpecialMeal objects together.
using MealList = vector<unique_ptr<meal>>;

class menu {
    int menuID;
    vector<pair<string, MealList>> weeklySchedule;
    friend class MessAuthority;

public:
    menu(int id);
    void setMealsForDay();
    const vector<pair<string, MealList>>& getWeeklySchedule() const;
    MealList* getMealsForDay(const string& day);
};

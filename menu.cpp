#include "menu.h"
#include "utils.h" // For readInt
#include <iostream>
#include <limits>

using namespace std;

menu::menu(int id) {
        menuID = id;
        vector<string> days =
        {
            "Monday",
            "Tuesday",
            "Wednesday",
            "Thursday",
            "Friday",
            "Saturday",
            "Sunday"
        };

        for (int i = 0; i < days.size(); i++)
        {
            weeklySchedule.emplace_back(days[i], MealList());
        }
    }
    
    void menu::setMealsForDay() {
        string day;
        int n;

        cout << "Enter day: ";
        cin >> day;

        MealList* meals = getMealsForDay(day);
        if (meals == nullptr)
        {
            cout << "Invalid day!\n";
            return;
        }

        n = readInt("How many meals do you want to set for this day? ", 1, 10);

        for (int i = 0; i < n; i++)
        {
            // factory returns the right derived object behind a meal pointer
            meals->push_back(promptAndCreateMeal());
        }

        cout << "\nMeals added to " << day << " successfully!\n";
    }       // sets up meals for a day

    const vector<pair<string, MealList>>& menu::getWeeklySchedule() const{
        return weeklySchedule;
    }       // Returns schedule for a week

    MealList* menu::getMealsForDay(const string& day) {
        for (int i = 0; i < weeklySchedule.size(); i++)
        {
            if (equalsIgnoreCase(weeklySchedule[i].first, day))
            {
                return &weeklySchedule[i].second;
            }
        }

        return nullptr;
    }   
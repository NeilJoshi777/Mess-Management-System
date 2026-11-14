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
            weeklySchedule.push_back({days[i], vector<meal>()});
        }
    }
    
    void menu::setMealsForDay() {
        string day, type, item;
        int n, itemCount, prepared;
        double price;

        cout << "Enter day: ";
        cin >> day;

        int dayIndex = -1;

        for (int i = 0; i < weeklySchedule.size(); i++)
        {
            if (weeklySchedule[i].first == day)
            {
                dayIndex = i;
                break;
            }
        }

        if (dayIndex == -1)
        {
            cout << "Invalid day!\n";
            return;
        }

        n = readInt("How many meals do you want to set for this day? ", 1, 10);

        for (int i = 0; i < n; i++)
        {
            cout << "\nEnter meal type: ";
            cin >> type;

            itemCount = readInt("Enter number of food items: ", 1, 50);

            vector<string> items;

            for (int j = 0; j < itemCount; j++)
            {
                cout << "Enter food item: ";

                cin >> ws;
                getline(cin, item);

                items.push_back(item);
            }

            while (true)
            {
                cout << "Enter price: Rs. ";

                if (cin >> price && price >= 0)
                    break;

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Invalid price!\n";
            }

            prepared = readInt("Enter quantity prepared: ", 0, 100000);

            meal m(type, items, price, prepared);

            weeklySchedule[dayIndex].second.push_back(m);
        }

        cout << "\nMeals added to " << day << " successfully!\n";
    }       // sets up mewals for a day

    const vector<pair<string, vector<meal>>>& menu::getWeeklySchedule() const{
        return weeklySchedule;
    }       // Returns schedule for a week

    vector<meal>* menu::getMealsForDay(const string& day) {
        for (int i = 0; i < weeklySchedule.size(); i++)
        {
            if (weeklySchedule[i].first == day)
            {
                return &weeklySchedule[i].second;
            }
        }

        return nullptr;
    }   
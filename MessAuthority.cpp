#include "MessAuthority.h"
#include "utils.h" // For readInt
#include <iostream>
#include <limits>
using namespace std;

MessAuthority::MessAuthority(string name, string id, int menuId) : authorityName(name), authorityID(id), messMenu(menuId){};
    // Find a student by enrollment number (returns nullptr if not found)
   student* MessAuthority::findStudent(long int enrollment) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i].Enrollment_no == enrollment)
            return &students[i];
    }
    return nullptr;
}

// Lets a student view the menu / pick a meal
   menu& MessAuthority::getMenu() {
    return messMenu;
}
    void MessAuthority::addMeal()
    {
    string day, type, item;
    vector<string> foodItems;

    double price;
    int n, prepared;

    cout << "Enter day: ";
    cin >> day;

    cout << "Enter meal type: ";
    cin >> type;

    n = readInt("Enter number of food items: ", 1, 50);

    for (int i = 0; i < n; i++)
    {
        cout << "Enter food item: ";

        cin >> ws;
        getline(cin, item);

        foodItems.push_back(item);
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

    for (int i = 0; i < messMenu.weeklySchedule.size(); i++)
    {
        if (messMenu.weeklySchedule[i].first == day)
        {
            meal m(type, foodItems, price, prepared);

            messMenu.weeklySchedule[i].second.push_back(m);

            cout << "Meal added successfully!\n";
            return;
        }
    }

    cout << "Day not found!\n";
    }
    void MessAuthority::removeMeal(){
        string day, type;

    cout << "Enter day: ";
    cin >> day;

    cout << "Enter meal type to remove: ";
    cin >> type;

    for (int i = 0; i < messMenu.weeklySchedule.size(); i++) {

        if (messMenu.weeklySchedule[i].first == day) {

            for (int j = 0; j < messMenu.weeklySchedule[i].second.size(); j++) {

                if (messMenu.weeklySchedule[i].second[j].mealType == type) {

                    messMenu.weeklySchedule[i].second.erase(
                        messMenu.weeklySchedule[i].second.begin() + j
                    );

                    cout << "Meal removed successfully!";
                    return;
                }
            }

            cout << "Meal not found!";
            return;
        }
    }

    cout << "Day not found!";
    }
    void MessAuthority::updateMeal()
{
    string day, type;

    cout << "Enter day: ";
    cin >> day;

    cout << "Enter meal type to update: ";
    cin >> type;

    for (int i = 0; i < messMenu.weeklySchedule.size(); i++)
    {
        if (messMenu.weeklySchedule[i].first == day)
        {
            for (int j = 0; j < messMenu.weeklySchedule[i].second.size(); j++)
            {
                if (messMenu.weeklySchedule[i].second[j].mealType == type)
                {
                    meal& m = messMenu.weeklySchedule[i].second[j];

                    cout << "\nWhat do you want to update?\n";
                    cout << "1. Add food items\n";
                    cout << "2. Remove food items\n";
                    cout << "3. Change price\n";
                    cout << "4. Change prepared quantity\n";

                    int choice = readInt("Enter choice: ", 1, 4);

                    switch (choice)
                    {
                        case 1:
                            m.addFoodItems();
                            break;

                        case 2:
                            m.removeFoodItems();
                            break;

                        case 3:
                            m.setPrice();
                            break;

                        case 4:
                        {
                            int quantity = readInt(
                                "Enter new prepared quantity: ",
                                m.getQuantityConsumed(),
                                100000
                            );

                            m.setQuantityPrepared(quantity);
                            break;
                        }
                    }

                    cout << "Meal update operation completed.\n";
                    return;
                }
            }

            cout << "Meal not found!\n";
            return;
        }
    }

    cout << "Day not found!\n";
}
    void MessAuthority::viewMenu(){
         for (int i = 0; i < messMenu.weeklySchedule.size(); i++) {

        cout << "\nDay: " << messMenu.weeklySchedule[i].first << endl;

        for (int j = 0; j < messMenu.weeklySchedule[i].second.size(); j++) {

            cout << "\nMeal Type: "
                 << messMenu.weeklySchedule[i].second[j].mealType;

            cout << "\nFood Items: ";

            for (int k = 0; k < messMenu.weeklySchedule[i].second[j].foodItems.size(); k++) {

                cout << messMenu.weeklySchedule[i].second[j].foodItems[k];

                if (k != messMenu.weeklySchedule[i].second[j].foodItems.size() - 1)
                    cout << ", ";
            }

            cout << "\nPrice: Rs. "
                 << messMenu.weeklySchedule[i].second[j].price << endl;

            cout << "-----------------------------\n";
        }
      }
    }
    void MessAuthority::addStudents(){
        long int enrollment;
        string name;

    cout << "Enter Enrollment Number: ";
    cin >> enrollment;

    // Check if student already exists
    for (int i = 0; i < students.size(); i++) {

        if (students[i].Enrollment_no == enrollment) {
            cout << "Student already exists!";
            return;
        }
    }

    cout << "Enter Student Name: ";
    cin.ignore();
    getline(cin, name);

    student s(enrollment, name);

    students.push_back(s);

    cout << "Student added successfully!";
    }
    void MessAuthority::removeStudents(){

    long int enrollment;

    cout << "Enter Enrollment Number of student to remove: ";
    cin >> enrollment;

    for (int i = 0; i < students.size(); i++) {

        if (students[i].Enrollment_no == enrollment) {

            students.erase(students.begin() + i);

            cout << "Student removed successfully!";
            return;
        }
    }

    cout << "Student not found!";
    }
    void MessAuthority::viewStudents(){
        if (students.empty()) {
        cout << "No students registered yet!";
        return;
    }

    for (int i = 0; i < students.size(); i++) {

        cout << "\nStudent " << i + 1 << endl;

        cout << "Enrollment Number: "
             << students[i].Enrollment_no << endl;

        cout << "Student Name: "
             << students[i].Student_name << endl;

        cout << "Membership Status: ";

        if (students[i].active_status == true)
            cout << "Active" << endl;
        else
            cout << "Inactive" << endl;

        cout << "Due Amount: Rs. "
             << students[i].Due_amount << endl;

        cout << "--------------------------\n";
    }
    }    //checking which students are subscribed to mess or not
    void MessAuthority::viewFeedback(){
        if (students.empty()) {
        cout << "No students registered!";
        return;
    }

    for (int i = 0; i < students.size(); i++) {

        if (students[i].feedback != "") {

            cout << "\nStudent Name: "
                 << students[i].Student_name << endl;

            cout << "Feedback: "
                 << students[i].feedback << endl;

            cout << "-------------------------\n";
        }
     }
    }   //viewing the feedback of students
    void MessAuthority::generateWasteReport()
    {
    int totalPrepared = 0;
    int totalConsumed = 0;

    for (int i = 0; i < messMenu.weeklySchedule.size(); i++)
    {
        for (int j = 0; j < messMenu.weeklySchedule[i].second.size(); j++)
        {
            const meal& m = messMenu.weeklySchedule[i].second[j];

            totalPrepared += m.getQuantityPrepared();

            totalConsumed += m.getQuantityConsumed();
        }
    }

    int totalWasted = totalPrepared - totalConsumed;

    cout << "\n========== WASTE REPORT ==========\n";

    cout << "Total Food Prepared: "
         << totalPrepared << " plates\n";

    cout << "Total Food Consumed: "
         << totalConsumed << " plates\n";

    cout << "Total Food Wasted: "
         << totalWasted << " plates\n";

    cout << "==================================\n";
    }
    
    void MessAuthority::generateStudentsReport(){
    int totalStudents = students.size();
    int activeStudents = 0;
    int inactiveStudents = 0;
    int totalDue = 0;

    for (int i = 0; i < students.size(); i++) {

        if (students[i].active_status == true) {
            activeStudents++;
        }
        else {
            inactiveStudents++;
        }

        totalDue += students[i].Due_amount;
    }

    cout << "\n========== STUDENT REPORT ==========\n";

    cout << "Total Students: " << totalStudents << endl;
    cout << "Active Students: " << activeStudents << endl;
    cout << "Inactive Students: " << inactiveStudents << endl;
    cout << "Total Outstanding Dues: Rs. " << totalDue << endl;

    cout << "====================================\n";
    }   //report regarding # of students being subscribed, to eat all 3/4 time meals.
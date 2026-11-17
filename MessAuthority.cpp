#include "MessAuthority.h"
#include "utils.h" // For readInt
#include "report.h"
#include <iostream>
#include <limits>
using namespace std;

MessAuthority::MessAuthority(string name, string id, int menuId) : authorityName(name), authorityID(id), messMenu(menuId){};
    // Find a student by enrollment number (returns nullptr if not found)
   student* MessAuthority::findStudent(long int enrollment) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i]->Enrollment_no == enrollment)
            return students[i].get();
    }
    return nullptr;
}

// Lets a student view the menu / pick a meal
   menu& MessAuthority::getMenu() {
    return messMenu;
}
    void MessAuthority::addMeal()
    {
    string day;

    cout << "Enter day: ";
    cin >> day;

    MealList* meals = messMenu.getMealsForDay(day);
    if (meals == nullptr)
    {
        cout << "Day not found!\n";
        return;
    }

    // Factory returns Breakfast / Lunch / Dinner / SpecialMeal behind a meal pointer.
    meals->push_back(promptAndCreateMeal());
    cout << "Meal added successfully!\n";
    }
    void MessAuthority::removeMeal(){
        string day, type;

    cout << "Enter day: ";
    cin >> day;

    cout << "Enter meal type to remove (Breakfast/Lunch/Dinner/Special): ";
    cin >> type;

    for (int i = 0; i < messMenu.weeklySchedule.size(); i++) {

        if (messMenu.weeklySchedule[i].first == day) {

            for (int j = 0; j < messMenu.weeklySchedule[i].second.size(); j++) {

                if (equalsIgnoreCase(messMenu.weeklySchedule[i].second[j]->getCategory(), type)) {

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

    cout << "Enter meal type to update (Breakfast/Lunch/Dinner/Special): ";
    cin >> type;

    for (int i = 0; i < messMenu.weeklySchedule.size(); i++)
    {
        if (messMenu.weeklySchedule[i].first == day)
        {
            for (int j = 0; j < messMenu.weeklySchedule[i].second.size(); j++)
            {
                if (equalsIgnoreCase(messMenu.weeklySchedule[i].second[j]->getCategory(), type))
                {
                    meal& m = *messMenu.weeklySchedule[i].second[j];

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
        for (size_t i = 0; i < messMenu.weeklySchedule.size(); i++) {
            cout << "\nDay: " << messMenu.weeklySchedule[i].first << endl;

            for (size_t j = 0; j < messMenu.weeklySchedule[i].second.size(); j++) {
                // runtime polymorphism: each meal prints itself
                messMenu.weeklySchedule[i].second[j]->displayMeal();
            }
        }
    }
    void MessAuthority::addStudents(){
        long int enrollment;
        string name;

    cout << "Enter Enrollment Number: ";
    cin >> enrollment;

    // Check if student already exists
    if (findStudent(enrollment) != nullptr) {
        cout << "Student already exists!";
        return;
    }

    cout << "Enter Student Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "\nSelect student type:\n";
    cout << "1. Hostel Student (10% meal discount)\n";
    cout << "2. Day Scholar (no discount)\n";
    cout << "3. Scholarship Student (custom discount)\n";
    int type = readInt("Enter choice: ", 1, 3);

    // Each branch creates a different derived object, stored as a student pointer.
    unique_ptr<student> s;
    if (type == 1) {
        string room;
        cout << "Enter hostel room number: ";
        getline(cin, room);
        s = make_unique<HostelStudent>(enrollment, name, room);
    }
    else if (type == 2) {
        string city;
        cout << "Enter home city: ";
        getline(cin, city);
        s = make_unique<DayScholar>(enrollment, name, city);
    }
    else {
        string scholarship;
        cout << "Enter scholarship name: ";
        getline(cin, scholarship);
        int percent = readInt("Enter discount % (1-100): ", 1, 100);
        s = make_unique<ScholarshipStudent>(enrollment, name, scholarship, percent);
    }

    students.push_back(std::move(s));

    cout << "Student added successfully!";
    }
    void MessAuthority::removeStudents(){

    long int enrollment;

    cout << "Enter Enrollment Number of student to remove: ";
    cin >> enrollment;

    for (int i = 0; i < students.size(); i++) {

        if (students[i]->Enrollment_no == enrollment) {

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

    for (size_t i = 0; i < students.size(); i++) {

        cout << "\nStudent " << i + 1 << endl;

        cout << "Enrollment Number: " << students[i]->Enrollment_no << endl;
        cout << "Student Name: " << students[i]->Student_name << endl;
        cout << "Student Type: " << students[i]->getStudentType() << endl;   // virtual call

        cout << "Membership Status: ";
        if (students[i]->revoked)
            cout << "Revoked" << endl;
        else if (students[i]->active_status)
            cout << "Active" << endl;
        else
            cout << "Inactive" << endl;

        cout << "Due Amount: Rs. " << students[i]->Due_amount << endl;

        cout << "--------------------------\n";
    }
    }    //checking which students are subscribed to mess or not
    void MessAuthority::viewFeedback(){
        if (students.empty()) {
        cout << "No students registered!";
        return;
    }

    for (size_t i = 0; i < students.size(); i++) {

        if (students[i]->feedback != "") {

            cout << "\nStudent Name: " << students[i]->Student_name << endl;
            cout << "Feedback: " << students[i]->feedback << endl;
            cout << "-------------------------\n";
        }
     }
    }   //viewing the feedback of students

    // ---- Reports: each report is a different derived class used through a Report pointer ----
    void MessAuthority::generateWasteReport()
    {
        unique_ptr<Report> r = make_unique<WasteReport>(messMenu);
        r->generate();
    }

    void MessAuthority::generateStudentsReport(){
        unique_ptr<Report> r = make_unique<StudentReport>(students);
        r->generate();
    }

    void MessAuthority::generateFinancialReport(){
        unique_ptr<Report> r = make_unique<FinancialReport>(students);
        r->generate();
    }

    // One loop, three different reports: the classic runtime polymorphism example.
    void MessAuthority::generateAllReports(){
        vector<unique_ptr<Report>> reports;
        reports.push_back(make_unique<WasteReport>(messMenu));
        reports.push_back(make_unique<StudentReport>(students));
        reports.push_back(make_unique<FinancialReport>(students));

        for (const auto& r : reports)
            r->generate();
    }

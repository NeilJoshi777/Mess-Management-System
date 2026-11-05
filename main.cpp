#include<iostream>
#include<bits/stdc++.h>    
using namespace std;

class MessAuthority{
    string authorityName;
    string authorityID;
    vector<student>students; //list of all the students
    menu messMenu;    //Authority can access the mess menu

    public:
    void addMeal();
    void removeMeal();
    void updateMeal();
    void viewMenu();
    void addStudents();
    void removeStudents();
    void viewStudents();     //checking which students are subscribed to mess or not
    void viewFeedback();    //viewing the feedback of students
    void generateWasteReport();
    void generateStudentsReport();   //report regarding # of students being subscribed, to eat all 3/4 time meals.
};


class student{
    protected:
    long int Enrollment_no;
    string Student_name;
    bool active_status(); 
    int Due_amount;
    
    public:

    void Give_feedback();
    void update_active_status(); //only able to eat meal if status is active
    void view_details(); //shows number of meals ate and total bill
    void pay_bill();
    void Revoke_membership();
    void mark_attendence(); //count meals ate
    void view_menu();
    
};

class meal
{
    string mealType; //Breakfast, lunch or dinner
    vector<string> foodItems;
    double price; 
    
    public:
    void addFoodItems();
    void removeFoodItems();
    void setPrice();
    double getPrice();
    void displayMeal();
};

class menu
{
    int menuID;
    vector<pair<string, vector<meal>>> weeklySchedule; // Will contain whole menu

    public:
    menu(int id);
    void setMealsForDay(); // sets up mewals for a day
    vector<pair<string, vector<meal>>> getWeeklySchedule(); // Returns schedule for a week
    vector<meal> getMealsForDay(); // Returns schedule of a day

};    


int main(){
    return 0;
}
#include<iostream>
#include<bits/stdc++.h>    
using namespace std;

class MessAuthority;
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
     meal(string type, vector<string> items, double p): mealType(type), foodItems(items), price(p) {}
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
    friend class MessAuthority;

    public:
    menu(int id);
    void setMealsForDay(); // sets up mewals for a day
    vector<pair<string, vector<meal>>> getWeeklySchedule(); // Returns schedule for a week
    vector<meal> getMealsForDay(); // Returns schedule of a day

};    

class MessAuthority{
    string authorityName;
    string authorityID;
    vector<student>students; //list of all the students
    menu messMenu;    //Authority can access the mess menu

    public:
    MessAuthority(string name, string id, int menuId) : authorityName(name), authorityID(id), messMenu(menuId){};
    void addMeal(){
        string day, type, item;
        vector<string> foodItems;
        double price;
        int n;

        cout << "\nEnter day: ";
        cin >> day;

        cout << "Enter meal type (Breakfast/Lunch/Dinner): ";
        cin >> type;

        cout << "Enter number of food items: ";
        cin >> n;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < n; i++) {
            cout << "Enter food item " << i + 1 << ": ";
            getline(cin, item);
            foodItems.push_back(item);
        }

        cout << "Enter meal price: ";
        cin >> price;

        for (auto &entry : messMenu.weeklySchedule) {

            if (entry.first == day) {

                entry.second.push_back(meal(type, foodItems, price));

                cout << "Meal added successfully!\n";
                return;
            }
        }

        cout << "Invalid day! Please set up the weekly schedule first.\n";
        
    }
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


int main(){
    return 0;
}
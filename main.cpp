#include<iostream>
#include<bits/stdc++.h>    
using namespace std;

class meal;
class menu;
class MessAuthority;

static int readInt(const string& prompt, int lo, int hi) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= lo && value <= hi) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            return value;
        }
        cin.clear();                                              
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter a number between " << lo << " and " << hi << ".\n";
    }
}
class student{
    protected:
    long int Enrollment_no;
    string Student_name;
    bool active_status; 
    int Due_amount;
    string feedback;
    int MealsEaten;
    bool revoked;

    public:
    friend class MessAuthority;
    student(long int enrollment, string name) {
    Enrollment_no = enrollment;
    Student_name = name;
    active_status = true;
    Due_amount = 0;
    MealsEaten =0;
    feedback= "";
    revoked = false;
    
}

    void Give_feedback(){
        int rating;
        string comment;

        cout << "\nEnter rating for the mess (1 to 5): ";
        cin >> rating;
        while (rating < 1 || rating > 5) {
            cout << "Invalid rating! Please enter a value between 1 and 5: ";
            cin >> rating;
        }

        cout << "Enter your feedback/comments: ";
        cin >> ws; 
        getline(cin, comment);

        feedback = "[Rating: " + to_string(rating) + "/5] " + comment;
        cout << "Thank you! Your feedback has been recorded successfully.\n";
    }
    
    void update_active_status(){
        if (revoked) {
            cout << "Your membership was revoked. Contact the mess authority to rejoin.\n";
            return;
        }
        cout << "Your account is currently " << (active_status ? "Active" : "Inactive") << ".\n";
        string action = active_status ? "Deactivate" : "Activate";
        if (readInt("Would you like to " + action + "? Yes(1) / No(0): ", 0, 1) == 1) {
            active_status = !active_status;
            cout << "Changes saved. Account is now "<< (active_status ? "Active" : "Inactive") << ".\n";
        } 
        else {
            cout << "No changes made.\n";
        }
    } //only able to eat meal if status is active
    void view_details(){
        cout << "\n========== STUDENT DETAILS ==========\n";
        cout<< "Enrollment Number : " << Enrollment_no << '\n';
        cout<< "Student Name      : " << Student_name << '\n';
        cout<< "Membership Status : " << (revoked ? "Revoked" : active_status ? "Active" : "Inactive") << '\n';
        cout<< "Total Meals Eaten : " << MealsEaten << '\n';
        cout<< "Total Due Bill    : Rs. " << Due_amount << '\n';
        cout<< "Latest Feedback   : " << (feedback.empty() ? "No feedback given yet" : feedback) << '\n';
        cout<< "=====================================\n";
    }
    
    void pay_bill(){
        if (Due_amount <= 0) {
            cout << "\nNo pending dues! Your bill is already clear.\n";
            return;
        }
        cout << "\nYour current pending bill is: Rs. " << Due_amount << '\n';
        int amount = readInt("Enter amount to pay: Rs. ", 1, numeric_limits<int>::max());
 
        if (amount > Due_amount) {
            cout << "Amount exceeds due bill. Paying exact due of Rs. " << Due_amount << " instead.\n";
            amount = static_cast<int>(Due_amount);   // see note: use paise/int for money if you want exactness
        }
        Due_amount -= amount;
        cout << "Payment successful! Remaining Due: Rs. " << Due_amount << '\n';
    }

    
    void Revoke_membership(){
    if (revoked) {
        cout << "Membership is already revoked.\n";
        return;
    }
    if (Due_amount > 0) {
        cout << "Cannot revoke membership with pending dues of Rs. " << Due_amount
             << ". Please pay your bill first.\n";
        return;
    }
    cout << "Revoking means you leave the mess permanently.\n";
    if (readInt("Are you sure? Yes(1) / No(0): ", 0, 1) == 1) {
        revoked = true;
        active_status = false;
        //remove_student()
        cout << "Your membership has been revoked.\n";
    } else {
        cout << "Cancelled. Membership unchanged.\n";
    }
}
    void mark_attendence(meal &m); //count meals ate
    void view_menu(menu& men);
    
};

class meal
{
    string mealType; //Breakfast, lunch or dinner
    vector<string> foodItems;
    double price; 
    friend class MessAuthority;
    int quantityPrepared;
    int quantityConsumed;

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

void student::mark_attendence(meal& m) {
    if (revoked || !active_status) {
        cout << "Your account is not active, so you cannot eat a meal. Activate it first.\n";
        return;
    }
    MealsEaten++;
    Due_amount += m.getPrice();
    //m.recordConsumption();
    //cout << "Attendance marked for " << m.getMealType()//---------------------------------------------------------->>>>>>>
         //<< ". Rs. " << m.getPrice() << " added to your bill.\n";
}

void student::view_menu(menu& mn){
    const auto& schedule = mn.getWeeklySchedule();
    if (schedule.empty()) {
        cout << "Menu has not been set yet.\n";
        return;
    }
    cout << "\n========== WEEKLY MENU ==========\n";
    for (const auto& day : schedule) {
        cout << "\nDay: " << day.first << '\n';
        for (const auto& m : day.second) {
            //m.displayMeal();----------------------------------------------------------------------->>>>>>>>>>>>>>>
            cout << "-----------------------------\n";
        }
    }
}



class MessAuthority{
    string authorityName;
    string authorityID;
    vector<student>students; //list of all the students//----------------->> make static???? as it is used in revoke function
    menu messMenu;    //Authority can access the mess menu

    public:
    MessAuthority(string name, string id, int menuId) : authorityName(name), authorityID(id), messMenu(menuId){};
    void addMeal(){

    string day, type, item;
    vector<string> foodItems;
    double price;
    int n;

    cout << "Enter day: ";
    cin >> day;

    cout << "Enter meal type: ";
    cin >> type;

    cout << "Enter number of food items: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Enter food item: ";
        cin >> item;
        foodItems.push_back(item);
    }

    cout << "Enter price: ";
    cin >> price;

    for (int i = 0; i < messMenu.weeklySchedule.size(); i++) {
        if (messMenu.weeklySchedule[i].first == day) {
            messMenu.weeklySchedule[i].second.push_back(meal(type, foodItems, price));
            cout << "Meal added successfully!";
            return;
        }
    }

    cout << "Day not found!";
    }
    void removeMeal(){
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
    void updateMeal(){
        string day, type, item;
    vector<string> foodItems;
    double price;
    int n;

    cout << "Enter day: ";
    cin >> day;

    cout << "Enter meal type to update: ";
    cin >> type;

    for (int i = 0; i < messMenu.weeklySchedule.size(); i++) {

        if (messMenu.weeklySchedule[i].first == day) {

            for (int j = 0; j < messMenu.weeklySchedule[i].second.size(); j++) {

                if (messMenu.weeklySchedule[i].second[j].mealType == type) {

                    cout << "Enter number of new food items: ";
                    cin >> n;

                    foodItems.clear();

                    for (int k = 0; k < n; k++) {
                        cout << "Enter food item: ";
                        cin >> item;
                        foodItems.push_back(item);
                    }

                    cout << "Enter new price: ";
                    cin >> price;

                    messMenu.weeklySchedule[i].second[j].foodItems = foodItems;
                    messMenu.weeklySchedule[i].second[j].price = price;

                    cout << "Meal updated successfully!";
                    return;
                }
            }

            cout << "Meal not found!";
            return;
        }
    }

    cout << "Day not found!";

    }
    void viewMenu(){
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
    void addStudents(){
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
    void removeStudents(){

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
    void viewStudents(){
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
    void viewFeedback(){
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
    void generateWasteReport(){
    int totalPrepared = 0;
    int totalConsumed = 0;
    int totalWasted = 0;

    for (int i = 0; i < messMenu.weeklySchedule.size(); i++) {

        for (int j = 0; j < messMenu.weeklySchedule[i].second.size(); j++) {

            totalPrepared += messMenu.weeklySchedule[i].second[j].quantityPrepared;

            totalConsumed += messMenu.weeklySchedule[i].second[j].quantityConsumed;
        }
    }

    totalWasted = totalPrepared - totalConsumed;

    cout << "\n========== WASTE REPORT ==========\n";

    cout << "Total Food Prepared: " << totalPrepared << " plates\n";
    cout << "Total Food Consumed: " << totalConsumed << " plates\n";
    cout << "Total Food Wasted: " << totalWasted << " plates\n";

    cout << "==================================\n";
    }

    void generateStudentsReport(){
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
};


int main(){
    return 0;
}

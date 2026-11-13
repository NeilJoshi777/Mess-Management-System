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
    meal(string type, vector<string> items, double p, int prepared = 0);
    
    void setQuantityPrepared(int quantity);
    bool recordConsumption() {
        if (quantityConsumed >= quantityPrepared)
        {
            cout << "Sorry! This meal is out of stock.\n";
            return false;
        }

        quantityConsumed++;

        return true;
}

    int getQuantityPrepared() const{
        return quantityPrepared;
}

    int getQuantityConsumed() const{
        return quantityConsumed;
} 
    
    void addFoodItems() {
        int n;
        string item;

        n = readInt("How many food items do you want to add? ", 1, 50);

        for (int i = 0; i < n; i++)
        {
            cout << "Enter food item " << i + 1 << ": ";

            cin >> ws;
            getline(cin, item);

            foodItems.push_back(item);
        }

        cout << "Food items added successfully!\n";
    }
    
    void removeFoodItems() {
        if (foodItems.empty())
        {
            cout << "No food items available to remove.\n";
            return;
        }

        string item;

        cout << "\nCurrent food items:\n";

        for (int i = 0; i < foodItems.size(); i++)
        {
            cout << i + 1 << ". " << foodItems[i] << '\n';
        }

        cout << "Enter the name of the food item to remove: ";

        cin >> ws;
        getline(cin, item);

        auto it = find(foodItems.begin(), foodItems.end(), item);

        if (it != foodItems.end())
        {
            foodItems.erase(it);
            cout << "Food item removed successfully!\n";
        }
        else
        {
            cout << "Food item not found!\n";
        }
}
    
    void setPrice() {
        double newPrice;

        while (true)
        {
            cout << "Enter new meal price: Rs. ";

            if (cin >> newPrice && newPrice >= 0)
            {
                price = newPrice;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Price updated successfully!\n";
                return;
            }

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid price! Enter a non-negative number.\n";
        }
}

    double getPrice() const{
        return price;
}
    
    void displayMeal() const{
        cout << "\nMeal Type: " << mealType;

        cout << "\nFood Items: ";

        for (int i = 0; i < foodItems.size(); i++)
        {
            cout << foodItems[i];

            if (i != foodItems.size() - 1)
                cout << ", ";
        }

        cout << "\nPrice: Rs. " << price;

        cout << "\nQuantity Prepared: " << quantityPrepared;

        cout << "\nQuantity Consumed: " << quantityConsumed;

        cout << "\nQuantity Remaining: "
            << quantityPrepared - quantityConsumed << '\n';

        cout << "-----------------------------\n";
}

};

meal::meal(string type, vector<string> items, double p, int prepared) {       
    mealType = type;
    foodItems = items;
    price = p;

    quantityPrepared = prepared;
    quantityConsumed = 0;
}

void meal::setQuantityPrepared(int quantity)
{
    if (quantity < quantityConsumed)
    {
        cout << "Prepared quantity cannot be less than "
             << "already consumed quantity.\n";
        return;
    }

    quantityPrepared = quantity;
    cout << "Prepared quantity updated successfully!\n";
}

class menu
{
    int menuID;
    vector<pair<string, vector<meal>>> weeklySchedule; // Will contain whole menu
    friend class MessAuthority;

    public:
    menu(int id) {
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
    
    void setMealsForDay() {
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

    const vector<pair<string, vector<meal>>>& getWeeklySchedule() const{
        return weeklySchedule;
}       // Returns schedule for a week

    vector<meal>* getMealsForDay(const string& day) {
        for (int i = 0; i < weeklySchedule.size(); i++)
        {
            if (weeklySchedule[i].first == day)
            {
                return &weeklySchedule[i].second;
            }
        }

        return nullptr;
}        // Returns schedule of a day

};    

void student::mark_attendence(meal& m)
{
    if (revoked || !active_status)
    {
        cout << "Your account is inactive or revoked. "
             << "You cannot eat a meal.\n";
        return;
    }

    // First check whether a plate is available
    if (!m.recordConsumption())
    {
        return;
    }

    // Record attendance only if consumption succeeds
    MealsEaten++;

    // Add meal price to student's pending bill
    Due_amount += static_cast<int>(m.getPrice());

    cout << "Attendance marked successfully!\n";
    cout << "Meal price added: Rs. " << m.getPrice() << '\n';
    cout << "Total pending bill: Rs. " << Due_amount << '\n';
}

void student::view_menu(menu& mn)
{
    const auto& schedule = mn.getWeeklySchedule();

    if (schedule.empty())
    {
        cout << "Menu has not been set yet.\n";
        return;
    }

    cout << "\n========== WEEKLY MENU ==========\n";

    for (const auto& day : schedule)
    {
        cout << "\nDay: " << day.first << '\n';

        if (day.second.empty())
        {
            cout << "No meals added for this day.\n";
            continue;
        }

        for (const auto& m : day.second)
        {
            m.displayMeal();
        }
    }
}



class MessAuthority{
    string authorityName;
    string authorityID;
    vector<student>students; //list of all the students
    menu messMenu;    //Authority can access the mess menu

    public:
    MessAuthority(string name, string id, int menuId) : authorityName(name), authorityID(id), messMenu(menuId){};
    // Find a student by enrollment number (returns nullptr if not found)
   student* findStudent(long int enrollment) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i].Enrollment_no == enrollment)
            return &students[i];
    }
    return nullptr;
}

// Lets a student view the menu / pick a meal
   menu& getMenu() {
    return messMenu;
}
    void addMeal()
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
    void updateMeal()
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
    void generateWasteReport()
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
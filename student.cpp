#include "student.h"
#include "meal.h"   // Include full definitions here
#include "menu.h"   
#include "utils.h"  // For readInt
#include <limits>

using namespace std;

student::student(long int enrollment, string name) {
    Enrollment_no = enrollment;
    Student_name = name;
    active_status = true;
    Due_amount = 0;
    MealsEaten =0;
    feedback= "";
    revoked = false;
    
}
void student::Give_feedback(){
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
    
    void student::update_active_status(){
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
    void student::view_details(){
        cout << "\n========== STUDENT DETAILS ==========\n";
        cout<< "Enrollment Number : " << Enrollment_no << '\n';
        cout<< "Student Name      : " << Student_name << '\n';
        cout<< "Membership Status : " << (revoked ? "Revoked" : active_status ? "Active" : "Inactive") << '\n';
        cout<< "Total Meals Eaten : " << MealsEaten << '\n';
        cout<< "Total Due Bill    : Rs. " << Due_amount << '\n';
        cout<< "Latest Feedback   : " << (feedback.empty() ? "No feedback given yet" : feedback) << '\n';
        cout<< "=====================================\n";
    }
    
    void student::pay_bill(){
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

    
    void student::Revoke_membership(){
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
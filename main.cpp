#include<iostream>
using namespace std;

class MessAuthority{
    string authorityName;
    string authorityID;

    public:
    void addMeal();
    void removeMeal();
    void updateMeal();
    void viewMenu();
    void addStudents();
    void removeStudents();
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



int main(){
    return 0;
}
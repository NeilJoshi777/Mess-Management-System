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
    void generateStudentsReport();
};


class student{
    protected:
    long int Enrollment_no;
    string Student_name;
    
    public:

    void Give_feedback();
    void update_active_status();
    void view_bill();
    void pay_bill();

};



int main(){
    return 0;
}
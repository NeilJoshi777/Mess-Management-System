#pragma once
#include <string>
#include <iostream>

class meal; // Forward declarations to avoid circular dependencies
class menu;
class MessAuthority;

class student {
protected:
    long int Enrollment_no;
    std::string Student_name;
    bool active_status;
    int Due_amount;
    std::string feedback;
    int MealsEaten;
    bool revoked;

public:
    friend class MessAuthority;
    student(long int enrollment, std::string name);
    void Give_feedback();
    void update_active_status();
    void view_details();
    void pay_bill();
    void Revoke_membership();
    void mark_attendence(meal &m);
    void view_menu(menu& men);
};
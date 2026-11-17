#pragma once
#include <string>
#include <iostream>

class meal; // Forward declarations to avoid circular dependencies
class menu;
class MessAuthority;

// =====================================================================
//  BASE CLASS : student   (abstract)
//  Pure virtual  -> getStudentType(), getDiscountRate()
//  Virtual       -> calculateCharge(), view_details(), printExtraDetails()
//  Derived       -> HostelStudent, DayScholar, ScholarshipStudent
// =====================================================================
class student {
protected:
    long int Enrollment_no;
    std::string Student_name;
    bool active_status;
    int Due_amount;
    int TotalBilled;
    std::string feedback;
    int MealsEaten;
    bool revoked;

    // Hook used by view_details(); derived classes print their own extra lines.
    virtual void printExtraDetails() const {}

public:
    friend class MessAuthority;
    student(long int enrollment, std::string name);
    virtual ~student() = default;

    // ---- polymorphic interface ----
    virtual std::string getStudentType() const = 0;
    virtual double getDiscountRate() const = 0;          // 0.10 means 10% off
    virtual int calculateCharge(double mealPrice) const; // bill amount for one meal
    virtual void view_details();

    // ---- common behaviour ----
    void Give_feedback();
    void update_active_status();
    void pay_bill();
    void Revoke_membership();
    void mark_attendence(meal &m);   // takes base reference -> runtime polymorphism
    void view_menu(menu& men);

    // ---- getters (used by the Report classes) ----
    long int getEnrollment() const { return Enrollment_no; }
    const std::string& getName() const { return Student_name; }
    bool isActive() const { return active_status; }
    bool isRevoked() const { return revoked; }
    int getDue() const { return Due_amount; }
    int getTotalBilled() const { return TotalBilled; }
    int getMealsEaten() const { return MealsEaten; }
};

// ---------------------------------------------------------------------
//  DERIVED CLASS 1 : HostelStudent  - resident, 10% discount
// ---------------------------------------------------------------------
class HostelStudent : public student {
    std::string roomNumber;
protected:
    void printExtraDetails() const override;
public:
    HostelStudent(long int enrollment, std::string name, std::string room);
    std::string getStudentType() const override;
    double getDiscountRate() const override;
};

// ---------------------------------------------------------------------
//  DERIVED CLASS 2 : DayScholar - pays the full price
// ---------------------------------------------------------------------
class DayScholar : public student {
    std::string homeCity;
protected:
    void printExtraDetails() const override;
public:
    DayScholar(long int enrollment, std::string name, std::string city);
    std::string getStudentType() const override;
    double getDiscountRate() const override;
};

// ---------------------------------------------------------------------
//  DERIVED CLASS 3 : ScholarshipStudent - custom discount %
// ---------------------------------------------------------------------
class ScholarshipStudent : public student {
    std::string scholarshipName;
    int discountPercent;
protected:
    void printExtraDetails() const override;
public:
    ScholarshipStudent(long int enrollment, std::string name,
                       std::string scholarship, int percent);
    std::string getStudentType() const override;
    double getDiscountRate() const override;
};

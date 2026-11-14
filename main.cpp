#include <iostream>
#include "MessAuthority.h"
#include "student.h"
#include "utils.h"

using namespace std;

int main(){
    MessAuthority authority("Mess Manager", "MA001", 1);
    int role;

    do {
        cout << "\n====== MESS MANAGEMENT SYSTEM ======\n";
        cout << "1. Student\n";
        cout << "2. Mess Authority\n";
        cout << "0. Exit\n";
        role = readInt("Are you a Student or Mess Authority? Enter choice: ", 0, 2);

        // ---------------- STUDENT ----------------
        if (role == 1) {
            long int enrollment;
            cout << "\nEnter your Enrollment Number: ";
            cin >> enrollment;

            student* s = authority.findStudent(enrollment);
            if (s == nullptr) {
                cout << "Student not found! Ask the mess authority to register you.\n";
                continue;
            }

            int choice;
            do {
                cout << "\n------ STUDENT MENU ------\n";
                cout << "1. View my details\n";
                cout << "2. View weekly menu\n";
                cout << "3. Eat a meal (mark attendance)\n";
                cout << "4. Pay bill\n";
                cout << "5. Give feedback\n";
                cout << "6. Activate / Deactivate account\n";
                cout << "7. Revoke membership\n";
                cout << "0. Back\n";
                choice = readInt("Enter choice: ", 0, 7);

                switch (choice) {
                    case 1:
                        s->view_details();
                        break;
                    case 2:
                        s->view_menu(authority.getMenu());
                        break;
                    case 3: {
                        string day;
                        cout << "Enter day (e.g. Monday): ";
                        cin >> day;

                        vector<meal>* meals = authority.getMenu().getMealsForDay(day);
                        if (meals == nullptr) {
                            cout << "Invalid day!\n";
                            break;
                        }
                        if (meals->empty()) {
                            cout << "No meals available on " << day << ".\n";
                            break;
                        }

                        for (int i = 0; i < meals->size(); i++) {
                            cout << "\nOption " << i + 1;
                            (*meals)[i].displayMeal();
                        }

                        int pick = readInt("Choose meal number: ", 1, meals->size());
                        s->mark_attendence((*meals)[pick - 1]);
                        break;
                    }
                    case 4:
                        s->pay_bill();
                        break;
                    case 5:
                        s->Give_feedback();
                        break;
                    case 6:
                        s->update_active_status();
                        break;
                    case 7:
                        s->Revoke_membership();
                        break;
                    case 0:
                        cout << "Returning to main menu...\n";
                        break;
                }
            } while (choice != 0);
        }

        // ---------------- MESS AUTHORITY ----------------
        else if (role == 2) {
            int choice;
            do {
                cout << "\n------ AUTHORITY MENU ------\n";
                cout << "1. Add meal\n";
                cout << "2. Remove meal\n";
                cout << "3. Update meal\n";
                cout << "4. View menu\n";
                cout << "5. Add student\n";
                cout << "6. Remove student\n";
                cout << "7. View all students\n";
                cout << "8. View feedback\n";
                cout << "9. Waste report\n";
                cout << "10. Student report\n";
                cout << "0. Back\n";
                choice = readInt("Enter choice: ", 0, 10);

                switch (choice) {
                    case 1:  authority.addMeal();               break;
                    case 2:  authority.removeMeal();            break;
                    case 3:  authority.updateMeal();            break;
                    case 4:  authority.viewMenu();              break;
                    case 5:  authority.addStudents();           break;
                    case 6:  authority.removeStudents();        break;
                    case 7:  authority.viewStudents();          break;
                    case 8:  authority.viewFeedback();          break;
                    case 9:  authority.generateWasteReport();   break;
                    case 10: authority.generateStudentsReport();break;
                    case 0:
                        cout << "Returning to main menu...\n";
                        break;
                }
            } while (choice != 0);
        }

    } while (role != 0);

    cout << "\nThank you for using the Mess Management System!\n";
    return 0;
}
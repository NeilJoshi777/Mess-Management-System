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
int main(){
    return 0;
}
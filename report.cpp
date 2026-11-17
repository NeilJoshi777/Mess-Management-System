#include "report.h"
#include <iostream>
#include <map>
using namespace std;

// ====================== BASE CLASS : Report ======================

void Report::printHeader() const {
    cout << "\n========== " << getTitle() << " ==========\n";   // virtual call
}

void Report::printFooter() const {
    cout << string(getTitle().size() + 22, '=') << '\n';
}

// ====================== WasteReport ======================

WasteReport::WasteReport(const menu& m) : messMenu(m) {}

string WasteReport::getTitle() const { return "WASTE REPORT"; }

void WasteReport::generate() const {
    int totalPrepared = 0;
    int totalConsumed = 0;
    vector<string> flagged;

    for (const auto& day : messMenu.getWeeklySchedule()) {
        for (const auto& m : day.second) {
            int prepared = m->getQuantityPrepared();
            int consumed = m->getQuantityConsumed();
            totalPrepared += prepared;
            totalConsumed += consumed;

            if (prepared > 0) {
                double wastePct = 100.0 * (prepared - consumed) / prepared;
                // threshold differs for each meal type (virtual call)
                if (wastePct > m->getWasteThresholdPercent()) {
                    flagged.push_back(day.first + " " + m->getCategory() + ": "
                        + to_string((int)wastePct) + "% wasted (limit "
                        + to_string((int)m->getWasteThresholdPercent()) + "%)");
                }
            }
        }
    }

    printHeader();
    cout << "Total Food Prepared: " << totalPrepared << " plates\n";
    cout << "Total Food Consumed: " << totalConsumed << " plates\n";
    cout << "Total Food Wasted: " << totalPrepared - totalConsumed << " plates\n";

    if (flagged.empty()) {
        cout << "All meals are within their waste limits.\n";
    } else {
        cout << "\nMeals above their waste limit:\n";
        for (const auto& line : flagged)
            cout << "  [HIGH WASTE] " << line << '\n';
    }
    printFooter();
}

// ====================== StudentReport ======================

StudentReport::StudentReport(const vector<unique_ptr<student>>& s) : students(s) {}

string StudentReport::getTitle() const { return "STUDENT REPORT"; }

void StudentReport::generate() const {
    int active = 0, inactive = 0, totalDue = 0;
    map<string, int> byType;

    for (const auto& s : students) {
        if (s->isActive()) active++; else inactive++;
        totalDue += s->getDue();
        byType[s->getStudentType()]++;       // virtual call
    }

    printHeader();
    cout << "Total Students: " << students.size() << endl;
    cout << "Active Students: " << active << endl;
    cout << "Inactive Students: " << inactive << endl;
    for (const auto& entry : byType)
        cout << "  " << entry.first << "s: " << entry.second << endl;
    cout << "Total Outstanding Dues: Rs. " << totalDue << endl;
    printFooter();
}

// ====================== FinancialReport ======================

FinancialReport::FinancialReport(const vector<unique_ptr<student>>& s) : students(s) {}

string FinancialReport::getTitle() const { return "FINANCIAL REPORT"; }

void FinancialReport::generate() const {
    int billed = 0, pending = 0;
    for (const auto& s : students) {
        billed += s->getTotalBilled();
        pending += s->getDue();
    }

    printHeader();
    cout << "Total Billed: Rs. " << billed << endl;
    cout << "Total Collected: Rs. " << billed - pending << endl;
    cout << "Total Pending: Rs. " << pending << endl;
    printFooter();
}

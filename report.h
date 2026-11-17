#pragma once
#include <string>
#include <vector>
#include <memory>
#include "menu.h"
#include "student.h"

// =====================================================================
//  BASE CLASS : Report   (abstract)
//  Pure virtual -> getTitle(), generate()
//  Derived      -> WasteReport, StudentReport, FinancialReport
// =====================================================================
class Report {
protected:
    void printHeader() const;
    void printFooter() const;
public:
    virtual ~Report() = default;
    virtual std::string getTitle() const = 0;
    virtual void generate() const = 0;
};

// Reports food prepared vs consumed, and flags meals that waste too much.
class WasteReport : public Report {
    const menu& messMenu;
public:
    explicit WasteReport(const menu& m);
    std::string getTitle() const override;
    void generate() const override;
};

// Reports student counts (by status and by student type) and total dues.
class StudentReport : public Report {
    const std::vector<std::unique_ptr<student>>& students;
public:
    explicit StudentReport(const std::vector<std::unique_ptr<student>>& s);
    std::string getTitle() const override;
    void generate() const override;
};

// Reports money billed, collected and still pending.
class FinancialReport : public Report {
    const std::vector<std::unique_ptr<student>>& students;
public:
    explicit FinancialReport(const std::vector<std::unique_ptr<student>>& s);
    std::string getTitle() const override;
    void generate() const override;
};

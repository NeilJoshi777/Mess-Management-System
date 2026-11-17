#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <memory>

class MessAuthority;

// =====================================================================
//  BASE CLASS : meal   (abstract)
//  Pure virtual  -> getCategory(), getServingTime()
//  Virtual       -> getPrice(), getWasteThresholdPercent(), displayMeal()
//  Derived       -> Breakfast, Lunch, Dinner, SpecialMeal
// =====================================================================
class meal {
protected:
    std::vector<std::string> foodItems;
    double price;               // base price (derived classes may adjust the final price)
    int quantityPrepared;
    int quantityConsumed;

    static void printSeparator();

    friend class MessAuthority;

public:
    meal(std::vector<std::string> items, double p, int prepared = 0);
    virtual ~meal() = default;   // virtual destructor: safe delete through base pointer

    // ---- polymorphic interface ----
    virtual std::string getCategory() const = 0;      // "Breakfast", "Lunch", ...
    virtual std::string getServingTime() const = 0;   // time slot of this meal
    virtual double getPrice() const;                  // final price charged (base: plain price)
    virtual double getWasteThresholdPercent() const;  // acceptable % of food wasted
    virtual void displayMeal() const;                 // print meal details

    // ---- common (non-virtual) behaviour ----
    void setQuantityPrepared(int quantity);
    bool recordConsumption();
    int getQuantityPrepared() const;
    int getQuantityConsumed() const;
    void addFoodItems();
    void removeFoodItems();
    void setPrice();
};

// ---------------------------------------------------------------------
//  DERIVED CLASS 1 : Breakfast
// ---------------------------------------------------------------------
class Breakfast : public meal {
public:
    Breakfast(std::vector<std::string> items, double p, int prepared = 0);
    std::string getCategory() const override;
    std::string getServingTime() const override;
    double getWasteThresholdPercent() const override;
    void displayMeal() const override;
};

// ---------------------------------------------------------------------
//  DERIVED CLASS 2 : Lunch
// ---------------------------------------------------------------------
class Lunch : public meal {
public:
    Lunch(std::vector<std::string> items, double p, int prepared = 0);
    std::string getCategory() const override;
    std::string getServingTime() const override;
    double getWasteThresholdPercent() const override;
    void displayMeal() const override;
};

// ---------------------------------------------------------------------
//  DERIVED CLASS 3 : Dinner
// ---------------------------------------------------------------------
class Dinner : public meal {
public:
    Dinner(std::vector<std::string> items, double p, int prepared = 0);
    std::string getCategory() const override;
    std::string getServingTime() const override;
    double getWasteThresholdPercent() const override;
    void displayMeal() const override;
};

// ---------------------------------------------------------------------
//  DERIVED CLASS 4 : SpecialMeal  (festival / feast, costs extra)
// ---------------------------------------------------------------------
class SpecialMeal : public meal {
    std::string occasion;
    double surchargePercent;
public:
    SpecialMeal(std::vector<std::string> items, double p, int prepared,
                std::string occasionName, double surcharge);
    std::string getCategory() const override;
    std::string getServingTime() const override;
    double getPrice() const override;                 // base price + surcharge
    double getWasteThresholdPercent() const override; // stricter: special food is costly
    void displayMeal() const override;
};

// Asks the authority for meal details and returns the right derived object
// (as a base-class pointer). Returns nullptr if nothing was created.
std::unique_ptr<meal> promptAndCreateMeal();

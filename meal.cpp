#include "meal.h"
#include "utils.h"
#include <limits>
#include <algorithm>
#include <string>
using namespace std;

// ====================== BASE CLASS : meal ======================

meal::meal(vector<string> items, double p, int prepared) {
    foodItems = items;
    price = p;
    quantityPrepared = prepared;
    quantityConsumed = 0;
}

void meal::printSeparator() {
    cout << "-----------------------------\n";
}

double meal::getPrice() const {
    return price;
}

double meal::getWasteThresholdPercent() const {
    return 15.0;
}

// Prints the details every meal has. Derived classes call this and add their own lines.
void meal::displayMeal() const {
    cout << "\nMeal Type: " << getCategory();           // virtual call
    cout << "\nServing Time: " << getServingTime();     // virtual call

    cout << "\nFood Items: ";
    for (size_t i = 0; i < foodItems.size(); i++) {
        cout << foodItems[i];
        if (i != foodItems.size() - 1)
            cout << ", ";
    }

    cout << "\nPrice: Rs. " << getPrice();              // virtual call

    cout << "\nQuantity Prepared: " << quantityPrepared;
    cout << "\nQuantity Consumed: " << quantityConsumed;
    cout << "\nQuantity Remaining: " << quantityPrepared - quantityConsumed << '\n';
}

void meal::setQuantityPrepared(int quantity) {
    if (quantity < quantityConsumed) {
        cout << "Prepared quantity cannot be less than "
             << "already consumed quantity.\n";
        return;
    }
    quantityPrepared = quantity;
    cout << "Prepared quantity updated successfully!\n";
}

bool meal::recordConsumption() {
    if (quantityConsumed >= quantityPrepared) {
        cout << "Sorry! This meal is out of stock.\n";
        return false;
    }
    quantityConsumed++;
    return true;
}

int meal::getQuantityPrepared() const { return quantityPrepared; }
int meal::getQuantityConsumed() const { return quantityConsumed; }

void meal::addFoodItems() {
    int n;
    string item;

    n = readInt("How many food items do you want to add? ", 1, 50);

    for (int i = 0; i < n; i++) {
        cout << "Enter food item " << i + 1 << ": ";
        cin >> ws;
        getline(cin, item);
        foodItems.push_back(item);
    }
    cout << "Food items added successfully!\n";
}

void meal::removeFoodItems() {
    if (foodItems.empty()) {
        cout << "No food items available to remove.\n";
        return;
    }

    string item;
    cout << "\nCurrent food items:\n";
    for (size_t i = 0; i < foodItems.size(); i++)
        cout << i + 1 << ". " << foodItems[i] << '\n';

    cout << "Enter the name of the food item to remove: ";
    cin >> ws;
    getline(cin, item);

    auto it = find(foodItems.begin(), foodItems.end(), item);
    if (it != foodItems.end()) {
        foodItems.erase(it);
        cout << "Food item removed successfully!\n";
    } else {
        cout << "Food item not found!\n";
    }
}

void meal::setPrice() {
    double newPrice;
    while (true) {
        cout << "Enter new meal price: Rs. ";
        if (cin >> newPrice && newPrice >= 0) {
            price = newPrice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Price updated successfully!\n";
            return;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid price! Enter a non-negative number.\n";
    }
}

// ====================== DERIVED : Breakfast ======================

Breakfast::Breakfast(vector<string> items, double p, int prepared)
    : meal(items, p, prepared) {}

string Breakfast::getCategory() const { return "Breakfast"; }
string Breakfast::getServingTime() const { return "7:30 AM - 9:30 AM"; }
double Breakfast::getWasteThresholdPercent() const { return 10.0; }

void Breakfast::displayMeal() const {
    meal::displayMeal();
    cout << "Note: Light morning meal, served hot.\n";
    printSeparator();
}

// ====================== DERIVED : Lunch ======================

Lunch::Lunch(vector<string> items, double p, int prepared)
    : meal(items, p, prepared) {}

string Lunch::getCategory() const { return "Lunch"; }
string Lunch::getServingTime() const { return "12:30 PM - 2:30 PM"; }
double Lunch::getWasteThresholdPercent() const { return 15.0; }

void Lunch::displayMeal() const {
    meal::displayMeal();
    cout << "Note: Full thali meal.\n";
    printSeparator();
}

// ====================== DERIVED : Dinner ======================

Dinner::Dinner(vector<string> items, double p, int prepared)
    : meal(items, p, prepared) {}

string Dinner::getCategory() const { return "Dinner"; }
string Dinner::getServingTime() const { return "7:30 PM - 9:30 PM"; }
double Dinner::getWasteThresholdPercent() const { return 12.0; }

void Dinner::displayMeal() const {
    meal::displayMeal();
    cout << "Note: Evening meal.\n";
    printSeparator();
}

// ====================== DERIVED : SpecialMeal ======================

SpecialMeal::SpecialMeal(vector<string> items, double p, int prepared,
                         string occasionName, double surcharge)
    : meal(items, p, prepared), occasion(occasionName), surchargePercent(surcharge) {}

string SpecialMeal::getCategory() const { return "Special"; }
string SpecialMeal::getServingTime() const { return "8:00 PM - 10:00 PM"; }

// Overridden: special meals cost the base price plus a surcharge.
double SpecialMeal::getPrice() const {
    return price + price * surchargePercent / 100.0;
}

double SpecialMeal::getWasteThresholdPercent() const { return 5.0; }

void SpecialMeal::displayMeal() const {
    meal::displayMeal();
    cout << "Occasion: " << occasion << " (includes " << surchargePercent
         << "% special surcharge)\n";
    printSeparator();
}

// ====================== Factory ======================

static double readPrice() {
    double price;
    while (true) {
        cout << "Enter price: Rs. ";
        if (cin >> price && price >= 0)
            return price;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid price!\n";
    }
}

unique_ptr<meal> promptAndCreateMeal() {
    cout << "\nSelect meal type:\n";
    cout << "1. Breakfast\n2. Lunch\n3. Dinner\n4. Special (festival / feast)\n";
    int category = readInt("Enter choice: ", 1, 4);

    int itemCount = readInt("Enter number of food items: ", 1, 50);
    vector<string> items;
    for (int i = 0; i < itemCount; i++) {
        string item;
        cout << "Enter food item: ";
        cin >> ws;
        getline(cin, item);
        items.push_back(item);
    }

    double price = readPrice();
    int prepared = readInt("Enter quantity prepared: ", 0, 100000);

    // The derived object is created here, but callers only ever see a meal*.
    switch (category) {
        case 1: return make_unique<Breakfast>(items, price, prepared);
        case 2: return make_unique<Lunch>(items, price, prepared);
        case 3: return make_unique<Dinner>(items, price, prepared);
        default: {
            string occasion;
            cout << "Enter occasion name (e.g. Diwali Feast): ";
            cin >> ws;
            getline(cin, occasion);
            int surcharge = readInt("Enter special surcharge % (0-100): ", 0, 100);
            return make_unique<SpecialMeal>(items, price, prepared, occasion, surcharge);
        }
    }
}

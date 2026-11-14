#include "meal.h"
#include "utils.h" 
#include <limits>
#include <algorithm>
#include<string>
using namespace std;

    meal::meal(string type, vector<string> items, double p, int prepared) {       
        mealType = type;
        foodItems = items;
        price = p;
        quantityPrepared = prepared;
        quantityConsumed = 0;
    }
    
    void meal::setQuantityPrepared(int quantity){
        if (quantity < quantityConsumed)
        {
            cout << "Prepared quantity cannot be less than "
                << "already consumed quantity.\n";
            return;
        }

        quantityPrepared = quantity;
        cout << "Prepared quantity updated successfully!\n";
    }
    bool meal::recordConsumption() {
        if (quantityConsumed >= quantityPrepared)
        {
            cout << "Sorry! This meal is out of stock.\n";
            return false;
        }

        quantityConsumed++;

        return true;
    }

    int meal::getQuantityPrepared() const{
        return quantityPrepared;
    }

    int meal::getQuantityConsumed() const{
        return quantityConsumed;
    } 
    
    void meal::addFoodItems() {
        int n;
        string item;

        n = readInt("How many food items do you want to add? ", 1, 50);

        for (int i = 0; i < n; i++)
        {
            cout << "Enter food item " << i + 1 << ": ";

            cin >> ws;
            getline(cin, item);

            foodItems.push_back(item);
        }

        cout << "Food items added successfully!\n";
    }
    
    void meal::removeFoodItems() {
        if (foodItems.empty())
        {
            cout << "No food items available to remove.\n";
            return;
        }

        string item;

        cout << "\nCurrent food items:\n";

        for (int i = 0; i < foodItems.size(); i++)
        {
            cout << i + 1 << ". " << foodItems[i] << '\n';
        }

        cout << "Enter the name of the food item to remove: ";

        cin >> ws;
        getline(cin, item);

        auto it = find(foodItems.begin(), foodItems.end(), item);

        if (it != foodItems.end())
        {
            foodItems.erase(it);
            cout << "Food item removed successfully!\n";
        }
        else
        {
            cout << "Food item not found!\n";
        }
    }
    
    void meal::setPrice() {
        double newPrice;

        while (true)
        {
            cout << "Enter new meal price: Rs. ";

            if (cin >> newPrice && newPrice >= 0)
            {
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

    double meal::getPrice() const{
        return price;
    }
    
    void meal::displayMeal() const{
        cout << "\nMeal Type: " << mealType;

        cout << "\nFood Items: ";

        for (int i = 0; i < foodItems.size(); i++)
        {
            cout << foodItems[i];

            if (i != foodItems.size() - 1)
                cout << ", ";
        }

        cout << "\nPrice: Rs. " << price;

        cout << "\nQuantity Prepared: " << quantityPrepared;

        cout << "\nQuantity Consumed: " << quantityConsumed;

        cout << "\nQuantity Remaining: "
            << quantityPrepared - quantityConsumed << '\n';

        cout << "-----------------------------\n";
    }

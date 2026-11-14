#pragma once
#include <string>
#include <vector>
#include <iostream>

class MessAuthority; 

class meal {
    std::string mealType;
    std::vector<std::string> foodItems;
    double price;
    int quantityPrepared;
    int quantityConsumed;

    friend class MessAuthority;

public:
    meal(std::string type, std::vector<std::string> items, double p, int prepared = 0);
    void setQuantityPrepared(int quantity);
    bool recordConsumption();
    int getQuantityPrepared() const;
    int getQuantityConsumed() const;
    void addFoodItems();
    void removeFoodItems();
    void setPrice();
    double getPrice() const;
    void displayMeal() const;
};
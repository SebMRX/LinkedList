#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>
using namespace std;

struct FoodItem {
    string name;
    double price;
    bool available;
    FoodItem* link;
};

class LinkedList {
private:
    FoodItem* head;

public:
    LinkedList() { head = nullptr; }

    ~LinkedList() {
        FoodItem* current = head;
        while (current) {
            FoodItem* temp = current;
            current = current->link;
            delete temp;
        }
    }

    void addItem(string name, double price, bool available) {
        FoodItem* newItem = new FoodItem{name, price, available, nullptr};
        if (!head) {
            head = newItem;
        } else {
            FoodItem* current = head;
            while (current->link) {
                current = current->link;
            }
            current->link = newItem;
        }
    }

    void displayItems() {
        FoodItem* current = head;

        while (current) {
            if (current->available)
                cout << "- " << current->name << " ($" << current->price << ") [Available]" << endl;
            current = current->link;
        }

        current = head;
        while (current) {
            if (!current->available)
                cout << "- " << current->name << " ($" << current->price << ") [Not Available]" << endl;
            current = current->link;
        }
    }
};

#endif

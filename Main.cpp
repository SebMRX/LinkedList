#include <iostream>
#include <fstream>
#include <string>
#include "LinkedList.h"  

using namespace std;

string trim(string str) {
    int first = str.find_first_not_of(" \t");
    if (first == -1) return "";
    int last = str.find_last_not_of(" \t");
    return str.substr(first, last - first + 1);
}

int main() {
    int NUM_CATEGORIES = 3;
    string categories[] = {"Appetizers", "Main Course", "Desserts"};
    LinkedList lists[3];

    ifstream infile("menu.txt");
    if (!infile) {
        cout << "Error opening file menu.txt" << endl;
        return 1;
    }

    string line;
    while (getline(infile, line)) {
        if (line == "") continue;

        int firstQuote = line.find('\"');
        if (firstQuote == -1) {
            cout << "Invalid format in line: " << line << endl;
            continue;
        }

        string category = trim(line.substr(0, firstQuote));
        int secondQuote = line.find('\"', firstQuote + 1);
        if (secondQuote == -1) {
            cout << "Invalid format in line: " << line << endl;
            continue;
        }

        string itemName = line.substr(firstQuote + 1, secondQuote - firstQuote - 1);
        string remaining = line.substr(secondQuote + 1);

        int spacePos = remaining.find(' ');
        if (spacePos == -1) {
            cout << "Invalid format in line: " << line << endl;
            continue;
        }

        double price = atof(remaining.substr(0, spacePos).c_str());
        int availInt = atoi(remaining.substr(spacePos + 1).c_str());
        bool available = (availInt == 1);

        int index = -1;
        for (int i = 0; i < NUM_CATEGORIES; i++) {
            if (categories[i] == category) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            lists[index].addItem(itemName, price, available);
        } else {
            cout << "Unknown category: " << category << endl;
        }
    }

    for (int i = 0; i < NUM_CATEGORIES; i++) {
        cout << "Category: " << categories[i] << endl;
        lists[i].displayItems();
    }

    return 0;
}

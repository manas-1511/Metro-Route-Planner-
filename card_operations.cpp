#include "card_operations.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Saves balance to a file so it persists across runs
static double loadBalance(const string& username) {
    ifstream f(username + "_balance.txt");
    double bal = 200.0; // default starting balance
    if (f.is_open()) f >> bal;
    return bal;
}

static void saveBalance(const string& username, double balance) {
    ofstream f(username + "_balance.txt");
    f << balance;
}

void recharge(string username) {
    double amount = loadBalance(username);
    int choice;
    do {
        cout << "\nCurrent Balance: Rs." << amount << endl;
        cout << "1. Recharge\n2. Exit\nEnter choice: ";
        cin >> choice;
        if (choice == 1) {
            double amt;
            cout << "Enter recharge amount: ";
            cin >> amt;
            amount += amt;
            saveBalance(username, amount);
            cout << "Recharged! New Balance: Rs." << amount << endl;
        }
    } while (choice != 2);
}

// Call this after a trip is taken to deduct fare
void deductFare(const string& username, double fare) {
    double balance = loadBalance(username);
    if (balance < fare) {
        cout << "Insufficient balance! Please recharge. Current: Rs." << balance << endl;
        return;
    }
    balance -= fare;
    saveBalance(username, balance);
    cout << "Fare deducted: Rs." << fare << " | Remaining Balance: Rs." << balance << endl;
}

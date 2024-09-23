#include <iostream>
#include <limits>
using namespace std;

#define CLEAR "cls"

class BankAccount {
protected:
    double balance;
public:
    BankAccount(double initialBalance) : balance(initialBalance) {}

    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
    virtual void checkBalance() const {
        cout << "Current balance: " << balance << endl;
    }
};

class SavingsAccount : public BankAccount {
private:
    static const double MIN_BALANCE;
public:
    SavingsAccount(double initialBalance) : BankAccount(initialBalance) {}

    void deposit(double amount) override {
        if (amount > 0) {
            balance += amount;
            cout << amount << " deposited successfully.\n";
        } else {
            cout << "Invalid amount! Please enter a positive number.\n";
        }
    }

    void withdraw(double amount) override {
        if (amount > 0 && (balance - amount >= MIN_BALANCE)) {
            balance -= amount;
            cout << amount << " withdrawn successfully.\n";
        } else if (amount <= 0) {
            cout << "Invalid amount! Please enter a positive number.\n";
        } else {
            cout << "Insufficient balance! Minimum balance should be " << MIN_BALANCE << ".\n";
        }
    }
};

const double SavingsAccount::MIN_BALANCE = 1000.0;

class CurrentAccount : public BankAccount {
public:
    CurrentAccount(double initialBalance) : BankAccount(initialBalance) {}

    void deposit(double amount) override {
        if (amount > 0) {
            balance += amount;
            cout << amount << " deposited successfully.\n";
        } else {
            cout << "Invalid amount! Please enter a positive number.\n";
        }
    }

    void withdraw(double amount) override {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            cout << amount << " withdrawn successfully.\n";
        } else if (amount <= 0) {
            cout << "Invalid amount! Please enter a positive number.\n";
        } else {
            cout << "Insufficient balance!\n";
        }
    }
};

void displayMainMenu() {
    cout << "\n==== Main Menu ====\n";
    cout << "1. Savings Account\n";
    cout << "2. Current Account\n";
    cout << "3. Exit\n";
}

void displayAccountMenu() {
    cout << "\n==== Account Menu ====\n";
    cout << "1. Deposit\n";
    cout << "2. Withdraw\n";
    cout << "3. Check Balance\n";
    cout << "4. Back to Main Menu\n";
}

double getValidDoubleInput() {
    double value;
    while (!(cin >> value)) {
        cout << "Invalid input! Please enter a valid number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return value;
}

int getValidIntInput(int min, int max) {
    int value;
    while (!(cin >> value) || value < min || value > max) {
        cout << "Invalid input! Please enter a number between " << min << " and " << max << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return value;
}

int main() {
    BankAccount* account = nullptr;
    int mainChoice, accountChoice;
    double initialBalance, amount;

    while (true) {
        system(CLEAR);
        displayMainMenu();
        cout << "Choose an account type (1-3): ";
        mainChoice = getValidIntInput(1, 3);

        if (mainChoice == 3) {
            cout << "Thank you for using our bank!\n";
            break;
        }

        cout << "Enter initial balance: ";
        initialBalance = getValidDoubleInput();

        if (mainChoice == 1) {
            account = new SavingsAccount(initialBalance);
        } else if (mainChoice == 2) {
            account = new CurrentAccount(initialBalance);
        }

        while (true) {
            system(CLEAR);
            displayAccountMenu();
            cout << "Choose an action (1-4): ";
            accountChoice = getValidIntInput(1, 4);

            if (accountChoice == 4) {
                delete account;
                break;
            }

            switch (accountChoice) {
                case 1:
                    cout << "Enter amount to deposit: ";
                    amount = getValidDoubleInput();
                    account->deposit(amount);
                    break;
                case 2:
                    cout << "Enter amount to withdraw: ";
                    amount = getValidDoubleInput();
                    account->withdraw(amount);
                    break;
                case 3:
                    account->checkBalance();
                    break;
                default:
                    cout << "Invalid choice! Please try again.\n";
            }

            system("pause");
        }
    }

    system(CLEAR);
    system("pause");
    return 0;
}

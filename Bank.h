#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <map>

using namespace std; 
// Transaction structure to store transaction details
struct Transaction {
    string type;
    double amount;
    time_t timestamp;
};

// Account type enum
enum class AccountType {
    SAVINGS,
    CHECKING,
    LOAN
};

// Function to print decorative ASCII art
void printLogo() {
    cout << "          WELCOME TO BANK MANAGEMENT SYSTEM          ";
}

class Account {
private:
    string accountNumber;
    string ownerName;
    double balance;
    AccountType type;
    vector<Transaction> transactionHistory;
    time_t creationTime;

public:
    Account(string accNum, string owner, double initialBalance, AccountType accType) : accountNumber(accNum), ownerName(owner), balance(initialBalance), type(accType) {
        creationTime = time(nullptr);
    }

    string getAccountNumber() const { return accountNumber; }
    string getOwnerName() const { return ownerName; }
    double getBalance() const { return balance; }
    AccountType getAccountType() const { return type; }
    string getCreationDate() const { return ctime(&creationTime); }

    void deposit(double amount) {
        balance += amount;
        recordTransaction("Deposit", amount);
        cout << "Deposited " << amount << " successfully. New balance: " << balance << endl;
    }

    bool withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            recordTransaction("Withdrawal", amount);
            cout << "Withdrawn " << amount << " successfully. New balance: " << balance << endl;
            return true;
        } else {
            cout << "Insufficient funds." << endl;
            return false;
        }
    }

    void recordTransaction(string type, double amount) {
        Transaction transaction;
        transaction.type = type;
        transaction.amount = amount;
        transaction.timestamp = time(nullptr);
        transactionHistory.push_back(transaction);
    }

    void displayTransactionHistory() const {
        cout << "\nTransaction History for Account " << accountNumber << ":" << endl;
        cout << "-------------------------------------------" << endl;
        cout << setw(15) << "Type" << setw(15) << "Amount" << setw(25) << "Timestamp" << endl;
        cout << "-------------------------------------------" << endl;
        for (const auto& transaction : transactionHistory) {
            cout << setw(15) << transaction.type << setw(15) << transaction.amount << setw(25) << ctime(&transaction.timestamp);
        }
        cout << endl;
    }
};

class Bank {
private:
    vector<Account> accounts;
    map<string, string> credentials; // Map to store username and password

public:
    Bank() {
        // Add default admin credentials
        credentials["admin"] = "admin123";
    }

    // Function to create account
    void createAccount() {
        string accountNumber, ownerName;
        double initialBalance;
        int accountTypeChoice;

        cout << "Enter account number: ";
        cin >> accountNumber;

        cout << "Enter owner name: ";
        cin.ignore(); // Clear input buffer
        getline(cin, ownerName);

        cout << "Enter initial balance: ";
        cin >> initialBalance;

        cout << "Select account type:\n";
        cout << "1. Savings\n";
        cout << "2. Checking\n";
        cout << "3. Loan\n";
        cout << "Enter choice: ";
        cin >> accountTypeChoice;

        AccountType accType;
        switch (accountTypeChoice) {
            case 1:
                accType = AccountType::SAVINGS;
                break;
            case 2:
                accType = AccountType::CHECKING;
                break;
            case 3:
                accType = AccountType::LOAN;
                break;
            default:
                cout << "Invalid choice. Defaulting to savings account." << endl;
                accType = AccountType::SAVINGS;
        }

        accounts.emplace_back(accountNumber, ownerName, initialBalance, accType);
        cout << "Account created successfully." << endl;
    }

    Account* findAccount(string accountNumber) {
        auto it = find_if(accounts.begin(), accounts.end(), [&](const Account& acc) {
            return acc.getAccountNumber() == accountNumber;
        });
        if (it != accounts.end()) {
            return &(*it);
        } else {
            return nullptr;
        }
    }

    void deposit() {
        string accountNumber;
        double amount;

        cout << "Enter account number: ";
        cin >> accountNumber;

        cout << "Enter amount to deposit: ";
        cin >> amount;

        Account* acc = findAccount(accountNumber);
        if (acc) {
            acc->deposit(amount);
        } else {
            cout << "Account not found." << endl;
        }
    }

    void withdraw() {
        string accountNumber;
        double amount;

        cout << "Enter account number: ";
        cin >> accountNumber;

        cout << "Enter amount to withdraw: ";
        cin >> amount;

        Account* acc = findAccount(accountNumber);
        if (acc) {
            acc->withdraw(amount);
        } else {
            cout << "Account not found." << endl;
        }
    }

    void transfer() {
        string fromAccountNumber, toAccountNumber;
        double amount;

        cout << "Enter from account number: ";
        cin >> fromAccountNumber;

        cout << "Enter to account number: ";
        cin >> toAccountNumber;

        cout << "Enter amount to transfer: ";
        cin >> amount;

        Account* fromAcc = findAccount(fromAccountNumber);
        Account* toAcc = findAccount(toAccountNumber);
        if (fromAcc && toAcc) {
            if (fromAcc->withdraw(amount)) {
                toAcc->deposit(amount);
                cout << "Transfer successful." << endl;
            } else {
                cout << "Transfer failed due to insufficient funds." << endl;
            }
        } else {
            cout << "One or both accounts not found." << endl;
        }
    }

    void displayAccountInfo() {
        string accountNumber;

        cout << "Enter account number: ";
        cin >> accountNumber;

        Account* acc = findAccount(accountNumber);
        if (acc) {
            cout << "\nAccount Information\n";
            cout << "-------------------------------------------" << endl;
            cout << setw(20) << "Account Number: " << acc->getAccountNumber() << endl;
            cout << setw(20) << "Owner Name: " << acc->getOwnerName() << endl;
            cout << setw(20) << "Balance: $" << fixed << setprecision(2) << acc->getBalance() << endl;
            cout << setw(20) << "Account Type: ";
            switch (acc->getAccountType()) {
                case AccountType::SAVINGS:
                    cout << "Savings Account" << endl;
                    break;
                case AccountType::CHECKING:
                    cout << "Checking Account" << endl;
                    break;
                case AccountType::LOAN:
                    cout << "Loan Account" << endl;
                    break;
            }
            cout << setw(20) << "Creation Date: " << acc->getCreationDate();
            acc->displayTransactionHistory();
        } else {
            cout << "Account not found." << endl;
        }
    }
};



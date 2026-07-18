#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
using namespace std;

class BankAccount
{
private:
    int accountNumber;
    string customerName;
    double balance;

public:
    void createAccount();
    void displayAccount();
    int getAccountNumber();
    double getBalance();
    void saveAccount();
    void displayAllAccounts();
    void depositMoney();
    void withdrawMoney();
    void checkBalance();   
};
void BankAccount::displayAllAccounts()
{
    ifstream file("accounts.txt");

    if (!file)
    {
        cout << "\nNo records found.\n";
        return;
    }

    int accNo;
    string name;
    double bal;
    char comma;

    cout << "\n========== ACCOUNT LIST ==========\n";

    while (file >> accNo >> comma)
    {
        getline(file, name, ',');
        file >> bal;

        cout << "\nAccount Number : " << accNo;
        cout << "\nCustomer Name  : " << name;
        cout << "\nBalance        : " << bal;
        cout << "\n-----------------------------";
    }

    file.close();
}

void BankAccount::createAccount()
{
    cout << "\nEnter Account Number: ";
    cin >> accountNumber;

    cin.ignore();

    cout << "Enter Customer Name: ";
    getline(cin, customerName);

    cout << "Enter Initial Balance: ";
    cin >> balance;
}

void BankAccount::displayAccount()
{
    cout << "\n----------------------------";
    cout << "\nAccount Number : " << accountNumber;
    cout << "\nCustomer Name  : " << customerName;
    cout << "\nBalance        : " << balance;
    cout << "\n----------------------------";
}

int BankAccount::getAccountNumber()
{
    return accountNumber;
}

double BankAccount::getBalance()
{
    return balance;
}

int main()
{
    BankAccount account;
    int choice;

    do
    {
        cout << "\n===== BANK MANAGEMENT SYSTEM =====\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Balance\n";
        cout << "5. Display All Accounts\n";
        cout << "6. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                account.createAccount();
                account.saveAccount();
                break;
            case 2:
                account.depositMoney();
                break;

            case 3:
                account.withdrawMoney();
                break;

            case 4:
                account.checkBalance();
                break;
            case 5:
                account.displayAllAccounts();
                break;

            case 6:
                cout << "\nThank You!\n";
                break;

            default:
                cout << "\nInvalid choice.\n";
        }

    }while(choice!=6);

    return 0;
}

void BankAccount::saveAccount()
{
    ofstream file("accounts.txt", ios::app);

    if(file.is_open())
    {
        file << accountNumber << ","
             << customerName << ","
             << balance << endl;

        file.close();

        cout << "\nAccount saved successfully.\n";
    }
    else
    {
        cout << "\nError opening file.\n";
    }
}
void BankAccount::checkBalance()
{
    ifstream file("accounts.txt");

    if (!file)
    {
        cout << "\nNo accounts found.\n";
        return;
    }

    int searchAccNo;
    cout << "\nEnter Account Number: ";
    cin >> searchAccNo;

    int accNo;
    string name;
    double bal;
    char comma;

    bool found = false;

    while (file >> accNo >> comma)
    {
        getline(file, name, ',');
        file >> bal;

        if (accNo == searchAccNo)
        {
            cout << "\n------ ACCOUNT DETAILS ------";
            cout << "\nAccount Number : " << accNo;
            cout << "\nCustomer Name  : " << name;
            cout << "\nBalance        : " << bal;
            cout << "\n-----------------------------";

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\nAccount not found.\n";
    }

    file.close();
}
void BankAccount::depositMoney()
{
    int searchAccNo;
    double deposit;

    cout << "\nEnter Account Number: ";
    cin >> searchAccNo;

    cout << "Enter Amount to Deposit: ";
    cin >> deposit;

    ifstream file("accounts.txt");
    ofstream temp("temp.txt");

    int accNo;
    string name;
    double bal;
    char comma;

    bool found = false;

    while (file >> accNo >> comma)
    {
        getline(file, name, ',');
        file >> bal;

        if (accNo == searchAccNo)
        {
            bal += deposit;
            found = true;
        }

        temp << accNo << "," << name << "," << bal << endl;
    }

    file.close();
    temp.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if(found)
        cout << "\nAmount deposited successfully.\n";
    else
        cout << "\nAccount not found.\n";
}
void BankAccount::withdrawMoney()
{
    int searchAccNo;
    double withdraw;

    cout << "\nEnter Account Number: ";
    cin >> searchAccNo;

    cout << "Enter Amount to Withdraw: ";
    cin >> withdraw;

    ifstream file("accounts.txt");
    ofstream temp("temp.txt");

    int accNo;
    string name;
    double bal;
    char comma;

    bool found = false;

    while (file >> accNo >> comma)
    {
        getline(file, name, ',');
        file >> bal;

        if (accNo == searchAccNo)
        {
            found = true;

            if (withdraw <= bal)
            {
                bal -= withdraw;
                cout << "\nAmount withdrawn successfully.\n";
            }
            else
            {
                cout << "\nInsufficient Balance.\n";
            }
        }

        temp << accNo << "," << name << "," << bal << endl;
    }

    file.close();
    temp.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found)
    {
        cout << "\nAccount not found.\n";
    }
}

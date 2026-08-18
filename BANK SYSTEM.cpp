#include <iostream>

using namespace std;

struct Acc
{
    unsigned long long ID;
    string name;
    short age;
    string password;
    double balance = 0;
};

void ShowMainMenu(int& choice)
{
    cout << "--------------------------------------\n";
    cout << "________Bank Management System________\n";
    cout << "[1] : Create Acc\n";
    cout << "[2] : Log in\n";
    cout << "[3] : Exit\n";
    cout << "\n\nChoice : ";
    cin >> choice;
}

void CreateAcc(Acc acc[100], int& numberOfAccounts)
{
    acc[numberOfAccounts].ID = numberOfAccounts + 1;

    cout << "Enter Name : ";
    cin >> acc[numberOfAccounts].name;

    cout << "Enter Your Age : ";
    cin >> acc[numberOfAccounts].age;

    if (acc[numberOfAccounts].age > 70 ||
        acc[numberOfAccounts].age < 18)
    {
        cout << "We Don't Accept This Age. Bye\n";
        return;
    }

    cout << "Enter Hard Password : ";
    cin >> acc[numberOfAccounts].password;

    cout << "Your ACC ID : "
        << acc[numberOfAccounts].ID << endl;

    numberOfAccounts++;

    cout << "Account Created Successfully\n";
}

void AccountMenu(Acc& account)
{
    int choice;

    do
    {
        cout << "\n================================\n";
        cout << "        Welcome " << account.name << "\n";
        cout << "================================\n";

        cout << "[1] Check Balance\n";
        cout << "[2] Deposit\n";
        cout << "[3] Withdraw\n";
        cout << "[4] Account Info\n";
        cout << "[5] Log Out\n";

        cout << "\nChoice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Balance : "
                << account.balance << endl;
            break;

        case 2:
        {
            double amount;

            cout << "How Much Money You Want To Deposit: ";
            cin >> amount;

            if (amount > 0)
            {
                account.balance += amount;

                cout << "Deposit Successfully\n";
                cout << "New Balance : "
                    << account.balance << endl;
            }
            else
            {
                cout << "Invalid Amount\n";
            }

            break;
        }

        case 3:
        {
            double amount;

            cout << "How Much Money You Want To Withdraw: ";
            cin >> amount;

            if (amount <= 0)
            {
                cout << "Invalid Amount\n";
            }
            else if (amount > account.balance)
            {
                cout << "Insufficient Balance\n";
            }
            else
            {
                account.balance -= amount;

                cout << "Withdraw Successfully\n";
                cout << "New Balance : "
                    << account.balance << endl;
            }

            break;
        }

        case 4:
            cout << "\n===== Account Information =====\n";
            cout << "Acc ID : " << account.ID << endl;
            cout << "Name   : " << account.name << endl;
            cout << "Age    : " << account.age << endl;
            cout << "Balance: " << account.balance << endl;
            break;

        case 5:
            cout << "Logged Out Successfully\n";
            break;

        default:
            cout << "Invalid Choice\n";
        }

    } while (choice != 5);
}

void LogIn(Acc acc[100], int numberOfAccounts)
{
    unsigned long long searchById;
    string searchByPass;

    cout << "\n===== Login =====\n";

    cout << "Please Enter ID : ";
    cin >> searchById;

    int accountIndex = -1;

    // Search for account
    for (int i = 0; i < numberOfAccounts; i++)
    {
        if (acc[i].ID == searchById)
        {
            accountIndex = i;
            break;
        }
    }

    // ID not found
    if (accountIndex == -1)
    {
        cout << "Account Not Found\n";
        return;
    }

    // Password attempts
    for (int attempts = 3; attempts > 0; attempts--)
    {
        cout << "Enter Password: ";
        cin >> searchByPass;

        if (searchByPass == acc[accountIndex].password)
        {
            cout << "\nLogin Successful!\n";

            AccountMenu(acc[accountIndex]);

            return;
        }

        cout << "Wrong Password\n";
        cout << "Attempts Left: " << attempts - 1 << endl;
    }

    cout << "Login Failed\n";
}

int main()
{
    Acc acc[100];

    int numberOfAccounts = 0;
    int choice;

    do
    {
        ShowMainMenu(choice);

        switch (choice)
        {
        case 1:
            CreateAcc(acc, numberOfAccounts);
            break;

        case 2:
            LogIn(acc, numberOfAccounts);
            break;

        case 3:
            cout << "Good Bye\n";
            break;

        default:
            cout << "Invalid Choice\n";
            break;
        }

    } while (choice != 3);

    return 0;
}
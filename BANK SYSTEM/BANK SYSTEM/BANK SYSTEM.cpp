// BANK SYSTEM.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

const string ClientsFileName = "ClientInfo.txt";

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

enum Choice
{
    ShowCLientList = 1,
    AddNewClientInfo,
    DelteClientInfo,
    UpdateCLintInfo,
    FindClients,
    Exit
};

bool FindClientByAccountNumber(string AccountNumber, vector<sClient>& vClient, sClient& Client)
{
    for (sClient C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

bool ClientExists(string AccountNumber, vector<sClient>& vClients)
{
    sClient Client;
    return FindClientByAccountNumber(AccountNumber, vClients, Client);
}

vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord;

    while ((pos = S1.find(Delim)) != string::npos)
    {
        sWord = S1.substr(0, pos);

        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());
    }

    if (S1 != "")
    {
        vString.push_back(S1);
    }

    return vString;
}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
    sClient Client;
    vector<string> vClientData = SplitString(Line, Seperator);

    if (vClientData.size() >= 5)
    {
        Client.AccountNumber = vClientData[0];
        Client.PinCode = vClientData[1];
        Client.Name = vClientData[2];
        Client.Phone = vClientData[3];
        Client.AccountBalance = stod(vClientData[4]);
    }

    return Client;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;
}

vector<sClient> LoadCleintsDataFromFile(string FileName)
{
    vector<sClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;

        while (getline(MyFile, Line))
        {
            if (Line != "")
            {
                sClient Client = ConvertLinetoRecord(Line);
                vClients.push_back(Client);
            }
        }

        MyFile.close();
    }

    return vClients;
}

void GoBackToMainMenu()
{
    cout << "\n\nPress Any Key To Go Back To Main Menu...";
    system("pause > nul");
}

void PrintClientCard(sClient Client)
{
    cout << "\nThe Following Are The Client Details\n\n";
    cout << "Account Number : " << Client.AccountNumber << endl;
    cout << "Pin Code       : " << Client.PinCode << endl;
    cout << "Name           : " << Client.Name << endl;
    cout << "Phone          : " << Client.Phone << endl;
    cout << "Account Balance: " << Client.AccountBalance << endl;
}

void PrintClientRecord(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << stDataLine << endl;
        MyFile.close();
    }
}

string ReadClientNumber()
{
    string FindClient;

    cout << "\n\tEnter Client ID: ";
    getline(cin >> ws, FindClient);

    return FindClient;
}

sClient ReadNewClient(vector<sClient>& vClients)
{
    sClient Client;

    cout << "Enter Account Number? ";
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExists(Client.AccountNumber, vClients))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists.";
        cout << "\nEnter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

void AddNewClient(vector<sClient>& vClients)
{
    char Add = 'y';

    do
    {
        sClient Client = ReadNewClient(vClients);

        vClients.push_back(Client);

        AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));

        cout << "\nClient Added Successfully\n";

        cout << "\nDo You want Add More? ";
        cin >> Add;

        if (Add == 'y' || Add == 'Y')
        {
            system("cls");
        }

    } while (Add == 'y' || Add == 'Y');
}

void PrintAllClientsData(vector<sClient> vClients)
{
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    for (sClient Client : vClients)
    {
        PrintClientRecord(Client);
        cout << endl;
    }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

bool MarkClientForDeleteByAccountID(string AccountNumber, vector<sClient>& vClient)
{
    for (sClient& s : vClient)
    {
        if (s.AccountNumber == AccountNumber)
        {
            s.MarkForDelete = true;
            return true;
        }
    }

    return false;
}

void SaveClientDataToFile(string FileName, vector<sClient>& vClient)
{
    fstream ClientFile;
    string DataLine;

    ClientFile.open(FileName, ios::out);

    if (ClientFile.is_open())
    {
        for (sClient& s : vClient)
        {
            if (s.MarkForDelete == false)
            {
                DataLine = ConvertRecordToLine(s);
                ClientFile << DataLine << endl;
            }
        }

        ClientFile.close();
    }
}

bool DeleteClientInfo(string AccNum, vector<sClient>& vClient)
{
    char Delete = 'N';
    char Again = 'N';

    bool DeletedAnyClient = false;

    do
    {
        sClient Client;

        if (FindClientByAccountNumber(AccNum, vClient, Client))
        {
            PrintClientCard(Client);

            cout << "\nAre you sure you want to delete this client? (Y/N): ";
            cin >> Delete;

            if (Delete == 'y' || Delete == 'Y')
            {
                MarkClientForDeleteByAccountID(AccNum, vClient);

                SaveClientDataToFile(ClientsFileName, vClient);

                vClient = LoadCleintsDataFromFile(ClientsFileName);

                cout << "\nClient Deleted Successfully\n";

                DeletedAnyClient = true;
            }
            else
            {
                cout << "\nDelete Canceled\n";
            }
        }
        else
        {
            cout << "\nClient with Account Number [" << AccNum << "] was not found.\n";
        }

        cout << "\nDo You want Delete More? ";
        cin >> Again;

        if (Again == 'y' || Again == 'Y')
        {
            AccNum = ReadClientNumber();
            system("cls");
        }

    } while (Again == 'y' || Again == 'Y');

    return DeletedAnyClient;
}

sClient ChangeClientInfo()
{
    sClient Client;

    cout << "\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

bool UpdateClientByAccountNumber(string AccNum, vector<sClient>& vClient)
{
    sClient Client;
    char Update = 'n';

    if (!FindClientByAccountNumber(AccNum, vClient, Client))
    {
        cout << "\nClient With Account ID (" << AccNum << ") Not Found\n";
        return false;
    }

    PrintClientCard(Client);

    cout << "\nAre You Sure You Want Update Client? (Y/N): ";
    cin >> Update;

    if (Update == 'y' || Update == 'Y')
    {
        for (sClient& s : vClient)
        {
            if (s.AccountNumber == AccNum)
            {
                s = ChangeClientInfo();
                s.AccountNumber = AccNum;
                break;
            }
        }

        SaveClientDataToFile(ClientsFileName, vClient);

        cout << "\nClient Info Updated Successfully\n";

        return true;
    }

    cout << "\nUpdate Canceled\n";

    return false;
}

Choice ReadChoice()
{
    int choice;

    cout << "\nChoose What Do You Want Do? [1 , 6] ? ";
    cin >> choice;

    return (Choice)choice;
}

void FindClient(string AccountNumber, vector<sClient>& vClient)
{
    sClient Client;

    if (FindClientByAccountNumber(AccountNumber, vClient, Client))
    {
        PrintClientCard(Client);
    }
    else
    {
        cout << "\nClient With Account ID (" << AccountNumber << ") Not Found\n";
    }
}

void HandleMainMenuOption(Choice UserChoice, vector<sClient>& vClient)
{
    switch (UserChoice)
    {
    case ShowCLientList:

        PrintAllClientsData(vClient);
        GoBackToMainMenu();

        break;

    case AddNewClientInfo:

        cout << "\n----------------------------------------------\n";
        cout << "           Add Client Screen\n";
        cout << "----------------------------------------------\n";

        AddNewClient(vClient);
        GoBackToMainMenu();

        break;

    case DelteClientInfo:

        cout << "\n----------------------------------------------\n";
        cout << "           Delete Screen\n";
        cout << "----------------------------------------------\n";

        DeleteClientInfo(ReadClientNumber(), vClient);
        GoBackToMainMenu();

        break;

    case UpdateCLintInfo:

        cout << "\n----------------------------------------------\n";
        cout << "           Update Client Info Screen\n";
        cout << "----------------------------------------------\n";

        UpdateClientByAccountNumber(ReadClientNumber(), vClient);
        GoBackToMainMenu();

        break;

    case FindClients:

        cout << "----------------------------------------------\n";
        cout << "           Find Client Screen\n";
        cout << "----------------------------------------------\n";

        FindClient(ReadClientNumber(), vClient);
        GoBackToMainMenu();

        break;
    }
}

void ShowMainMenu()
{
    cout << "===============================================================\n";
    cout << "\n\t\t\tMain Menu Screen\n\n";
    cout << "===============================================================\n";

    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Exit.\n";

    cout << "===============================================================\n";
}

void StartBank()
{
    vector<sClient> Data = LoadCleintsDataFromFile(ClientsFileName);

    while (true)
    {
        system("cls");

        ShowMainMenu();

        Choice UserChoice = ReadChoice();

        system("cls");

        if (UserChoice == Exit)
        {
            cout << "\nBANK SYSTEM OFF )-:\n";
            break;
        }

        HandleMainMenuOption(UserChoice, Data);
    }
}

int main()
{
    StartBank();
    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage code files
//   2. Use Team Explorer window to connect to source control
//   3. Use the Output window to see output information
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, you can go to File > Open > Project and select the .sln file
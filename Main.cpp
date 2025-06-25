#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <regex>
#include "CustomerClass.h"
#include "Customer.h"
#include "ProductClass.h"
#include "Prod_Management.h"
#include "Rewards.h"
#include "Shopping.h"

using namespace std;

int main()
{

    bool mLoop = true;

    int uInput;

    while (mLoop)
    {
        cout << "   --What would you like to do?--" << endl;
        cout << "(1) Register Customer" << endl;
        cout << "(2) Remove Customer" << endl;
        cout << "(3) Add Product" << endl;
        cout << "(4) Remove Product" << endl;
        cout << "(5) Shopping" << endl;
        cout << "(6) Reward Management" << endl;
        cout << "(7) View Customer Profile" << endl;
        cout << "(8)Exit Program" << endl;
        cout << "Enter a number: ";

        // While loop validating the user is inputing a number
        if (!(cin >> uInput))
        {
            cout << "Please enter a single digit between 1 and 4" << endl;
            cin.clear();
            cin.ignore(123, '\n');
            continue;
        }
        // If statement making sure the number is between 1 and 9
        if (!(uInput > 0 && uInput <= 9))
        {
            cout << "Please enter a single digit between 1 and 9" << endl;
            cin.clear();
            cin.ignore(123, '\n');
            continue;
        }
        else
        {
            // Switch statement to lead to the possible choices
            switch (uInput)
            {
            case 1:
                CreateCustomer();
                break;
            case 2:
                DeleteCustomer();
                break;
            case 3:
                cin.clear();
                cin.ignore(123, '\n');
                addProduct();
                break;
            case 4:
                cin.clear();
                cin.ignore(123, '\n');
                removeProduct();
                break;
            case 5:
                Shopping(GetCustID());
                break;
            case 6:
                RewardManagement();
                break;
            case 7:
                CustomerProfile();
                break;
            case 8:
                cin.clear();
                cin.ignore(123, '\n');
                cout << "Exit" << endl;
                mLoop = false;
                break;
            default:
                cout << "Please enter a single digit between 1 and 8" << endl;
                continue;
            }
        }
    }
}
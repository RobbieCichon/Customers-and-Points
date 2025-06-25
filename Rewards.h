#ifndef REWARDS_H
#define REWARDS_H
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include "CustomerClass.h"
#include "Customer.h"

// Function Purpose:     Removes saved customer's information from the customers.txt text file
// Return value:         void
// Parameters:           RPoints                 int                     Amount of points to
// Parameters:           CustID                  string                  ID of customer to be deleted
void AwardPoints(int RPoints, std::string CustID)
{
    // Constructs a customer class using the given id
    Customer Cust(CustID);

    // Adds the specified points to the customer's total
    Cust.Points += RPoints;

    std::cout << "Point total is now: " << Cust.Points << "\n";
}

std::string GetPrice()
{
    std::string Price;

    std::cout << "Please enter price" << std::endl;
    while (true)
    {
        while (!(std::cin >> Price))
        {
            std::cout << "Please enter only numbers" << std::endl;
            std::cin.clear();
            std::cin.ignore(123, '\n');
        }

        if (!(std::stoi(Price) > 0 || std::stoi(Price) < 65535))
        {
            std::cout << "Please enter a positive number between 0 and 65535" << std::endl;
            continue;
        }
        else
        {
            break;
        }
    }

    return Price;
}

std::string GetPrize()
{
    std::string Prize;
    std::string line;
    bool aPrize = false;
    std::ifstream Prizes("prizes.txt");

    while (true)
    {

        std::cout << "Enter the desired prize: ";

        while (!(std::cin >> Prize))
        {
            std::cin.clear();
            std::cin.ignore(123, '\n');
            std::cout << "Enter the desired prize: ";
        }

        while (getline(Prizes, line))
        {
            if (line == "Item name: " + Prize)
            {
                aPrize = true;
                break;
            }
            else
            {
                continue;
            }
        }

        if (aPrize)
        {
            break;
        }
        else
        {
            continue;
        }
    }

    Prizes.close();
    return Prize;
}

// Function Purpose:     Adds a reward that could be redeemed to the prizes text file
// Return value:         void
void AddPrize()
{

    std::string Prize;
    std::string Price;

    std::cout << "Enter the prize name: ";

    while (!(std::cin >> Prize))
    {
        std::cin.clear();
        std::cin.ignore(123, '\n');
        std::cout << "Enter the prize name: ";
    }

    // Open files for reading and writing
    std::ifstream Prizes("prizes.txt");
    std::ofstream Temp("temp.txt", std::ios::app);

    // Declare variables
    bool Check = false;
    std::string line;
    std::string TString = "Item name: " + Prize;

    // loop through file and ensure that prize doesn't exist
    while (getline(Prizes, line))
    {
        Temp << line << "\n";
        if (TString == line)
        {
            Check = true;
            break;
        }
        else
        {
            continue;
        }
    }

    // If prize doesn't exist, it appends info to the end of the file
    if (Check)
    {
        std::cout << "Prize already exists!\n";
        return;
    }
    else
    {
        Price = GetPrice();
        Temp << "Item name: " << Prize << "\n";
        Temp << "Item price:\n"
             << Price << "\n\n";
        std::cout << "Item added!\n";
    }

    // Closes files and renames new file
    Prizes.close();
    Temp.close();
    std::remove("prizes.txt");
    std::rename("temp.txt", "prizes.txt");
}

// Function Purpose:     Prompts user for their desired prize and Customer ID, then
//                       Removes a prize from the rewards text file and subtracts the amount from the customer's point total if able
// Return value:         void
// Parameters:           prize                   string                  Name of prize to be redeemed
// Parameters:           CustID                  string                  ID of customer to be deleted
void RedeemPoints()
{

    std::string Prize = GetPrize();
    std::string CustID = GetCustID();

    // Opens files for reading and writing
    std::ifstream Prizes("prizes.txt");
    std::ofstream Temp("temp.txt", std::ios::app);

    // Declare variables
    std::string line;
    std::string TString = "Item name: " + Prize;
    bool Check = false;
    int iprice;
    int Dec = 0;

    // Loops through file, once it finds the designated item it doesn't transfer it over to the new file, removing it
    while (getline(Prizes, line))
    {
        if (line != TString && Dec <= 0)
        {
            Temp << line << "\n";
        }

        else
        {
            switch (Dec)
            {
            case 0:
            {
                Check = true;
                Dec = 3;
                break;
            }
            case 1:
            {
                --Dec;
                break;
            }
            case 2:
            {
                std::stringstream PointsLine;
                PointsLine << line;
                PointsLine >> iprice;
                --Dec;
                break;
            }
            case 3:
                --Dec;
                break;
            }
        }
    }

    // If item is found, it closes and renames files
    if (!Check)
    {
        std::cout << "Item not found!\n";
        return;
    }
    else
    {

        Prizes.close();
        Temp.close();

        // Creates customer class and tries to subtract the price from point total
        Customer Cust(CustID);

        std::cout << Cust.Points << std::endl;
        std::cout << iprice << std::endl;

        if (Cust.Points < iprice)
        {
            std::cout << "Not enough points!\n";
            std::remove("temp.txt");
        }
        else
        {
            std::remove("prizes.txt");
            std::rename("temp.txt", "prizes.txt");

            Cust.Points -= iprice;

            std::cout << "Prize Redeemed! Remaining Points: " << Cust.Points << "\n";
        }
    }
}

// Function Purpose:     Prompts user to either add prize or redeem points
// Return value:         void
void RewardManagement()
{
    bool RCheck = true;
    int RuInput;

    while (RCheck)
    {
        std::cout << "(1) Add prize\n";
        std::cout << "(2) Redeem Points\n";
        std::cout << "Enter a number: ";

        // While loop validating the user is inputing a number
        if (!(std::cin >> RuInput))
        {
            std::cout << "Please enter a single digit between 1 and 4" << std::endl;
            std::cin.clear();
            std::cin.ignore(123, '\n');
            continue;
        }

        // If statement making sure the number is between 1 and 2
        if (!(RuInput > 0 && RuInput < 3))
        {
            std::cout << "Please enter a single digit between 1 and 2" << std::endl;
            std::cin.clear();
            std::cin.ignore(123, '\n');
            continue;
        }
        if (RuInput == 1)
        {
            AddPrize();
            RCheck = false;
        }
        else
        {
            RedeemPoints();
            RCheck = false;
        }
    }
}

#endif
#ifndef SHOPPING_H
#define SHOPPING_H
#include <ctime>
#include "ProductClass.h"
#include "Customer.h"
#include "Rewards.h"

// Function Purpose:     Processes a transaction, outputting a log file, removing stock of purchased products, and awarding points to customer
// Return value:         void
// Parameters:           CustID                  string                  ID of customer to award points to
void Shopping(std::string CustID)
{
    // Initializes variables
    float Sum = 0;
    int Tpoints = 0;
    std::string CurrentProdID, TempInput, UserID;
    std::string TID = "TID";

    // Opens file for writing
    std::ofstream Tfile("transactions.txt", std::ios::app);

    // Gets User ID
    std::cout << "Please enter user ID:\n";
    std::cin >> UserID;

    // Generates random 10 digit transaction ID
    srand((unsigned)time(0));
    for (int t = 0; t <= 9; t++)
    {
        int RandNum = rand() % 10;
        TID += std::to_string(RandNum);
    }
    // Writes to file
    Tfile << TID << "\n";
    Tfile << UserID << "\n";

    // Loops through asking for product ID and amount buying
    while (true)
    {
        TempInput = "";
        int TempStock = 0;

        std::cout << "Please enter the full product ID:\n";
        std::cin >> CurrentProdID;

        // Generates product class based off given ID
        Product CurrentProd(CurrentProdID);

        std::cout << "How many of product is being bought?\n";
        std::cin >> TempStock;

        // Ensures enough stock is available and subtracts stock amount
        if (TempStock > CurrentProd.stock)
        {
            std::cout << "Not enough of product!\n";
            continue;
        }
        else
        {
            Sum += TempStock * CurrentProd.prodPrice;
            CurrentProd.stock -= TempStock;
        }

        Tfile << CurrentProdID;

        // Gives option to add more or finish
        std::cout << "Add more products? y/n.\n";
        std::cin >> TempInput;

        if (TempInput == "y")
        {
            Tfile << ", ";
            continue;
        }
        else if (TempInput == "n")
        {
            break;
        }
    }

    std::cout << "Total today: " << Sum << "\n";

    std::cout << "How many points are being awarded?\n";
    std::cin >> Tpoints;
    AwardPoints(Tpoints, CustID);

    // Adds last of info to log and closes file
    Tfile << "\n"
          << Sum << "\n";
    Tfile << Tpoints << "\n\n";

    Tfile.close();
}


#endif
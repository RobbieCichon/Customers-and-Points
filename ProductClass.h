#ifndef PRODUCTCLASS_H
#define PRODUCTCLASS_H
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

class Product
{
public:
    Product(std::string);
    ~Product();
    int stock;
    std::string prodName;
    std::string prodID;
    float prodPrice;
};

Product::Product(std::string ProdID)
{
    // Open file for reading
    std::ifstream ProdFile("products.txt");

    // Declare variables
    bool Check = false;
    std::string line;
    prodID = ProdID;
    int Dec = -1;

    // loops through file looking for matching product ID
    while (getline(ProdFile, line))
    {
        if (line == ProdID && Dec <= 0)
        {
            Check = true;
            prodID = line;
            Dec = 2;
        }
        else
        {
            switch (Dec)
            {
            case 0:
            {
                std::stringstream StocksLine;
                StocksLine << line;
                StocksLine >> stock;
                --Dec;
                break;
            }
            case 1:
            {
                std::stringstream PriceLine;
                PriceLine << line;
                PriceLine >> prodPrice;
                Dec--;
                break;
            }
            case 2:
            {
                prodName = line;
                Dec--;
                break;
            }
            default:
            {
                continue;
                break;
            }
            }
        }
    }
}

// Function Purpose:     Saves any changes done to product to text file, overwriting previous data
// Return value:         void
// Parameters:
Product::~Product()
{
    // Open files for reading and writing
    std::ifstream CustFile("products.txt");
    std::ofstream Temp("temp.txt");

    // Decalre variables
    std::string line;
    int Dec = 0;

    // Loops through file looking for id to replace info
    while (getline(CustFile, line))
    {
        if (prodID != line && Dec == 0)
        {
            Temp << line << "\n";
        }
        else
        {
            switch (Dec)
            {
            case 0:
            {
                Temp << line << "\n";
                Dec = 3;
                break;
            }
            case 1:
            {
                Temp << stock << "\n";
                Dec--;
                break;
            }
            case 2:
            {
                Temp << prodPrice << "\n";
                Dec--;
                break;
            }
            case 3:
            {
                Temp << prodName << "\n";
                Dec--;
                break;
            }
            }
        }
    }

    // closes and renames files
    CustFile.close();
    Temp.close();
    std::remove("products.txt");
    std::rename("temp.txt", "products.txt");
}

#endif
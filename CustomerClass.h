#ifndef CUSTOMERCLASS_H
#define CUSTOMERCLASS_H
#include <string>
#include <sstream>
#include <fstream>

class Customer
{
public:
    Customer(std::string);
    ~Customer();
    int Points;
    std::string Username;
    std::string FirstName;
    std::string LastName;
    std::string ID;
    std::string DoB;
};

Customer::Customer(std::string CustID)
{
    // Open file for reading
    std::ifstream CustFile("customers.txt");

    // Declare variables
    bool Check = false;
    std::string line;
    int Dec = -1;

    // loops through file looking for matching customer ID
    while (getline(CustFile, line))
    {
        if (line == CustID && Dec <= 0)
        {
            Check = true;
            ID = line;
            Dec = 4;
        }
        else
        {
            switch (Dec)
            {
            case 0:
            {
                std::stringstream PointsLine;
                PointsLine << line;
                PointsLine >> Points;
                --Dec;
                break;
            }
            case 1:
            {
                DoB = line;
                Dec--;
                break;
            }
            case 2:
            {
                LastName = line;
                Dec--;
                break;
            }
            case 3:
            {
                FirstName = line;
                Dec--;
                break;
            }
            case 4:
            {
                Username = line;
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

Customer::~Customer()
{
    // Open files for reading and writing
    std::ifstream CustFile("customers.txt");
    std::ofstream Temp("temp.txt");

    // Decalre variables
    std::string line;
    int Dec = 0;

    // Loops through file looking for id to replace info
    while (getline(CustFile, line))
    {
        if (ID != line && Dec == 0)
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
                Dec = 5;
                break;
            }
            case 1:
            {
                Temp << Points << "\n";
                Dec--;
                break;
            }
            case 2:
            {
                Temp << DoB << "\n";
                Dec--;
                break;
            }
            case 3:
            {
                Temp << LastName << "\n";
                Dec--;
                break;
            }
            case 4:
            {
                Temp << FirstName << "\n";
                Dec--;
                break;
            }
            case 5:
            {
                Temp << Username << "\n";
                Dec--;
                break;
            }
            }
        }
    }

    // closes and renames files
    CustFile.close();
    Temp.close();
    remove("customers.txt");
    rename("temp.txt", "customers.txt");
}

#endif
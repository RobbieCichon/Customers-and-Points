#ifndef PROD_MANAGEMENT_H
#define PROD_MANAGEMENT_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <regex>
#include "ProductClass.h"

std::ifstream rLogs;
std::ofstream wLogs;

// Function that checks to see if the product name passed through it already exists
// in the products log file
//
// result - The boolean value that is returned from the function
// that dictates if the product name is in the log file
//
// rx - The regex pattern that is used for comparison to find
// the Name line for each product in the log file
//
// line - string variable that is used to loop through the log file
//
// match - smatch value used to pass the string found by the regex comparison
bool prodNameTaken(std::string name)
{

    rLogs.open("products.txt");

    bool result = false;
    std::regex rx(name);
    std::smatch match;
    std::string line;

    while (getline(rLogs, line))
    {
        if (regex_search(line, match, rx))
        {

            result = true;
        }
        else
        {
            continue;
        }
    }

    rLogs.close();
    return result;
}

// Function the prompts the user to input a name for the product they're entering
// and returns it to where function was called
//
// prodName - string variable that stores the product name input by user
std::string getProdName()
{

    std::string prodName;

    // While loop for product name
    while (true)
    {

        std::cout << "Product Name: ";

        while (!(getline(std::cin, prodName)))
        {
            std::cout << "Please enter a valid name" << std::endl;
            std::cin.clear();
            std::cin.ignore(123, '\n');
            std::cout << "Product Name: ";
        }

        if (prodName.length() > 20 || prodName.length() < 3)
        {
            std::cout << "That name is too long or short. Name must be between 3 and 20 characters in length." << std::endl;
            std::cin.clear();
            std::cin.ignore(123, '\n');
            continue;
        }
        else
        {
            if (prodNameTaken(prodName))
            {
                std::cout << "That product name is taken, please enter a different name." << std::endl;
                std::cin.clear();
                std::cin.ignore(123, '\n');
            }
            else
            {
                break;
            }
        }
    }

    return prodName;
}

// Function prompting user to input the price for the product they're entering
// and returns price to where function is called
//
// prodPrice - Variable that stores the price input by user
float getProdPrice()
{

    float prodPrice;

    // While loop for price
    while (true)
    {

        std::cout << "Product price: ";

        while (!(std::cin >> prodPrice))
        {
            std::cout << "Please enter only numbers" << std::endl;
            std::cin.clear();
            std::cin.ignore(123, '\n');
            std::cout << "Price: ";
        }

        if (!(prodPrice > 0 || prodPrice < 65535))
        {
            std::cout << "Please enter a positive number between 0 and 65535" << std::endl;
            continue;
        }
        else
        {
            break;
        }
    }

    return prodPrice;
}

// Function that prompts the user for the current stock of the product being input
// and returns the stock input to where the function is called
//
// stock - variable that stores the stock input by user
int getStock()
{

    int stock;

    // While loop for the current stock of the product
    while (true)
    {

        std::cout << "Current stock: ";

        while (!(std::cin >> stock))
        {
            std::cout << "Please enter only numbers" << std::endl;
            std::cin.clear();
            std::cin.ignore(123, '\n');
            std::cout << "Current stock: ";
        }

        if (!(stock > 0 || stock < 65535))
        {
            std::cout << "Please enter a positive number between 0 and 65535" << std::endl;
            continue;
        }
        else
        {
            break;
        }
    }

    return stock;
}

// Finds the highest product ID currently in the products log file
//
// line - string variable used to loop through the log file
//
// rx - regex variable used to store the regex pattern used to compare each line to
//
// match - smatch variable used to hold the string found using the regex pattern
//
// prevID - int variable used for comparing to the next ID in line
//
// focusID - the next ID in line that the prevID is compared against
//
// sID - the intitial
int getHighestProdID()
{

    rLogs.open("products.txt");

    std::string line;
    std::regex rx("P[0-9]{5}");

    int prevID = 0;
    int focusID = 0;

    while (getline(rLogs, line))
    {

        if (regex_match(line, rx))
        {
            // Setting the string equal to just the numbers in the product ID, foregoing the P
            // slot 14 is P, 15 to the end is the numbers
            focusID = std::stoi(line.substr(1, line.length()));
            if (focusID > prevID)
            {
                prevID = focusID;
            }
        }
    }
    rLogs.close();
    return prevID;
}

/*Generates and returns the product ID based on the current amount of products already logged

 prodID - string storing the product ID

 countLength - the number of digits in count variable

 count - variable used to find the count length of the prodCount
*/
std::string makeProdIDString(int cProdCount)
{

    std::string prodID;

    int countLength = 0;
    cProdCount += 1;
    int count = cProdCount;

    while (count != 0)
    {
        count = count / 10;
        countLength++;
    }

    prodID = "P";
    for (int i = 0; i < (5 - countLength); i++)
    {
        prodID = prodID + "0";
    }

    prodID = prodID + std::to_string(cProdCount);

    return prodID;
}

/*Checking with user that the info they entered is correct

 result - the boolean to be returned

 input - string to hold the user's input

*/
bool productCheck(Product obj)
{

    bool result;
    std::string input;

    std::cout << "Is this information correct?" << std::endl;
    std::cout << "Product ID: " << obj.prodID << std::endl;
    std::cout << "Name: " << obj.prodName << std::endl;
    std::cout << "Price: " << obj.prodPrice << std::endl;
    std::cout << "Current stock: " << obj.stock << std::endl;

    while (true)
    {

        std::cout << "Y/N: ";

        while (!(std::cin >> input))
        {
            std::cout << "Please type Y or N" << std::endl;
            std::cin.clear();
            std::cin.ignore(123, '\n');
            std::cout << "Y/N: ";
        }

        if (input == "N" || input == "n")
        {
            result = false;
            break;
        }
        else if (input == "Y" || input == "y")
        {
            result = true;
            break;
        }
        else
        {
            std::cout << "Please type either Y or N" << std::endl;
            std::cin.clear();
            std::cin.ignore(123, '\n');
            std::cout << "Y/N: ";
            continue;
        }
    }
    return result;
}

/*

 Function that opens the text file,
 logs the product information into the text file
 and the closes the file

*/

void logProduct(Product obj, int prodNum)
{

    wLogs.open("products.txt", std::ios_base::out | std::ios_base::app);

    wLogs << obj.prodID << std::endl;
    wLogs << obj.prodName << std::endl;
    wLogs << obj.prodPrice << std::endl;
    wLogs << obj.stock << std::endl;
    wLogs << "" << std::endl;

    wLogs.close();
}

/*
    Main function for adding a new product

    ID, name, price, stock - variables used for holding the input variables by the user


*/
void addProduct()
{

    std::string ID;
    std::string name;
    float price;
    int stock;
    int currentProdCount;

    bool prodLoop = true;

    std::cout << "----Please fill out the product information.----" << std::endl;

    name = getProdName();

    price = getProdPrice();

    stock = getStock();

    currentProdCount = getHighestProdID();

    ID = makeProdIDString(currentProdCount);

    Product activeProduct(ID);
    activeProduct.prodName = name;
    activeProduct.prodPrice = price;
    activeProduct.stock = stock;

    if (productCheck(activeProduct))
    {
        logProduct(activeProduct, (currentProdCount + 1));
        std::cout << "Thank you, the product has been added." << std::endl;
    }
    else
    {
        std::cout << "Product has been canceled." << std::endl;
    }
}

void deleteProd(std::string ID)
{

    // Open files for reading and writing
    std::ifstream ProdFile("products.txt");
    std::ofstream Temp("temp.txt");

    // Decalre variables
    std::string line;
    bool found;
    int Dec = 0;
    std::regex rx(ID);

    // Loops through file looking for id to replace info
    while (getline(ProdFile, line))
    {

        if (regex_search(line, rx))
        {
            found = true;
        }
        else
        {
            found = false;
        }

        if (!found && Dec <= 0)
        {
            Temp << line << "\n";
        }
        else
        {
            switch (Dec)
            {
            case 0:
            {
                Dec = 4;
                break;
            }

            default:
            {
                --Dec;
                break;
            }
            }
        }
    }

    // closes and renames files
    ProdFile.close();
    Temp.close();
    std::remove("products.txt");
    std::rename("temp.txt", "products.txt");
}

// Function that checks if an input ID exists as an ID for a product
bool isAnID(std::string input)
{

    rLogs.open("products.txt");

    std::string line;
    std::smatch match;

    bool result = false;

    // Looping through the text file
    while (getline(rLogs, line))
    {

        // If a match is found between the regex format and the current line
        if (regex_search(line, match, std::regex("[0-9]{5}")))
        {

            // If a match is found between that same line and the ID input by the user
            if (regex_search(line, std::regex(input)))
            {
                result = true;
                break;
            }
            else
            {
                continue;
            }
        }
        else
        {
            continue;
        }
    }
    rLogs.close();
    return result;
}

void removeProduct()
{

    std::string line;
    std::smatch match;

    int count = 0;

    std::string input;

    rLogs.open("products.txt");

    // While loop that shows the user all the IDs and names of the products
    while (getline(rLogs, line))
    {

        // If there is a match between the regex formats and the current line
        if (regex_match(line, std::regex("P[0-9]{5}")))
        {
            std::cout << line << ": ";
        }
        else
        {
            if (regex_match(line, std::regex("[a-zA-Z]{3,20}")))
            {
                std::cout << line << std::endl;
                count++;
            }
            else
            {
                continue;
            }
        }
    }

    rLogs.close();

    // While loop for asking the user what they want to delete
    while (true)
    {

        std::cout << "Enter the ID of the product you wish to delete." << std::endl;
        std::cout << "Enter: ";

        // Input validation
        while (!(std::cin >> input))
        {
            std::cout << "Please input string" << std::endl;
            std::cin.clear();
            std::cin.ignore(123, '\n');
            std::cout << "Enter: ";
        }

        // If what the user input is a real Product ID that's in the file
        if (isAnID(input))
        {
            deleteProd(input);
            break;
        }
        else
        {
            std::cout << "That ID doesn't exist" << std::endl;
            std::cin.clear();
            std::cin.ignore(123, '\n');
            continue;
        }
    }
}


#endif
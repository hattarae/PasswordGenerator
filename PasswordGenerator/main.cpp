#include <iostream>
#include "Password.h"
int main()
{
    Password password;

    bool valid = false; //exception handling: is all user input valid
    while (!valid)
    {
        try 
        {
            password.getLength();
            valid = true;
        }
        catch (const std::runtime_error& e)
        {
            std::cout << "Error: " << e.what() << "\n Please enter a valid length between 1 and 50.\n";
        }
    }
    valid= false;
    while (!valid)
    {
        try
        {
            password.getOptions();
            valid = true;
        }
        catch (const std::runtime_error& e)
        {
            std::cout << "Error: " << e.what() << "\nPlease enter valid character set options.\n";
        }
    }

    std::vector<int> order = password.generateSetOrder();
    password.generatePassword(order);

    std::cout << "Generated password: \n" << password.getPassword() << "\n";

}

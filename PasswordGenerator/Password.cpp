#pragma once
#include "Password.h"

void Password::getLength()
{
	std::cout << "Enter desired length of password (1-50 inclusive): \n";
	length = 0;
	std::cin >> length;
	//if out of length constraints reprompt or exit
	if (length < 1 || length > 50)
	{
		throw std::runtime_error("Invalid length"); 
	}
}


void Password::getOptions()
{
	std::cout << "\nDo you want all of the character set options? (y/n): \n";
	char choice;
	std::cin >> choice;
	if (choice == 'y')
	{
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clear buffer just in case like below
		options.insert(0);
	}
	else if(choice == 'n')
	{
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clear buffer otherwise it doesnt call getline

		std::cout << "\nEnter character set options from: LC-lowercase, UC-uppercase, DG-digits, and SM-symbols (ex. LC DG): \n";
		std::string input;
		std::getline(std::cin, input);
		std::istringstream iss(input);
		std::string token;

		while (iss >> token)
		{
			std::transform(token.begin(), token.end(), token.begin(), ::toupper);
			if (token == "LC") {
				options.insert(1);
			}
			else if (token == "UC") {
				options.insert(2);
			}
			else if (token == "DG") {
				options.insert(3);
			}
			else if (token == "SM") {
				options.insert(4);
			}
			else {
				throw std::runtime_error("Invalid option/s"); 
			}
		}
	}
	else
	{
		throw std::runtime_error("Invalid choice of y/n.");
	}
}


std::vector<int> Password::generateSetOrder()
{
	std::vector<int> setOrder;
	std::mt19937 prng(std::random_device{}());
	std::uniform_int_distribution<int> rand(1, 4);
	while (setOrder.size() < length)
	{
		int result = rand(prng); // get random from options

		if (result == 1 && (options.find(1) != options.end() || options.find(0) != options.end())) {
			setOrder.push_back(result);
		}
		else if (result == 2 && (options.find(2) != options.end() || options.find(0) != options.end())) {
			setOrder.push_back(result);
		}
		else if (result == 3 && (options.find(3) != options.end() || options.find(0) != options.end())) {
			setOrder.push_back(result);
		}
		else if (result == 4 && (options.find(4) != options.end() || options.find(0) != options.end())) {
			setOrder.push_back(result);
		}
	}
	return setOrder;
}

void Password::generatePassword(std::vector<int> setOrder)
{
	std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
	std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string digits = "0123456789";
	std::string symbols = " ~!@#$%^&*()-=+[{]}\\;:'""/?.>,<";

	std::mt19937 prng(std::random_device{}());
	std::uniform_int_distribution<> randLower(0, lowercase.length() - 1);
	std::uniform_int_distribution<> randUpper(0, uppercase.length() - 1);
	std::uniform_int_distribution<> randDigits(0, digits.length() - 1);
	std::uniform_int_distribution<> randSymbols(0, symbols.length() - 1);

	password.clear();

	for (int i = 0; i < length; i++) 
	{
		if (setOrder[i] == 1) 
		{
			password += lowercase[randLower(prng)];
		}
		else if (setOrder[i] == 2)
		{
			password += uppercase[randUpper(prng)];
		}
		else if (setOrder[i] == 3)
		{
			password += digits[randDigits(prng)];
		}
		else if (setOrder[i] == 4)
		{
			password += symbols[randSymbols(prng)];
		}
	}
}

std::string Password::getPassword() const
{
	return password;
}

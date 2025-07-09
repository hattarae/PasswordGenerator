#pragma once
#include <string>
#include <set>
#include <sstream>
#include <random>
#include <algorithm>
#include <iostream>

class Password
{
	int length;
	std::set<int> options;
	std::string password;
public:

	void getLength();
	void getOptions();
	std::vector<int> generateSetOrder();
	void generatePassword(std::vector<int> setOrder); //void: mod member 'passowrd'
	std::string getPassword() const;
};
#pragma once
#include <iostream>

class User {
public:
	int age;
	User(std::string, std::string, int);
private:
	std::string name;
	std::string gender;
};

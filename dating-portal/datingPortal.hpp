#pragma once
#include <iostream>
#include <vector>
#include <string> 
#include <map>
#include <fstream>

class User 
{
public:
	User(std::string, std::string, int, std::string, std::vector<std::string>);       // used in manual creating user
	User(int, std::string, std::string, int, std::string, std::vector<std::string>);  // used in reading users from file
	std::string to_string(bool);         // true for saving to file, false for reading in the application
	uint64_t get_id();
private:
	static uint64_t last_id;
	uint64_t id;
	int age;
	std::vector<std::string> hobby;
	std::string name;
	std::string gender;
	std::string city;

	bool likes_men;
	bool likes_women;
};

User create_new_user();
std::map<uint64_t, User> read_users_from_file(std::string);
void show_users(std::map<uint64_t, User>);

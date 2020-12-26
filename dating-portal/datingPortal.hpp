#pragma once
#include <iostream>
#include <vector>
#include <string> 
#include <map>
#include <fstream>
#include <algorithm>

class User 
{
public:
	User(std::string, std::string, int, std::string, std::vector<std::string>, bool, bool);       // used in manual creating user
	User(int, std::string, std::string, int, std::string, std::vector<std::string>, bool, bool);  // used in reading users from file
	std::string to_string(bool);         // true for saving to file, false for reading in the application
	uint64_t get_id();
	~User() {};
private:
	static uint64_t last_id;
	uint64_t id;
	int age;
	std::vector<std::string> hobby;
	std::string name;
	std::string gender;
	std::string city;

	bool likes_women;
	bool likes_men;
};

class List_of_users
{
public:
	List_of_users();           // creates empty list
	List_of_users(std::string);  // creates list from txt
	void show_users();
	void create_new_user();
	void delete_user(uint64_t);
	~List_of_users() {};
private:
	std::map<uint64_t, User> users;
	std::string file_path;
};

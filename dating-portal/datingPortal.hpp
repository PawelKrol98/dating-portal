#pragma once
#include <iostream>
#include <vector>
#include <string> 
#include <map>
#include <fstream>
#include <algorithm>

struct orientation
{
	bool likes_women;
	bool likes_men;
};

class User 
{
	friend class List_of_users;
public:
	User(std::string, std::string, int, std::string, std::vector<std::string>, orientation);
	std::string to_string(bool);         // true for saving to file, false for reading in the application
	std::string get_gender();
	std::string get_city();
	std::vector<std::string> get_hobby();
	orientation get_orientation();
	int get_age();
	
	~User() {};
private:
	int age;
	std::vector<std::string> hobby;
	std::string name;
	std::string gender;
	std::string city;

	orientation preference;
};

class List_of_users
{
	friend List_of_users filter_for_user(List_of_users, User);
public:
	List_of_users();           // creates empty list
	List_of_users(std::string);  // creates list from txt
	void show_users();
	void create_new_user();
	void delete_user(uint64_t);
	User get_user(uint64_t);
	~List_of_users() {};
private:
	std::map<uint64_t, User> users;         
	std::string file_path;
	uint64_t last_id;
};


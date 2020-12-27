#pragma once
#include <iostream>
#include <vector>
#include <string> 
#include <map>
#include <fstream>
#include <algorithm>

namespace dating_portal
{

struct filter
{
	std::string by_city = "";
	std::vector<std::string> by_hobby = {};
	int min_age = 18;
	int max_age = 1000;
};

struct orientation
{
	bool likes_women;
	bool likes_men;
};

class User
{
public:
	User(std::string, std::string, int, std::string, std::vector<std::string>, orientation, std::string);
	std::string get_name();
	std::string to_string(bool);         // true for saving to file, false for reading in the application
	std::string get_gender();
	std::string get_city();
	std::vector<std::string> get_hobby();
	orientation get_orientation();
	int get_age();
	std::string get_password();
	bool compare_passwords(std::string);

	~User() {};
private:
	int age;
	std::vector<std::string> hobby;
	std::string name;
	std::string gender;
	std::string city;
	std::string password;

	orientation preference;
};

class List_of_users
{
	friend List_of_users filter_for_user(const List_of_users, User);
	friend List_of_users filter_list(const List_of_users, filter);
public:
	List_of_users();           // creates empty list
	List_of_users(std::string);  // creates list from txt
	void show_users();
	void create_new_user();
	void delete_user(uint64_t);
	User get_user(uint64_t);
	std::vector<uint64_t> get_ids();
	~List_of_users() {};
private:
	std::map<uint64_t, User> users;
	std::string file_path;
	uint64_t last_id;
};

class Menu
{
private:
	int num;
	std::string choice;
	List_of_users main_list;
public:
	Menu(List_of_users&);
	void main_menu();
	void user_menu(List_of_users, const uint64_t);
	void filtered_menu(List_of_users);
};


}

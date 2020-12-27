#include "datingPortal.hpp"

User::User(std::string _name = "no_name", std::string _gender = "no", int _age = 18,
	std::string _city = "no_city", std::vector<std::string> _hobby = {}, orientation _preference = { 0, 0})
{
	name = _name;
	gender = _gender;
	age = _age;
	city = _city;
	hobby = _hobby;
	preference.likes_women = _preference.likes_women;
	preference.likes_men = _preference.likes_men;
}


std::string User::to_string(bool for_saving)
{
	if (for_saving)
	{
		std::string interested_in;
		if (preference.likes_women and preference.likes_men) interested_in = "WM";
		else if (preference.likes_women) interested_in = "W";
		else if (preference.likes_men) interested_in = "M";
		std::string str = name + " " + gender + " " + std::to_string(age) + " " + interested_in + " " + city + " " + "hobby ";
		for (std::string i : hobby)
		{
			str += (i + " ");
		}
		return str;
	}
	else
	{
		std::string str = "name " + name + ", " +
			"gender " + gender + ", " +
			"age " + std::to_string(age) + ", " +
			"city " + city + ", " + "hobby: ";
		for (std::string i : hobby)
		{
			str += i + ", ";
		}
		str = str.substr(0, str.length() - 2);
		return str;
	}
}

std::string User::get_gender(){ return gender;}
std::string User::get_city() { return city; }
std::vector<std::string> User::get_hobby() { return hobby; }
int User::get_age() { return age; }
orientation User::get_orientation(){ return preference; }

List_of_users::List_of_users()
{
	users = {};
}

List_of_users::List_of_users(std::string _file_path)
{
	std::ifstream file;
	std::string line;
	file_path = _file_path;
	file.open(file_path);
	std::vector<std::string> lines{};
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			lines.push_back(line);
		}
	}
	int id;
	std::string name;
	std::string gender;
	int age;
	std::string city;
	std::vector<std::string> hobby;
	std::string interested_in;
	orientation preference {0,0};

	for (std::string u : lines)
	{
		hobby = {};
		id = std::stoi(u.substr(0, u.find(" ")));
		u.erase(0, u.find(" ") + 1);
		name = u.substr(0, u.find(" "));
		u.erase(0, u.find(" ") + 1);
		gender = u.substr(0, u.find(" "));
		u.erase(0, u.find(" ") + 1);
		age = std::stoi(u.substr(0, u.find(" ")));
		u.erase(0, u.find(" ") + 1);
		interested_in = u.substr(0, u.find(" "));
		if (interested_in == "W") { preference.likes_men = false; preference.likes_women = true; }
		else if (interested_in == "M") { preference.likes_men = true; preference.likes_women = false; }
		else if (interested_in == "WM") { preference.likes_men = true; preference.likes_women = true; }
		u.erase(0, u.find(" ") + 1);
		city = u.substr(0, u.find(" "));
		u.erase(0, u.find(" ") + 1);
		u += " ";
		while (u.find(" ") != std::string::npos)
		{
			if (u.substr(0, u.find(" ")) != "hobby") hobby.push_back(u.substr(0, u.find(" ")));
			u.erase(0, u.find(" ") + 1);
		}
		User usr(name, gender, age, city, hobby, preference);
		if (id > last_id) last_id = id;
		users.insert({id, usr});
	}
	file.close();
}

void List_of_users::show_users()
{
	int counter{ 0 };
	for (auto u : users)
	{
		counter++;
		std::cout << "[" << u.first << "] " <<u.second.to_string(0) << std::endl;
	}
	std::cout << "Found " << counter << "results.." << std::endl;
}


void List_of_users::create_new_user()
{
	std::string name;
	std::string gender;
	std::string str_age;
	std::string city;
	std::string str_hobby;
	std::string interested_in;
	orientation preference{0,0};
	std::cout << "Please enter your name:" << std::endl;
	std::cin >> name;
	while (gender != "W" and gender != "M")
	{
		std::cout << "Please choose your gender [choose W (woman) or M (man)]:" << std::endl;
		std::cin >> gender;
	}
	std::cout << "Please enter your age:" << std::endl;
	std::cin >> str_age;
	if (std::stoi(str_age) < 18)
	{
		std::cout << "You must be at least 18 years old to make a profile, type anything to exit" << std::endl;
		std::string exit;
		std::cin >> exit;
		return;
	}
	while (interested_in != "W" and interested_in != "M" and interested_in != "WM")
	{
		std::cout << "Who are you looking for? [choose W (woman) or M (man) or WM (woman and man)]" << std::endl;
		std::cin >> interested_in;
		if (interested_in == "W") { preference.likes_men = false; preference.likes_women = true; }
		else if (interested_in == "M") { preference.likes_men = true; preference.likes_women = false; }
		else if (interested_in == "WM") { preference.likes_men = true; preference.likes_women = true; }

	}
	std::cout << "Please enter your city:" << std::endl;
	std::cin >> city;
	std::cout << "Please enter your hobby or hobbies, write anything you like to do in free time or what interests you [seperate by space]:" << std::endl;
	std::cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');
	std::getline(std::cin, str_hobby);
	std::for_each(str_hobby.begin(), str_hobby.end(), [](char& c)          
		{
			c = ::tolower(c);               // changing to lowercase to make filtering easier
		});
	std::vector<std::string> hobby{};
	std::cout << str_hobby << std::endl;
	str_hobby += " ";
	while (str_hobby.find(" ") != std::string::npos)
	{
		hobby.push_back(str_hobby.substr(0, str_hobby.find(" ")));
		str_hobby.erase(0, str_hobby.find(" ") + 1);
	}
	User usr(name, gender, std::stoi(str_age), city, hobby, preference);
	std::ofstream file;
	last_id++;
	file.open(file_path, std::ios::app);      // ios::app to append file
	file << last_id << " " <<usr.to_string(true) << std::endl;
	file.close();
	users.insert({ last_id, usr });
}


void List_of_users::delete_user(uint64_t user_id)
{
	std::ifstream file;
	std::ofstream new_file;
	file.open(file_path);
	new_file.open("temp.txt");
	std::string user_to_delete = std::to_string(user_id) + ' ' + users[user_id].to_string(true);
	std::string line;
	while (std::getline(file, line))
	{
		if (line + ' ' != user_to_delete)       // +' '     because line in txt is one space longer
		{
			new_file << line << std::endl;
		}
	}
	file.close();
	new_file.close();
	std::remove(file_path.c_str());
	std::rename("temp.txt", file_path.c_str());
	users.erase(user_id);
}

List_of_users filter_for_user(List_of_users list, User usr)
{
	List_of_users new_list = List_of_users();
	new_list.file_path = list.file_path;
	new_list.last_id = list.last_id;
	orientation user_preference = usr.get_orientation();
	std::string user_gender = usr.get_gender();
	for (auto u : list.users)
	{
		std::string second_user_gender = u.second.get_gender();
		orientation second_user_preference = u.second.get_orientation();
		if (user_preference.likes_women and second_user_gender == "W"  and user_gender == "M" and second_user_preference.likes_men or
			user_preference.likes_men and second_user_gender == "M" and user_gender == "W" and second_user_preference.likes_women or 
			user_preference.likes_men and second_user_gender == "M" and user_gender == "M" and second_user_preference.likes_men or 
			user_preference.likes_women and second_user_gender == "W" and user_gender == "W" and second_user_preference.likes_women)
			new_list.users.insert({u.first, u.second});
	}
	return new_list;
}

std::vector <uint64_t> List_of_users::get_ids()
{
	std::vector <uint64_t> ids_of_users = {};
	for (auto i : users)
	{
		ids_of_users.push_back(i.first);
	}
	return ids_of_users;
}

List_of_users filter_list(const List_of_users list, filter my_filter)
{
	List_of_users new_list = list;
	if (my_filter.by_city != "")
	{
		for (uint64_t i : new_list.get_ids())
		{
			if (new_list.users[i].get_city() != my_filter.by_city) new_list.users.erase(i);
		}
	}
	if (!my_filter.by_hobby.empty())
	{
		bool hobby_flag;
		for (uint64_t i : new_list.get_ids())
		{
			hobby_flag = false;
			for (std::string h : my_filter.by_hobby)
			{
				for (auto g : new_list.users[i].get_hobby())
				{
					if (g == h) {
						hobby_flag = true;
						break;
					}
				}
				if (hobby_flag) break;
			}
			if (!hobby_flag) new_list.users.erase(i);
		}
	}
	for (uint64_t i : new_list.get_ids())
	{
		if (new_list.users[i].get_age() > my_filter.max_age or new_list.users[i].get_age() < my_filter.min_age) new_list.users.erase(i);
	}
	return new_list;
}

User List_of_users::get_user(uint64_t user_id) { return users[user_id]; }

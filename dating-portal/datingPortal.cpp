#include "datingPortal.hpp"

uint64_t User::last_id{ 0 };

User::User(std::string _name = "no_name", std::string _gender = "no", int _age = 18,
	std::string _city = "no_city", std::vector<std::string> _hobby = {}, bool _likes_women = false, bool _likes_men= false)
{
	name = _name;
	gender = _gender;
	age = _age;
	city = _city;
	hobby = _hobby;
	id = ++last_id;
	likes_women = _likes_women;
	likes_men = _likes_men;
}

User::User(int _id, std::string _name, std::string _gender, int _age,
	std::string _city, std::vector<std::string> _hobby, bool _likes_women, bool _likes_men)
{
	id = _id;
	if (id > last_id) last_id = id;
	name = _name;
	gender = _gender;
	age = _age;
	city = _city;
	hobby = _hobby;
	likes_women = _likes_women;
	likes_men = _likes_men;
}

std::string User::to_string(bool for_saving)
{
	if (for_saving)
	{
		std::string interested_in;
		if (likes_women and likes_men) interested_in = "WM";
		else if (likes_women) interested_in = "W";
		else if (likes_men) interested_in = "M";
		std::string str = std::to_string(id) + " " +
			 name + " " + gender + " " + std::to_string(age) + " " + interested_in + " " + city + " " + "hobby ";
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
		str = str.substr(0, str.length() - 4);
		return str;
	}
}

uint64_t User::get_id()
{
	return id;
}

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
	bool likes_men{false};
	bool likes_women{false};

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
		if (interested_in == "W") { likes_men = false; likes_women = true; }
		else if (interested_in == "M") { likes_men = true; likes_women = false; }
		else if (interested_in == "WM") { likes_men = true; likes_women = true; }
		u.erase(0, u.find(" ") + 1);
		city = u.substr(0, u.find(" "));
		u.erase(0, u.find(" ") + 1);
		u += " ";
		while (u.find(" ") != std::string::npos)
		{
			if (u.substr(0, u.find(" ")) != "hobby") hobby.push_back(u.substr(0, u.find(" ")));
			u.erase(0, u.find(" ") + 1);
		}
		User usr(id, name, gender, age, city, hobby, likes_women, likes_men);
		users.insert({usr.get_id(), usr});
	}
	file.close();
}

void List_of_users::show_users()
{
	for (auto u : users)
	{
		std::cout << u.second.to_string(0) << std::endl;
	}
}

void List_of_users::create_new_user()
{
	std::string name;
	std::string gender;
	std::string str_age;
	std::string city;
	std::string str_hobby;
	std::string interested_in;
	bool likes_men{ false };
	bool likes_women{ false };
	std::cout << "Please enter your name:" << std::endl;
	std::cin >> name;
	while (gender != "W" and gender != "M")
	{
		std::cout << "Please choose your gender [choose W (woman) or M (man)]:" << std::endl;
		std::cin >> gender;
	}
	std::cout << "Please enter your age:" << std::endl;
	std::cin >> str_age;
	while (interested_in != "W" and interested_in != "M" and interested_in != "WM")
	{
		std::cout << "Who are you looking for? [choose W (woman) or M (man) or WM (woman and man)]" << std::endl;
		std::cin >> interested_in;
		if (interested_in == "W") { likes_men = false; likes_women = true; }
		else if (interested_in == "M") { likes_men = true; likes_women = false; }
		else if (interested_in == "WM") { likes_men = true; likes_women = true; }

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
	User usr(name, gender, std::stoi(str_age), city, hobby, likes_women, likes_men);
	std::ofstream file;
	file.open(file_path, std::ios::app);      // ios::app to append file
	file << usr.to_string(true) << std::endl;
	file.close();
	users.insert({ usr.get_id(), usr });
}

void List_of_users::delete_user(uint64_t user_id)
{
	std::ifstream file;
	std::ofstream new_file;
	file.open(file_path);
	new_file.open("temp.txt");
	std::string user_to_delete = users[user_id].to_string(true);
	std::string line;
	while (std::getline(file, line))
	{
		if (line + ' ' != user_to_delete)       // +' '     because line in txt is longer about one space
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

#include "datingPortal.hpp"

uint64_t User::last_id{ 0 };

User::User(std::string _name, std::string _gender, int _age, std::string _city, std::vector<std::string> _hobby)
{
	name = _name;
	gender = _gender;
	age = _age;
	city = _city;
	hobby = _hobby;
	id = ++last_id;
}

User::User(int _id, std::string _name, std::string _gender, int _age, std::string _city, std::vector<std::string> _hobby)
{
	id = _id;
	if (id > last_id) last_id = id;
	name = _name;
	gender = _gender;
	age = _age;
	city = _city;
	hobby = _hobby;
}

std::string User::to_string(bool for_saving)
{
	if (for_saving)
	{
		std::string str = std::to_string(id) + " " +
			 name + " " + gender + " " + std::to_string(age) + " " + city + " " + "hobby ";
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

User create_new_user() {
	std::string name;
	std::string gender;
	std::string str_age;
	std::string city;
	std::string str_hobby;
	std::cout << "Please enter your name:" << std::endl;
	std::cin >> name;
	while (gender != "W" and gender != "M")
	{
		std::cout << "Please choose your gender [choose W (woman) or M (man)]:" << std::endl;
		std::cin >> gender;
	}
	std::cout << "Please enter your age:" << std::endl;
	std::cin >> str_age;
	std::cout << "Please enter your city:" << std::endl;
	std::cin >> city;
	std::cout << "Please enter your hobby or hobbies [seperate by space]:" << std::endl;
	std::cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');
	std::getline(std::cin, str_hobby);
	std::vector<std::string> hobby{};
	std::cout << str_hobby << std::endl;
	str_hobby += " ";
	while (str_hobby.find(" ") != std::string::npos)
	{
		hobby.push_back(str_hobby.substr(0, str_hobby.find(" ")));
		str_hobby.erase(0, str_hobby.find(" ") + 1);
	}
	return User(name, gender, std::stoi(str_age), city, hobby);
}

uint64_t User::get_id()
{
	return id;
}

std::map<uint64_t, User> read_users_from_file(std::string file_path)
{
	std::map<uint64_t, User> list_of_users{};
	std::ifstream file;
	std::string line;
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
		city = u.substr(0, u.find(" "));
		u.erase(0, u.find(" ") + 1);
		u += " ";
		while (u.find(" ") != std::string::npos)
		{
			hobby.push_back(u.substr(0, u.find(" ")));
			u.erase(0, u.find(" ") + 1);
		}
		User usr(id, name, gender, age, city, hobby);
		list_of_users.insert({usr.get_id(), usr});
	}
	file.close();
	return list_of_users;
}

void show_users(std::map<uint64_t, User> list_of_users)
{
	for (auto u : list_of_users)
	{
		std::cout << u.second.to_string(0) << std::endl;
	}
}
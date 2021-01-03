#include "datingPortal.hpp"

using namespace dating_portal;

User::User(std::string _name = "no_name", std::string _gender = "no", int _age = 18,
	std::string _city = "no_city", std::vector<std::string> _hobby = {}, orientation _preference = { 0, 0}, std::string _password = "no")
{
	name = _name;
	gender = _gender;
	age = _age;
	city = _city;
	hobby = _hobby;
	preference.likes_women = _preference.likes_women;
	preference.likes_men = _preference.likes_men;
	password = _password;
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

std::string User::get_name() { return name; }
std::string User::get_gender(){ return gender;}
std::string User::get_city() { return city; }
std::vector<std::string> User::get_hobby() { return hobby; }
int User::get_age() { return age; }
orientation User::get_orientation(){ return preference; }
bool User::compare_passwords(std::string provided_password) { return provided_password == password; }
std::string User::get_password() { return password; }



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
	std::string password;

	for (std::string u : lines)
	{
		hobby = {};
		id = std::stoi(u.substr(0, u.find(" ")));
		u.erase(0, u.find(" ") + 1);
		password = u.substr(0, u.find(" "));
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
		User usr(name, gender, age, city, hobby, preference, password);
		if (id > last_id) {
			last_id = id;
		}
		users.insert({id, usr});
	}
	std::ofstream file2;
	file2.open("last_id.txt");
	file2 << std::to_string(last_id);
	file2.close();
	file.close();
}

void List_of_users::show_users()
{
	uint64_t counter{ 0 };
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
	std::string password;
	std::cout << "Please enter your name:" << std::endl;
	std::cin >> name;
	std::cout << "Please enter your passwords (no spaces):" << std::endl;
	std::cin >> password;
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
	str_hobby += " ";
	while (str_hobby.find(" ") != std::string::npos)
	{
		hobby.push_back(str_hobby.substr(0, str_hobby.find(" ")));
		str_hobby.erase(0, str_hobby.find(" ") + 1);
	}
	User usr(name, gender, std::stoi(str_age), city, hobby, preference, password);
	std::ofstream file;
	last_id++;
	file.open("last_id.txt");
	file << std::to_string(last_id);
	file.close();
	std::ofstream file2;
	file2.open(file_path, std::ios::app);      // ios::app to append file
	file2 << last_id << " " << password <<" " <<usr.to_string(true) << std::endl;
	file2.close();
	users.insert({ last_id, usr });
	std::cout << "Your ID is " << last_id << std::endl;
}


void List_of_users::delete_user(uint64_t user_id)
{
	std::ifstream file;
	std::ofstream new_file;
	file.open(file_path);
	new_file.open("temp.txt");
	std::string user_to_delete = std::to_string(user_id) + ' ' + users[user_id].get_password() + ' ' + users[user_id].to_string(true);
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

List_of_users dating_portal::filter_for_user(const List_of_users list, User usr)
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

List_of_users dating_portal::filter_list(const List_of_users list, filter my_filter)
{
	List_of_users new_list = list;
	if (!my_filter.by_cities.empty())
	{
		bool city_flag;
		for (uint64_t i : new_list.get_ids())
		{
			city_flag = false;
			for (std::string h : my_filter.by_cities)
			{
				if (new_list.users[i].get_city() == h) {
					city_flag = true;
					break;
				}
				if (city_flag) break;
			}
			if (!city_flag) new_list.users.erase(i);
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

User& List_of_users::get_user(uint64_t user_id) { return users[user_id]; }

void List_of_users::send_messages(List_of_users main_list, uint64_t sender_id, uint64_t receiver_id)
{
	std::system("CLS");
	User sender = main_list.get_user(sender_id);
	User receiver = main_list.get_user(receiver_id);
	std::string sender_file_path = "chats/" + std::to_string(sender_id) + "_" + std::to_string(receiver_id) + "_.txt";
	std::string receiver_file_path = "chats/" + std::to_string(receiver_id) + "_" + std::to_string(sender_id) + "_.txt";
	std::ifstream sender_file;
	sender_file.open(sender_file_path);
	std::string line;
	while (std::getline(sender_file, line))
	{
		std::cout << line << std::endl;
	}
	sender_file.close();
	std::ofstream sender_file2;
	std::ofstream receiver_file;
	sender_file2.open(sender_file_path, std::ios::app);
	receiver_file.open(receiver_file_path, std::ios::app);
	std::string message;
	time_t t;   // zdobądź obecny czas
	struct tm* now;
	bool is_friend = false;
	sender_file.open("friends/" + std::to_string(sender_id) + ".txt");
	while (std::getline(sender_file, line))
	{
		if (std::stoi(line) == receiver_id) is_friend = true;
	}
	sender_file.close();
	if (!is_friend)
	{
		std::ofstream sendfr;
		std::ofstream recvfr;
		sendfr.open("friends/" + std::to_string(sender_id) + ".txt", std::ios::app);
		recvfr.open("friends/" + std::to_string(receiver_id) + ".txt", std::ios::app);
		sendfr << std::to_string(receiver_id) + "\n";
		recvfr << std::to_string(sender_id) + "\n";
		sendfr.close();
		recvfr.close();
	}
	std::cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');
	while (true) 
	{
		std::cout << "Type message and press enter, or type exit() to leave chat:" << std::endl;
		std::getline(std::cin, message);
		if ( message == "exit()" ) break;
		t = time(0);
		now = localtime(&t);
		message = std::to_string(now->tm_year + 1900) + '-' + std::to_string(now->tm_mon + 1) + '-' +
			std::to_string(now->tm_mday) + " " + std::to_string(now->tm_hour) + ":" +
			std::to_string(now->tm_min) + " " + message + "\n";
		sender_file2 << "[you]" + message;
		receiver_file << "[" + sender.get_name() + "]" + message;
	}
	sender_file.close();
	receiver_file.close();
}

void List_of_users::set_last_id(uint64_t _last_id)
{
	last_id = _last_id;
}

Menu::Menu(List_of_users& _main_list)
{
	main_list = _main_list;
}

void Menu::select_num()
{
	std::cin >> choice;
	while (choice.empty() or !std::all_of(choice.begin(), choice.end(), ::isdigit))
	{
		std::cout << "type a number, not text" << std::endl;
		std::cin >> choice;
	}
	try 
	{
		num = std::stoi(choice);
	}
	catch (std::exception& e) 
	{
		std::cout << e.what() << std::endl;
	}
}

void Menu::main_menu()
{
    while (true)
    {
		std::system("CLS");
		std::cout << "Welcome to the dating portal, find your love today!" << std::endl;
        std::cout << "[1] log in" << std::endl;
        std::cout << "[2] create an account" << std::endl;
        std::cout << "[3] exit" << std::endl;
		select_num();
        switch (num)
        {
		case 1: 
		{
			std::system("CLS");
			std::string password;
			std::cout << "Please enter your ID " << std::endl;
			select_num();
			std::cout << "Please enter your password" << std::endl;
			std::cin >> password;
			if (main_list.get_user(num).compare_passwords(password)) { user_menu(filter_for_user(main_list, main_list.get_user(num)), num); }
			else {
				std::cout << "Incorrect password (type 'ok' to go back to main menu)" << std::endl;
				std::cin >> choice;
			}
			break; 
		}
        case 2:
            std::system("CLS");
            main_list.create_new_user();
			std::cout << "Accout successfully created! You can sign in with your ID and password (type 'ok' to go back to main menu)" << std::endl;
			std::cin >> choice;
            break;
        case 3:
            return;
            break;
        default:
            break;
        }
    }
}

void Menu::user_menu(List_of_users user_list, const uint64_t user_id)
{
	while (true)
	{
		std::system("CLS");
		std::cout << "Hello " << main_list.get_user(user_id).get_name() << ", how is your day?" <<std::endl;
		std::cout << "[1] search for partners" << std::endl;
		std::cout << "[2] show chats" << std::endl;
		std::cout << "[3] delete an account" << std::endl;
		std::cout << "[4] logout" << std::endl;
		select_num();
		switch (num)
		{
		case 1:
			filtered_menu(user_list, user_id);
			break;
		case 2:
		{
			std::system("CLS");
			std::vector<uint64_t> options;
			std::ifstream file;
			file.open("friends/" + std::to_string(user_id) + ".txt");
			std::string line;
			int id;
			while (std::getline(file, line))
			{
				id = std::stoi(line);
				std::cout << "[" << line << "]" << " " << main_list.get_user(id).get_name() << std::endl;
			}
			std::cout << "choose id to send message to ,type 'ok' to come back" << std::endl;
			std::cin >> choice;
			if (!std::all_of(choice.begin(), choice.end(), ::isdigit)) break;
			user_list.send_messages(main_list, user_id, std::stoi(choice));
			file.close();
		}
			break;
		case 3:
			std::system("CLS");
			std::cout << "Please enter your password to delete the account" << std::endl;
			std::cin >> choice;
			if (main_list.get_user(user_id).compare_passwords(choice))
			{
				main_list.delete_user(user_id);
				return;
			}
			else
			{
				std::cout << "Incorrect password (type 'ok' to contunue)" << std::endl;
				std::cin >> choice;
				break;
			}
		case 4:
			return;
			break;
		default:
			break;
		}
	}
}

void Menu::filtered_menu(List_of_users user_list, const uint64_t user_id)
{
	filter my_filter;
	while (true)
	{
		std::system("CLS");
		std::string print_hobby = "";
		std::string print_cities = "";
		for (auto s : my_filter.by_hobby)
		{
			print_hobby += s + ' ';
		}
		for (auto s : my_filter.by_cities)
		{
			print_cities += s + ' ';
		}
		std::cout << "Choosed filters: " << " hobbies: [" << print_hobby << "] cities: [" << print_cities
			<< "] minimal age: [" << my_filter.min_age << "] maximal age: [" << my_filter.max_age << "]" << std::endl;
		std::cout << "[1] show list of candidates" << std::endl;
		std::cout << "[2] add filter" << std::endl;
		std::cout << "[3] delete filters" << std::endl;
		std::cout << "[4] exit" << std::endl;
		select_num();
		switch (num)
		{
		case 1:
			std::system("CLS");
			filter_list(user_list, my_filter).show_users();
			std::cout << "choose id to send message to ,type 'ok' to come back" << std::endl;
			std::cin >> choice;
			if (!std::all_of(choice.begin(), choice.end(), ::isdigit)) break;
			user_list.send_messages(main_list, user_id, std::stoi(choice));
			break;
		case 2:
			std::cout << "What filter do you want to use?" << std::endl;
			std::cout << "[1] city" << std::endl;
			std::cout << "[2] hobbies" << std::endl;
			std::cout << "[3] minimum age" << std::endl;
			std::cout << "[4] maximum age" << std::endl;
			std::cout << "[5] exit" << std::endl;
			select_num();
			switch (num)
			{
			case 1:
			{
				std::string str_cities;
				std::cout << "Provide city or cities from were candidate should be, seperate by space:" << std::endl;
				std::cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');
				std::getline(std::cin, str_cities);
				str_cities += " ";
				while (str_cities.find(" ") != std::string::npos)
				{
					my_filter.by_cities.push_back(str_cities.substr(0, str_cities.find(" ")));
					str_cities.erase(0, str_cities.find(" ") + 1);
				}
				break;
			}
			case 2:
			{
				std::string str_hobby;
				std::cout << "Provide hobbies candidate should have, seperate by space(program will choose candidate with at least one):" << std::endl;
				std::cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');
				std::getline(std::cin, str_hobby);
				str_hobby += " ";
				while (str_hobby.find(" ") != std::string::npos)
				{
					my_filter.by_hobby.push_back(str_hobby.substr(0, str_hobby.find(" ")));
					str_hobby.erase(0, str_hobby.find(" ") + 1);
				}
				break;
			}
			case 3:
				std::cout << "Provide minimum age of candidate:" << std::endl;
				select_num();
				while (num < 18)
				{
					std::cout << "Age must be at least 18 " << std::endl;
					select_num();
				}
				my_filter.min_age = num;
				break;
			case 4:
				std::cout << "Provide maximum age of candidate" << std::endl;
				select_num();
				while (num < 18)
				{
					std::cout << "Age must be at least 18 " << std::endl;
					select_num();
				}
				my_filter.max_age = num;
				break;
			case 5:
				break;
			default:
				break;
			}
			break;
		case 3:
			my_filter = { {}, {}, 18, 1000 };
			break;
		case 4:
			return;
		default:
			break;
		}
	}
}


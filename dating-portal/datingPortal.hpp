#pragma once
#include <iostream>
#include <vector>
#include <string> 
#include <map>
#include <fstream>
#include <algorithm>
#pragma warning(disable : 4996)
#include <ctime>

namespace dating_portal
{

struct filter                 // struktura filtru, zawiera pola potrzebne do przeszukiwania u�ytkownik�w
{
	std::vector<std::string>  by_cities = {};
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
	std::string get_name();		// zwraca imi� u�ytkownika
	std::string to_string(bool);         // scala wszystkie dane u�ytkownika do stringa, flaga bool definiuje czy sformatowa� je w spos�b do zapisu do pliku txt czy do odczytu w konsoli
	std::string get_gender();	// zwraca p�e� u�ytkownika
	std::string get_city();		// zwraca miasto u�ytkownika
	std::vector<std::string> get_hobby();	// zwraca wszystkie zainteresowania u�ytkownika
	orientation get_orientation();	// zwraca struktur� orientation, kt�ra zawiera informacje o preferencjach u�ytkownika
	int get_age();	// zwraca wiek u�ytkownika
	std::string get_password();		// zwraca has�o u�ytkownika
	bool compare_passwords(std::string);	// zwraca 1 je�li string podany w argumencie jest taki sam jak has�o u�ytkownika i zwraca 0 gdy nie s� takie same


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
	friend List_of_users filter_for_user(const List_of_users, User);	// zwraca list� przefiltrowan� pod preferencje u�ytkownika (p�e�, orientacja)
	friend List_of_users filter_list(const List_of_users, filter);		// zwraca list� przefiltrowan� dodatkowymi parametrami, takimi jak miasto, hobby, wiek
public:
	List_of_users();           // konstruktor bez argumentu tworzy pust� list�
	List_of_users(std::string);  // tworzy list� z pliku txt
	void show_users();		// wypisuje wszystkich u�ytkownik�w z listy w konsoli
	void create_new_user();		// dodaje nowego u�ytkownika do listy, minimalny wiek przy wprowadzaniu to 18, je�li jest mniejszy to program nie pozwoli na stworzenie u�ytkownika
	void delete_user(uint64_t);		//  usuwa u�ytkownika o okre�lonym id z listy oraz z pliku txt
	User& get_user(uint64_t);		//  zwraca referencj� do u�ytkownika o okre�lonym id
	std::vector<uint64_t> get_ids();	// zwraca wektor, kt�ry zawiera wszystkie id u�ytkownik�w z listy
	void send_messages(List_of_users ,uint64_t, uint64_t);  // otwiera chat mi�dzy u�ytkownikami o okre�lonych id z danej listy
	void set_last_id(uint64_t);		// ustawia pole last_id w klasie, co przyda si� do indeksowania kolejnego dodania u�ytkownika
	~List_of_users() {};
private:
	std::map<uint64_t, User> users;
	std::map<uint64_t, std::string> passwords;
	std::string file_path;
	uint64_t last_id;
};

class Menu
{
private:
	int num;      // buffor zawieraj�cy wprowadzon� liczb�
	std::string choice;   // buffor zawieraj�cy wprowadzony ci�g znak�w
	List_of_users main_list;
	void select_num();		// pozwala na wprowadzenie liczby do bufora num, sprawdza czy podany tekst da si� skonwertowa� na liczb�, je�li nie to prosi o podanie liczby jeszcze raz
public:
	Menu(List_of_users&);  // konstruktor tworzy menu w oparciu o podan� list� u�ytkownik�w
	void main_menu();		// otwiera interfejs g��wnego menu logowania
	void user_menu(List_of_users, const uint64_t);		// otwiera menu u�ytkownika z danej listy o okre�lonym id
	void filtered_menu(List_of_users, const uint64_t);		// otwiera menu danego u�ytkownika do szukania kandydat�w
};

}

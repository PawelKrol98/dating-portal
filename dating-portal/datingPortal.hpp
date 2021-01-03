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

struct filter                 // struktura filtru, zawiera pola potrzebne do przeszukiwania uzytkownikow
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
	std::string get_name();		// zwraca imie uzytkownika
	std::string to_string(bool);         // scala wszystkie dane uzytkownika do stringa, flaga bool definiuje czy sformatowac je w sposob do zapisu do pliku txt czy do odczytu w konsoli
	std::string get_gender();	// zwraca plec uzytkownika
	std::string get_city();		// zwraca miasto uzytkownika
	std::vector<std::string> get_hobby();	// zwraca wszystkie zainteresowania uzytkownika
	orientation get_orientation();	// zwraca strukture orientation, ktora zawiera informacje o preferencjach uzytkownika
	int get_age();	// zwraca wiek uzytkownika
	std::string get_password();		// zwraca haslo uzytkownika
	bool compare_passwords(std::string);	// zwraca 1 jesli string podany w argumencie jest taki sam jak haslo uzytkownika i zwraca 0 gdy nie sa takie same


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
	friend List_of_users filter_for_user(const List_of_users, User);	// zwraca liste przefiltrowana pod preferencje uzytkownika (plec, orientacja)
	friend List_of_users filter_list(const List_of_users, filter);		// zwraca liste przefiltrowana dodatkowymi parametrami, takimi jak miasto, hobby, wiek
public:
	List_of_users();           // konstruktor bez argumentu tworzy pusta liste
	List_of_users(std::string);  // tworzy liste z pliku txt
	void show_users();		// wypisuje wszystkich uzytkownikow z listy w konsoli
	void create_new_user();		// dodaje nowego uzytkownika do listy, minimalny wiek przy wprowadzaniu to 18, jesli jest mniejszy to program nie pozwoli na stworzenie uzytkownika
	void delete_user(uint64_t);		//  usuwa uzytkownika o okreslonym id z listy oraz z pliku txt
	User& get_user(uint64_t);		//  zwraca referencje do uzytkownika o okreslonym id
	std::vector<uint64_t> get_ids();	// zwraca wektor, ktory zawiera wszystkie id uzytkownikow z listy
	void send_messages(List_of_users ,uint64_t, uint64_t);  // otwiera chat miedzy uzytkownikami o okreslonych id z danej listy
	void set_last_id(uint64_t);		// ustawia pole last_id w klasie, co przyda sie do indeksowania kolejnego dodania uzytkownika
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
	int num;      // buffor zawierajacy wprowadzona liczbe
	std::string choice;   // buffor zawierajacy wprowadzony ciag znakow
	List_of_users main_list;
	void select_num();		// pozwala na wprowadzenie liczby do bufora num, sprawdza czy podany tekst da sie skonwertowac na liczbe, jesli nie to prosi o podanie liczby jeszcze raz
public:
	Menu(List_of_users&);  // konstruktor tworzy menu w oparciu o podana liste uzytkownikow
	void main_menu();		// otwiera interfejs glownego menu logowania
	void user_menu(List_of_users, const uint64_t);		// otwiera menu uzytkownika z danej listy o okreslonym id
	void filtered_menu(List_of_users, const uint64_t);		// otwiera menu danego uzytkownika do szukania kandydatow
};

}

#include "datingPortal.hpp"
#include <stdlib.h>


int main()
{
    dating_portal::List_of_users main_list("users.txt");          // zainicjowanie listy u�ytkownik�w z pliku users.txt
    std::ifstream file;
    file.open("last_id.txt");                                    // zapisanie najwy�szego id
    if (file.good())
    {
        std::string last_id;
        std::getline(file, last_id);
        main_list.set_last_id(std::stoi(last_id));
    }
    file.close();
    dating_portal::Menu dating_portal(main_list);
    dating_portal.main_menu();                                  //uruchomienie g��wnego menu programu
    return 0;
}




#include "datingPortal.hpp"
#include <stdlib.h>


int main()
{
    dating_portal::List_of_users main_list("users.txt");
    std::ifstream file;
    file.open("last_id.txt");
    if (file.good())
    {
        std::string last_id;
        std::getline(file, last_id);
        main_list.set_last_id(std::stoi(last_id));
    }
    file.close();
    dating_portal::Menu dating_portal(main_list);
    dating_portal.main_menu();
    return 0;
}




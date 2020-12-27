#include "datingPortal.hpp"
#include <stdlib.h>

int main()
{
    dating_portal::List_of_users main_list("users.txt");
    dating_portal::Menu dating_portal(main_list);
    dating_portal.main_menu();
    return 0;
}




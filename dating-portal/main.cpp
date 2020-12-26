#include "datingPortal.hpp"

int main()
{
    List_of_users main_list("users.txt");
    main_list.show_users();
    main_list.delete_user(3);
    main_list.show_users();
    main_list.create_new_user();
    main_list.show_users();
    //main_list.create_new_user();
    //main_list.show_users();
}

#include "datingPortal.hpp"

int main()
{
    List_of_users main_list("users.txt");
    main_list.show_users();
    List_of_users filtered_list = filter_for_user(main_list, main_list.get_user(13));
    filtered_list.show_users();
}

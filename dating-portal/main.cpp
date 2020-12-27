#include "datingPortal.hpp"

int main()
{
    List_of_users main_list("users.txt");
    //main_list.show_users();
    List_of_users filtered_list = filter_for_user(main_list, main_list.get_user(1));
    filter my_filter = { "Krakow", {"polityka", "sport", "spiewanie", "taniec"}, 18, 21 };
    List_of_users filtered_filtered_list = filter_list(filtered_list, my_filter);
    filtered_filtered_list.show_users();
}

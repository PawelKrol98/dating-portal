#include "datingPortal.hpp"

int main()
{
    std::map<uint64_t, User> list_of_users = read_users_from_file("users.txt");
    show_users(list_of_users);
}

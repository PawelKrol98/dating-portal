#include <iostream>
#include "datingPortal.hpp"

int main()
{
    User user1("Pawel", "M", 18);
    User user2("Julka", "M", 28);
    int a = user1.age;
    int b = user2.age * 5;
    a += b;
    b += 2 * a;
}

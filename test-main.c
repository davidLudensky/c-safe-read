#include "safe_input.h"
#include <stdio.h>

int main() {
    int age = 0;
    long id = 0;
    char name[100] = "";
    bool likes_c = true;

    if (get_string("Enter your name: ", name, sizeof(name)))
        printf("Hello, %s!\n", name);

    if (get_int("Enter your age: ", &age))
        printf("You are %d years old.\n", age);

    if (get_long("Enter your ID: ", &id))
        printf("Your ID is %ld.\n", id);

    if (get_bool("Do you like C programming? (yes/no): ", &likes_c))
        printf("You %s C programming.\n", likes_c ? "like" : "don't like");

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "hash.h"

/**
 * main - Entry point of the program.
 *
 * Return: Always 0 (success).
 */
int main(void)
{
   
    hash_table *user_database = hash_table_create(100, simple_hash_function);

    load_users_from_file(user_database, "user_data.txt");
    hash_table_print(user_database);

    const char *search_username = "john_doe";
    User *found_user = hash_table_lookup(user_database, search_username);

    if (found_user != NULL)
    {
        printf("User found:\n");
        printf("Username: %s\n", found_user->username);
        printf("Email: %s\n", found_user->email);
        printf("Age: %d\n", found_user->age);
    }
    else
    {
        printf("User with username '%s' not found.\n", search_username);
    }

    hash_table_destroy(user_database);

    return 0;
}

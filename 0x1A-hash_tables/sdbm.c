#include "hash_tables.h"

unsigned long int sdbm(const unsigned char *str)
{
    unsigned long int hash = 0;
    int b;

    while ((b = *str++))
        hash = b + (hash << 6) + (hash << 16) - hash;

    return hash;
}

#include "hash_tables.h"

unsigned long int hash(const unsigned char *str)
{
    unsigned int hash = 0;
    int c;

    while ((c = *str++))
        hash += c;

    return hash;
}

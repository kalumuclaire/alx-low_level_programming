#include "hash_tables.h"

/**
 * key_index - Returns the index of a key
 *
 * @key: key
 * @size: size of array
 * Return: index of the key
 */

unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
	unsigned long int hash_value, index;

	hash_value = hash_djb2((unsigned char *)key);
	index = hash_value % size;

	return (index);
}

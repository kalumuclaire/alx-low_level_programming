#include "hash_tables.h"

/**
 * hash_table_set - add or update an element in a hash table.
 * @ht: pointer to the hash table.
 * @key: key to add - cannot be an empty string.
 * @value: The value associated with key.
 *
 * Return: upon failure - 0.
 *         otherwise - 1.
 */
int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
	hash_node_t *new;
	char *value_copy;
	unsigned long int index, i;

	if (ht == NULL || key == NULL || *key == '\0' || value == NULL)
		return (0);

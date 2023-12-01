#include "hash_tables.h"
/**
 * hash_table_create - Creates a hash table.
 *
 * @size: size of array
 * Return: pointer
 */

hash_table_t *hash_table_create(unsigned long int size)
{
	hash_table_t *hash_table;
	unsigned long int c;

	hash_table = malloc(sizeof(hash_table_t));

	if (hash_table == NULL)
		return (NULL);

	hash_table->size = size;
	hash_table->array = malloc(sizeof(hash_node_t *) * size);

	if (hash_table->array == NULL)
		return (NULL);

	for (c = 0; c < size; c++)
		hash_table->array[c] = NULL;

	return (hash_table);
}

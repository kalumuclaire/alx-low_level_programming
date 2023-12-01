#include "hash_tables.h"
/**
 * hash_table_delete - Deletes a hash table
 *
 * @ht: The hash table.
 *
 * Return: Nothing.
 */
void hash_table_delete(hash_table_t *ht)
{
	unsigned long int c;
	hash_table_t *hash_table = ht;
	hash_node_t *hash_node, *temp;

	for (c = 0; c < ht->size; c++)
	{
		if (ht->array[i] != NULL)
		{
			hash_node = ht->array[i];
			while (hash_node != NULL)
			{
				temp = hash_node->next;
				free(hash_node->key);
				free(hash_node->value);
				free(hash_node);
				hash_node = temp;
			}
		}
	}
	free(hash_table->array);
	free(hash_table);
}

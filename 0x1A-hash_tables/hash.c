#include "hash.h"

/**
 * hash_table_create - Creates a hash table.
 * @size: The size of the array.
 * @hf: The hash function to be used.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new hash table.
 */
hash_table *hash_table_create(uint32_t size, hashfunction hf) {
    hash_table *ht = malloc(sizeof(*ht));
    if (ht == NULL)
        return (NULL);

    ht->size = size;
    ht->hash = hf;
    ht->elements = calloc(sizeof(entry *), ht->size);
    return ht;
}

/**
 * hash_table_destroy - Destroys a hash table and frees memory.
 * @ht: The hash table to be destroyed.
 */
void hash_table_destroy(hash_table *ht) {
 
    for (uint32_t i = 0; i < ht->size; i++) {
        entry *current = ht->elements[i];
        while (current != NULL) {
            entry *next = current->next;
            free(current->key);
            free(current);
            current = next;
        }
    }
    free(ht->elements);
    free(ht);
}

/**
 * hash_table_print - Prints the contents of a hash table.
 * @ht: The hash table to be printed.
 */
void hash_table_print(hash_table *ht) {
    printf("start table\n");
    for (uint32_t i = 0; i < ht->size; i++) {
        if (ht->elements[i] == NULL) {
            printf("\t%i\t---\n", i);
        } else {
            printf("\t%i\t---\n", i);
            entry *tmp = ht->elements[i];
            while (tmp != NULL) {
                printf("\"%s\"(%p) -", tmp->key, tmp->object);
                tmp = tmp->next;
            }
            printf("\n");
        }
    }
}

/**
 * hash_table_index - Computes the index for a given key in the hash table.
 * @ht: The hash table.
 * @key: The key.
 *
 * Return: The index for the given key.
 */
static size_t hash_table_index(hash_table *ht, const char *key) {
    size_t result = (ht->hash(key, strlen(key)) % ht->size);
    return result;
}

/**
 * hash_table_insert - Inserts an entry into the hash table.
 * @ht: The hash table.
 * @key: The key of the entry.
 * @obj: The object associated with the key.
 *
 * Return: True if the insertion is successful, false otherwise.
 */
bool hash_table_insert(hash_table *ht, const char *key, void *obj) {
    if (key == NULL || obj == NULL)
        return false;

    size_t index = hash_table_index(ht, key);

    if (hash_table_lookup(ht, key) != NULL)
        return false;

    entry *e = malloc(sizeof(*e));
    e->object = obj;
    e->key = malloc(strlen(key) + 1);
    strcpy(e->key, key);

    e->next = ht->elements[index];
    ht->elements[index] = e;

    return true;
}

/**
 * hash_table_lookup - Looks up an entry in the hash table.
 * @ht: The hash table.
 * @key: The key to search for.
 *
 * Return: The object associated with the key, or NULL if not found.
 */
void *hash_table_lookup(hash_table *ht, const char *key) {
    if (key == NULL || ht == NULL)
        return NULL;

    size_t index = hash_table_index(ht, key);
    entry *tmp = ht->elements[index];
    while (tmp != NULL && strcmp(tmp->key, key) != 0) {
        tmp = tmp->next;
    }

    if (tmp == NULL)
        return NULL;

    return tmp->object;
}

/**
 * hash_table_delete - Deletes an entry from the hash table.
 * @ht: The hash table.
 * @key: The key to be deleted.
 *
 * Return: The object associated with the key, or NULL if not found.
 */
void *hash_table_delete(hash_table *ht, const char *key) {
    size_t index = hash_table_index(ht, key);

    entry *prev = NULL;
    entry *current = ht->elements[index];

    while (current != NULL && strcmp(current->key, key) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
    
        return NULL;
    }

    if (prev != NULL) {
        prev->next = current->next;
    } else {
        ht->elements[index] = current->next;
    }

    void *obj = current->object;
    free(current->key);
    free(current);

    return obj;
}

/**
 * simple_hash_function - A simple hash function.
 * @key: The key to be hashed.
 * @length: The length of the key.
 *
 * Return: The hash value.
 */
uint64_t simple_hash_function(const char *key, size_t length) {
    uint64_t hash = 0;
    for (size_t i = 0; i < length; i++) {
        hash = (hash * 31) + key[i];
    }
    return hash;
}/**
 * create_user - Creates a new User structure.
 * @username: The username of the user.
 * @email: The email of the user.
 * @age: The age of the user.
 *
 * Return: A pointer to the newly created User structure.
 */
User *create_user(const char *username, const char *email, int age) {
    User *new_user = malloc(sizeof(User));
    new_user->username = strdup(username);
    new_user->email = strdup(email);
    new_user->age = age;
    return new_user;
}

/**
 * load_users_from_file - Loads user data from a file and inserts it into the hash table.
 * @ht: The hash table.
 * @filename: The name of the file containing user data.
 */
void load_users_from_file(hash_table *ht, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        char *username = strtok(line, ",");
        char *email = strtok(NULL, ",");
        int age = atoi(strtok(NULL, ","));

        User *new_user = create_user(username, email, age);
        hash_table_insert(ht, new_user->username, new_user);
    }

    fclose(file);
}

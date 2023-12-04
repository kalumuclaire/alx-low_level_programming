#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef HASH_H
#define HASH_H

typedef struct {
    char *username;
    char *email;
    int age;
} User;

typedef uint64_t (*hashfunction)(const char*, size_t);

typedef struct entry {
    char *key;
    void *object;
    struct entry *next;
} entry;

typedef struct hash_table {
    uint32_t size;
    hashfunction hash;
    entry **elements;
} hash_table;

uint64_t simple_hash_function(const char* key, size_t length);
static size_t hash_table_index(hash_table *ht, const char *key);
hash_table *hash_table_create(uint32_t size, hashfunction hf);
void hash_table_destroy(hash_table *ht);
void hash_table_print(hash_table *ht);
bool hash_table_insert(hash_table *ht, const char *key, void *obj);
void *hash_table_lookup(hash_table *ht, const char *key);
void *hash_table_delete(hash_table *ht, const char *key);
void load_users_from_file(hash_table *ht, const char *filename);

#endif // HASH_H

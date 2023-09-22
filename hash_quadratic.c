#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

typedef struct {
    int key;
    int value;
    int is_occupied;
} Entry;

typedef struct {
    Entry table[TABLE_SIZE];
} HashTable;

int hash(int key) {
    return key % TABLE_SIZE;
}

int quadratic_probe(int index, int attempt) {
    return (index + attempt * attempt) % TABLE_SIZE;
}

void init_table(HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i].is_occupied = 0;
    }
}

void insert(HashTable *ht, int key, int value) {
    int index = hash(key);
    int attempt = 0;

    while (attempt < TABLE_SIZE) {
        int probe_index = quadratic_probe(index, attempt);
        
        if (!ht->table[probe_index].is_occupied) {
            ht->table[probe_index].key = key;
            ht->table[probe_index].value = value;
            ht->table[probe_index].is_occupied = 1;
            printf("Inserted (%d, %d) at index %d\n", key, value, probe_index);
            return;
        } else if (ht->table[probe_index].key == key) {
            // Update value if key already exists
            ht->table[probe_index].value = value;
            printf("Updated value for key %d at index %d\n", key, probe_index);
            return;
        } else {
            attempt++;
        }
    }

    printf("Failed to insert (%d, %d) - Table is full\n", key, value);
}

int search(HashTable *ht, int key) {
    int index = hash(key);
    int attempt = 0;

    while (attempt < TABLE_SIZE) {
        int probe_index = quadratic_probe(index, attempt);

        if (ht->table[probe_index].is_occupied && ht->table[probe_index].key == key) {
            return ht->table[probe_index].value;
        } else {
            attempt++;
        }
    }

    return -1; // Key not found
}

void delete(HashTable *ht, int key) {
    int index = hash(key);
    int attempt = 0;

    while (attempt < TABLE_SIZE) {
        int probe_index = quadratic_probe(index, attempt);

        if (ht->table[probe_index].is_occupied && ht->table[probe_index].key == key) {
            ht->table[probe_index].is_occupied = 0;
            printf("Deleted key %d at index %d\n", key, probe_index);
            return;
        } else {
            attempt++;
        }
    }

    printf("Key %d not found for deletion\n", key);
}

int main() {
    HashTable ht;
    init_table(&ht);

    insert(&ht, 5, 42);
    insert(&ht, 15, 24);
    insert(&ht, 25, 56);

    int result = search(&ht, 15);
    if (result != -1) {
        printf("Value for key 15 is %d\n", result);
    } else {
        printf("Key 15 not found\n");
    }

    delete(&ht, 15);

    result = search(&ht, 15);
    if (result != -1) {
        printf("Value for key 15 is %d\n", result);
    } else {
        printf("Key 15 not found\n");
    }

    return 0;
}

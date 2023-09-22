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

int hash(int key, int size) {
    return key % size;
}

int second_hash(int key, int size) {
    // Using a prime number for second hash helps reduce clustering
    return (7 - (key % 7)) % size;
}

void init_table(HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i].is_occupied = 0;
    }
}

void insert(HashTable *ht, int key, int value) {
    int attempt = 0;
    int index = hash(key, TABLE_SIZE);
    int step = second_hash(key, TABLE_SIZE);

    while (ht->table[index].is_occupied) {
        if (ht->table[index].key == key) {
            // Update value if key already exists
            ht->table[index].value = value;
            printf("Updated value for key %d at index %d\n", key, index);
            return;
        }
        index = (index + step) % TABLE_SIZE;
        attempt++;
        if(attempt > TABLE_SIZE) {
            printf("Insertion failed.  Most likely table is full\n");
            return;
        }
    }
    
    // FIXME: handle case table is filled.

    ht->table[index].key = key;
    ht->table[index].value = value;
    ht->table[index].is_occupied = 1;
    printf("Inserted (%d, %d) at index %d\n", key, value, index);
}

int search(HashTable *ht, int key) {
    int index = hash(key, TABLE_SIZE);
    int step = second_hash(key, TABLE_SIZE);

    while (ht->table[index].is_occupied) {
        if (ht->table[index].key == key) {
            return ht->table[index].value;
        }
        index = (index + step) % TABLE_SIZE;
    }
    
    return -1; // Key not found
}

void delete(HashTable *ht, int key) {
    int index = hash(key, TABLE_SIZE);
    int step = second_hash(key, TABLE_SIZE);

    while (ht->table[index].is_occupied) {
        if (ht->table[index].key == key) {
            ht->table[index].is_occupied = 0;
            printf("Deleted key %d at index %d\n", key, index);
            return;
        }
        index = (index + step) % TABLE_SIZE;
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


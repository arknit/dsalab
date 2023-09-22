#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    char* value;
    struct Node *next;
} Node;

typedef struct SeparateChainingHashTable {
    int size;
    Node **table;
} SeparateChainingHashTable;

int hash(int key, int size) {
    return key % size;
}

SeparateChainingHashTable *create_hash_table(int size) {
    SeparateChainingHashTable *hash_table = malloc(sizeof(SeparateChainingHashTable));
    hash_table->size = size;
    hash_table->table = malloc(sizeof(Node *) * size);
    for (int i = 0; i < size; i++) {
        hash_table->table[i] = NULL;
    }
    return hash_table;
}

void put(SeparateChainingHashTable *hash_table, int key, char* value) {
    int index = hash(key, hash_table->size);
    Node *new_node = malloc(sizeof(Node));
    new_node->key = key;
    new_node->value = value;
    new_node->next = hash_table->table[index];
    hash_table->table[index] = new_node;
}

char* get(SeparateChainingHashTable *hash_table, int key) {
    int index = hash(key, hash_table->size);
    Node *head = hash_table->table[index];
    while (head != NULL) {
        if (head->key == key) {
            return head->value;
        }
        head = head->next;
    }
    return NULL;
}

void removeAt(SeparateChainingHashTable *hash_table, int key) {
    int index = hash(key, hash_table->size);
    Node *head = hash_table->table[index];
    if (head == NULL) {
        return;
    }
    if (head->key == key) {
        hash_table->table[index] = head->next;
        free(head);
        return;
    }
    Node *prev = head;
    head = head->next;
    while (head != NULL) {
        if (head->key == key) {
            prev->next = head->next;
            free(head);
            return;
        }
        prev = head;
        head = head->next;
    }
}

void print_hash_table(SeparateChainingHashTable *hash_table) {
    for (int i = 0; i < hash_table->size; i++) {
        Node *head = hash_table->table[i];
        while (head != NULL) {
            printf("%d->", head->key);
            head = head->next;
        }
        printf("NULL\n");
    }
}

int main() {
    SeparateChainingHashTable *hash_table = create_hash_table(10);

    put(hash_table, 1, "Bob");
    put(hash_table, 2, "Alice");
    put(hash_table, 3, "Joe");

    printf("%s\n", get(hash_table, 1));
    printf("%s\n", get(hash_table, 2));
    printf("%s\n", get(hash_table, 3));

    removeAt(hash_table, 2);
    printf("%s\n", get(hash_table, 2)== NULL ? "NULL" : get(hash_table, 2));
    print_hash_table(hash_table);
    return 0;
}

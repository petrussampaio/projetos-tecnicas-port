#include <stdio.h>
#include "functions.h"

int hash(char* key) {
    int hash_value = 0;
    int key_len = strlen(key);
    for (int i = 0; i < key_len; i++) {
        hash_value += (int)key[i];
    }
    return hash_value % TABLE_SIZE;
}

struct Node* create_node(char* key, int value) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = (char*)malloc(strlen(key)+1);
    strcpy(node->key, key);
    node->value = value;
    node->next = NULL;
    return node;
}

struct HashTable* create_table() {
    struct HashTable* ht = (struct HashTable*)malloc(sizeof(struct HashTable));
    ht->table = (struct Node**)malloc(TABLE_SIZE * sizeof(struct Node*));
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}

void insert(struct HashTable* ht, char* key, int value) {
    int index = hash(key);
    struct Node* node = create_node(key, value);
    if (ht->table[index] == NULL) {
        ht->table[index] = node;
    } else {
        struct Node* current = ht->table[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }
}

void print_table(struct HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("chain %d: ", i);
        struct Node* current = ht->table[i];
        while (current != NULL) {
            printf("(%s, %d) -> ", current->key, current->value);
            current = current->next;
        }
        printf("NULL\n");
    }
}
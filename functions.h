#define TABLE_SIZE 3

struct Node {
    char* key;
    int value;
    struct Node* next;
};

struct HashTable {
    struct Node** table;
};

int hash(char* key);
struct Node* create_node(char* key, int value);
struct HashTable* create_table();
void insert(struct HashTable* ht, char* key, int value);
void print_table(struct HashTable* ht);
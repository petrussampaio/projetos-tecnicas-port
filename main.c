#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(void) {
    struct HashTable* ht = create_table();
    insert(ht, "D", 2);
    insert(ht, "Q", 0);
    insert(ht, "B", 0);
    insert(ht, "I", 1);
    insert(ht, "M", 2);
    insert(ht, "H", 0);
    insert(ht, "G", 2);
    insert(ht, "U", 1);
    insert(ht, "A", 2);
    insert(ht, "C", 1);
    insert(ht, "R", 1);
    insert(ht, "S", 2);
    insert(ht, "J", 2);
    print_table(ht);
    return 0;
}
#include <stdio.h>

#define SIZE 10

// Hash table structure
struct HashTable {
    int keys[SIZE];
    int values[SIZE];
};

// Hash function
int hash(int key) {
    return key % SIZE;
}

// Initialize hash table
void initHashTable(struct HashTable* ht) {
    for (int i = 0; i < SIZE; i++) {
        ht->keys[i] = -1; // -1 indicates an empty slot
        ht->values[i] = -1;
    }
}

// Insert key-value pair into hash table using linear probing
void insert(struct HashTable* ht, int key, int value) {
    int index = hash(key);

    while (ht->keys[index] != -1) {
        index = (index + 1) % SIZE; // Move to the next slot
    }

    ht->keys[index] = key;
    ht->values[index] = value;
}

// Search for a key in the hash table
int search(struct HashTable* ht, int key) {
    int index = hash(key);

    while (ht->keys[index] != -1) {
        if (ht->keys[index] == key) {
            return ht->values[index];
        }
        index = (index + 1) % SIZE; // Move to the next slot
    }

    return -1; // Key not found
}

int main() {
    struct HashTable ht;
    initHashTable(&ht);

    // Insert key-value pairs
    insert(&ht, 5, 10);
    insert(&ht, 15, 20);
    insert(&ht, 25, 30);
    insert(&ht, 35, 40);
    insert(&ht, 45, 50);

    // Search for values using keys
    printf("Value for key 15: %d\n", search(&ht, 15));
    printf("Value for key 35: %d\n", search(&ht, 35));
    printf("Value for key 25: %d\n", search(&ht, 25));
    printf("Value for key 50: %d\n", search(&ht, 50));

    return 0;
}

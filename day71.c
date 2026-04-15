#include <stdio.h>
#include <string.h>

#define EMPTY -1

int table[100];

// Initialize hash table
void init(int m) {
    for (int i = 0; i < m; i++)
        table[i] = EMPTY;
}

// Insert using quadratic probing
void insert(int key, int m) {
    int h = key % m;

    for (int i = 0; i < m; i++) {
        int idx = (h + i * i) % m;

        if (table[idx] == EMPTY) {
            table[idx] = key;
            return;
        }
    }
}

// Search using quadratic probing
int search(int key, int m) {
    int h = key % m;

    for (int i = 0; i < m; i++) {
        int idx = (h + i * i) % m;

        if (table[idx] == EMPTY)
            return 0;  // NOT FOUND

        if (table[idx] == key)
            return 1;  // FOUND
    }
    return 0;
}

int main() {
    int m, q;
    scanf("%d", &m);
    scanf("%d", &q);

    init(m);

    char op[10];
    int key;

    while (q--) {
        scanf("%s %d", op, &key);

        if (strcmp(op, "INSERT") == 0) {
            insert(key, m);
        } else if (strcmp(op, "SEARCH") == 0) {
            if (search(key, m))
                printf("FOUND\n");
            else
                printf("NOT FOUND\n");
        }
    }

    return 0;
}

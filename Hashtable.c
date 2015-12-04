//
// Created by Evan King on 11/10/15.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct linked_list {
    int key, value;
    struct linked_list *next;
} linked_list;

typedef struct hashtable {
    int size;
    int num_elem;
    int puts;
    struct linked_list **table;
} hashtable;

unsigned int hash(unsigned int a);
void hashtable_create(struct hashtable *self);
void hashtable_put(struct hashtable *self, int key, int value);
int hashtable_get(struct hashtable *self, int key);
void hashtable_remove(struct hashtable *self, int key);
void hashtable_stats(struct hashtable *self);

unsigned int hash(unsigned int a) {
    a = (a ^ 61) ^ (a >> 16);
    a = a + (a << 3);
    a = a ^ (a >> 4);
    a = a * 0x27d4eb2d;
    a = a ^ (a >> 15);
    return a;
}

void hashtable_stats(struct hashtable *self) {
    printf("length = %d, N = %d, puts = %d\n", self->num_elem, self->size, self->puts);
}

void hashtable_create(struct hashtable *self) {
    if (self->size == 0) {
        self->size = 2;
        self->puts = 0;
    }
    self->num_elem = 0;
    self->table = (struct linked_list **) malloc(sizeof(struct linked_list *) * self->size);
    for (int i = 0; i < self->size; i++)
        self->table[i] = NULL;
}

void hashtable_resize(struct hashtable *self) {
    struct hashtable new_table;
    new_table.size = 2 * self->size;
    new_table.puts = self->puts;
    hashtable_create(&new_table);

    struct linked_list *list;
    for (int i = 0; i < self->num_elem; i++) {
        list = self->table[i];
        while (list != NULL) {
            hashtable_put(&new_table, list->key, list->value);
            list = list->next;
        }
    }
    *self = new_table;
}

void hashtable_put(struct hashtable *self, int key, int value) {

    if ((self->num_elem + 1 / self->size) >= 0.75) {
        hashtable_resize(self);
    }

    struct linked_list *list;
    list = (struct linked_list *) malloc(sizeof(struct linked_list));

    unsigned int bucket = (hash(key)) % (self->size);

    list->value = value;
    list->key = key;
    list->next = self->table[bucket];
    self->table[bucket] = list;
    self->num_elem++;
    self->puts++;
}

int hashtable_get(struct hashtable *self, int key) {
    unsigned int bucket = (hash(key)) % (self->size);
    struct linked_list *list = self->table[bucket];
    while (list != NULL) {
        if (list->key == key) {
            return list->value;
        }
        list = list->next;
    }
    printf("ERROR: key %d not found.\n", key);
    exit(1);
}

void hashtable_remove(struct hashtable *self, int key){
    unsigned int bucket = (hash(key)) % (self->size);

    struct linked_list *list = self->table[bucket];
    struct linked_list *previous = list;

    if (list->key == key) {
        self->table[bucket] = list->next;
        self->num_elem--;
        return;
    }else{
        while (list->next != NULL) {
            if (list->key == key) {
                previous->next = list->next;
                free(list);
                self->num_elem--;
                return;
            }
            previous = list;
            list = list->next;
        }

    }
    printf("ERROR: key %d not found.\n", key);
    exit(1);
}

int main() {
    struct hashtable a;
    hashtable_create(&a);
    hashtable_put(&a,0,99);
    hashtable_stats(&a); /* prints: "length = 1, N = 2, puts = 1\n" */
    hashtable_put(&a, 1, 42);
    hashtable_stats(&a);
    assert(hashtable_get(&a, 0) == 99);
    hashtable_remove(&a, 0);
    hashtable_get(&a, 0); /* causes program to exit with exit code 1 */
    hashtable_remove(&a, 0); /* would also cause program to exit with exit code 1 */
    return 0;
}


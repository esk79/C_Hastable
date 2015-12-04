//
// Created by Evan King on 11/10/15.
//


#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H


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


#endif //HASHTABLE_HASHTABLE_H
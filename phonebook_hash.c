#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_hash.h"

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastname[], entry *pHead)
{
    /* choose the coresponding hashTable to find */
    unsigned int hashTarget = djb2Hash(lastname);
    entry *probe = NULL;

    if ( hashTable[hashTarget] == NULL ) {
        return NULL;
    } else {
        probe = hashTable[hashTarget];
    }

    while ( probe != NULL) {
        if (strcasecmp(lastname, probe->lastName) == 0)
            return probe;
        probe = probe->pNext;
    }
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    /* save the newEntry first */
    entry *newEntry = (entry *) malloc(sizeof(entry));
    strcpy(newEntry->lastName, lastName);
    /* calculate the hash value first and check whether the certain index of hashtable is empty*/
    unsigned int hashIndex = djb2Hash(lastName);
    if(hashTable[hashIndex] == NULL) {
        /* the first entry of the certain index of hashtable */
        hashTable[hashIndex] =  newEntry;
        hashTable[hashIndex]->pNext = NULL;
    } else {
        newEntry->pNext = hashTable[hashIndex];
        hashTable[hashIndex] = newEntry;
    }
    return newEntry;
}

unsigned int djb2Hash(char lastName[])
{
    unsigned long hash = 5381;
    int c;

    while ((c = *lastName++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return (unsigned int) hash % HASH_TABLE_SIZE;

}

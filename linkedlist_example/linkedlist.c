#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

/*
    linkedlistexample 0.1 - Trying to implement a doubly linked list.

    Copyright (C) 2023 Hauke Lubenow

    This program is free software: you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/* class List: */

    /* The list has two border-nodes "first" and "last", that aren't used
       for payload. The payload-nodes are created between the border-nodes.
       Beyond the two border-nodes, there is NULL.
       So the list looks like this:

                      NULL-X=N=N=N=N=N=N=N=N=N=N=N=X-NULL

    */

    struct List *List_init(void) {
        struct List *self        = malloc(sizeof(struct List));
        self->first              = malloc(sizeof(struct ListNode));
        self->last               = malloc(sizeof(struct ListNode));
        self->last->next         = NULL;
        self->first->previous    = NULL;
        self->first->next        = self->last;
        self->last->previous     = self->first;
        self->first->payloadtype = type_none;
        self->last->payloadtype  = type_none;
        return self;
    }

    void List_append(struct List *self, int payloadtype, void *payload) {
        /* Creating a new node: */
        struct ListNode *newnode   = malloc(sizeof(struct ListNode));
        newnode->payloadtype       = payloadtype;
        if (payloadtype == type_int) {
            newnode->payload = (int *) payload;
        }
        if (payloadtype == type_string) {
            newnode->payload = malloc(strlen(payload) + 1);
            strcpy(newnode->payload, payload);
        }
        /* Connecting the nodes: */
        self->current        = self->last->previous;
        newnode->next        = self->last;
        newnode->previous    = self->current;
        self->last->previous = newnode;
        self->current->next  = newnode;
    }

    struct ListNode *List_pop(struct List *self) {
        self->current = self->last->previous;
        if (self->current->previous == self->first) {
            puts("Can't pop empty list.");
            return NULL;
        }
        struct ListNode *expiringnode = self->current;
        self->current                 = self->current->previous;
        self->current->next           = self->last;
        self->last->previous          = self->current;
        return expiringnode;
    }

    int List_len(struct List *self) {
        int llen = 0;
        self->current = self->first->next;
        while (self->current != self->last) {
            llen++;
            self->current = self->current->next;
        }
        return llen;
    }

    int *List_getBytesForPrinting(struct List *self) {
        /* Calculating the bytes for reserving memory with malloc():
           We need the length of the list (llen),
           the number of characters of the final string (slen)
           and the number characters of the largest element (maxlen). */
        int *result = malloc(3 * sizeof(int));
        int llen   = 0;
        int slen   = 0;
        int maxlen = 0;
        char s[20];
        int pllen;
        self->current = self->first->next;
        while (self->current != self->last) {
            llen++;
            if (self->current->payloadtype == type_int) {
                sprintf(s, "%d",*((int *) self->current->payload));
                pllen = strlen(s);
                if (pllen > maxlen) {
                    maxlen = pllen;
                }
                slen += pllen;
                /* Two more for ', ':*/
                slen += 2;
            }
            if (self->current->payloadtype == type_string) {
                pllen = strlen((char *) self->current->payload);
                if (pllen > maxlen) {
                    maxlen = pllen;
                }
                slen += pllen;
                /* Two more for ', ':*/
                slen += 2;
                /* Two more for '""':*/
                slen += 2;
            }
            self->current = self->current->next;
        }
        /* Three more for "[]\0":*/
        slen += 3;
        result[0] = llen;
        result[1] = slen;
        result[2] = maxlen;
        return result;
    }

    void List_print(struct List *self) {
        int *result = List_getBytesForPrinting(self);
        int llen   = result[0];
        int slen   = result[1];
        int maxlen = result[2];
        free(result);
        char *s = malloc(slen);
        char *payloadstring = malloc(maxlen + 1);
        int n = 0;
        self->current = self->first->next;
        strcpy(s, "[");
        while (self->current != self->last) {
            if (self->current->payloadtype == type_int) {
                sprintf(payloadstring, "%d", *((int *) self->current->payload));
            }
            if (self->current->payloadtype == type_string) {
                strcpy(payloadstring, "\"");
                strcat(payloadstring, (char *) self->current->payload);
                strcat(payloadstring, "\"");
            }
            strcat(s, payloadstring);
            if (n < llen - 1) {
                strcat(s, ", ");
            }
            n++;
            self->current = self->current->next;
        }
        strcat(s, "]");
        printf("%s\n", s);
        free(s);
        free(payloadstring);
    }

    void List_destruct(struct List *self) {
        struct ListNode *temp;
        self->current = self->first;
        while (self->current->next != NULL) {
            temp = self->current;
            if (temp->payloadtype == type_string) {
                free(temp->payload);
            }
            free(temp);
            self->current = self->current->next;
        }
        free(self);
    }

/* End of class List. */


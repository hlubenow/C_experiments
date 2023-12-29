#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

/*
    linkedlistexample 0.3 - Trying to implement a doubly linked list.

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

/* General functions. */

void *mymalloc(size_t s) {
    /* Just doing malloc(), and checking for success. */
    void *p = malloc(s);
    if (p == NULL) {
        fprintf(stderr, "Warning: malloc() failed!\n");
        exit(EXIT_FAILURE);
    }
    return p;
}

void *myrealloc(void *p, size_t s) {
    /* Just doing realloc(), and checking for success. */
    p = realloc(p, s);
    if (p == NULL) {
        fprintf(stderr, "Warning: realloc() failed!\n");
        exit(EXIT_FAILURE);
    }
    return p;
}

/* End of general functions. */

/* class ListNode: */

    struct ListNode *ListNode_init(void) {
        struct ListNode *self = mymalloc(sizeof(struct ListNode));
        self->payloadstring   = NULL;
    }

    int ListNode_getPayloadStringSize(struct ListNode *self) {
        if (self->payloadtype == type_int) {
            char num[MAXNUMCHARS];
            sprintf(num, "%d", *((int *) self->payload));
            return strlen(num) + 1;
        }
        if (self->payloadtype == type_string) {
            return strlen((char *) self->payload) + 1;
        }
        if (self->payloadtype == type_list) {
            struct List *l = (struct List *) self->payload;
            return strlen(l->printstring) + 1;
        }
    }

    void ListNode_updatePayloadString(struct ListNode *self) {
        if (self->payloadstring == NULL) {
            self->payloadstring = mymalloc(ListNode_getPayloadStringSize(self));
        } else {
            self->payloadstring = myrealloc(self->payloadstring, ListNode_getPayloadStringSize(self));
        }
        if (self->payloadtype == type_int) {
            sprintf(self->payloadstring, "%d", *((int *) self->payload));
        } else if (self->payloadtype == type_string) {
            sprintf(self->payloadstring, "%s", (char *) self->payload);
        } else if (self->payloadtype == type_list) {
            struct List *l = (struct List *) self->payload;
            sprintf(self->payloadstring, "%s", l->printstring);
        }
    }

    void ListNode_printPayloadString(struct ListNode *self) {
        ListNode_updatePayloadString(self);
        printf("%s\n", self->payloadstring);
    }


/* End of class ListNode. */


/* class List: */

    /* The list's nodes are implemented as ListNode-objects.
       The list has two border-nodes "first" and "last", that aren't used
       for payload. The payload-nodes are created between the border-nodes.
       Beyond the two border-nodes, there is NULL.
       So the list looks like this:

                      NULL-X=N=N=N=N=N=N=N=N=N=N=N=X-NULL

    */

    struct List *List_init(void) {
        struct List *self        = mymalloc(sizeof(struct List));
        self->first              = ListNode_init();
        self->last               = ListNode_init();
        self->last->next         = NULL;
        self->first->previous    = NULL;
        self->first->next        = self->last;
        self->last->previous     = self->first;
        self->first->payloadtype = type_none;
        self->last->payloadtype  = type_none;
        self->printstring        = NULL;
        List_updatePrintString(self);
        return self;
    }

    void List_append(struct List *self, int payloadtype, void *payload) {
        /* Creating a new node: */
        struct ListNode *newnode   = ListNode_init();
        newnode->payloadtype       = payloadtype;
        if (payloadtype == type_int) {
            newnode->payload = (int *) payload;
        }
        if (payloadtype == type_string) {
            newnode->payload = (char *) payload;
        }
        if (payloadtype == type_list) {
            newnode->payload = (struct List *) payload;
        }
        /* Connecting the nodes: */
        self->current        = self->last->previous;
        newnode->next        = self->last;
        newnode->previous    = self->current;
        self->last->previous = newnode;
        self->current->next  = newnode;
        List_updatePrintString(self);
    }

    struct ListNode *List_pop(struct List *self) {
        self->current = self->last->previous;
        /* Empty list: */
        if (self->current == self->first) {
            return NULL;
        }
        struct ListNode *expiringnode = self->current;
        self->current                 = self->current->previous;
        self->current->next           = self->last;
        self->last->previous          = self->current;
        List_updatePrintString(self);
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

    int *List_getPrintstringSize(struct List *self) {
        /* Calculating the memory for the printstring (data[1]).
           Also, the length of the list (data[0]) is returned. */
        int *data = mymalloc(2);
        data[0] = 0;
        /* 3, because of "[]\0": */
        data[1] = 3;
        self->current = self->first->next;
        while (self->current != self->last) {
            data[0]++;
            ListNode_updatePayloadString(self->current);
            data[1] += strlen(self->current->payloadstring);
            /* 2, because of ", ": */
            data[1] += 2;
            self->current = self->current->next;
        }
        return data;
    }

    void List_updatePrintString(struct List *self) {
        int *data = List_getPrintstringSize(self);
        if (self->printstring == NULL) {
            self->printstring = mymalloc(data[1]);
        } else {
            self->printstring = myrealloc(self->printstring, data[1]);
        }
        int n = 0;
        self->current = self->first->next;
        strcpy(self->printstring, "[");
        while (self->current != self->last) {
            ListNode_updatePayloadString(self->current);
            if (self->current->payloadtype == type_string) {
                strcat(self->printstring, "\"");
            }
            strcat(self->printstring, self->current->payloadstring);
            if (self->current->payloadtype == type_string) {
                strcat(self->printstring, "\"");
            }
            /* "data[0]" is the length of the list (llen): */
            if (n < data[0] - 1) {
                strcat(self->printstring, ", ");
            }
            n++;
            self->current = self->current->next;
        }
        strcat(self->printstring, "]");
        free(data);
    }

    void List_print(struct List *self) {
        printf("%s\n", self->printstring);
    }

    void List_destruct(struct List *self) {
        struct ListNode *temp;
        self->current = self->first;
        while (self->current->next != NULL) {
            temp = self->current;
            if (temp->payloadtype == type_list) {
                List_destruct(temp->payload);
            }
            if (temp->payloadtype == type_string) {
                free(temp->payload);
            }
            free(temp->payloadstring);
            free(temp);
            self->current = self->current->next;
        }
        free(self->printstring);
        free(self);
    }

/* End of class List. */

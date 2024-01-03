#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

/*
    linkedlistexample 0.4 - Trying to implement a doubly linked list.

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

/* String functions. */

struct List *split(char *separator, char *text) {
   char *s = malloc(strlen(text) + 1);
   struct List *l = List_init();
   strcpy(s, text);
   char *p;
   int i, u;
   int slen = strlen(s);
   int seplen = strlen(separator);
   if (seplen > slen) {
       puts("Warning: Splitstring larger than mainstring.");
   }
   int found = 0;
   int startpoint = 0;
   p = s;
   for (i = 0; i <= slen; i++) {
       found = 1;
       for (u = 0; u < seplen; u++) {
           /* separator not at "s[i] ... s[i + seplen]": */
           if (s[i + u] != separator[u]) {
               found = 0;
               break;
           }
       }
       if (found || s[i] == '\0') {
           s[i] = '\0';
           List_appendString(l, p);
           startpoint = i + seplen;
           if (startpoint <= slen) {
               p = s + startpoint;
           }
       }
    }
    free(s);
    return l;
}

/* End of string functions. */


/* class ListNode: */

    struct ListNode *ListNode_init(void) {
        struct ListNode *self = mymalloc(sizeof(struct ListNode));
        self->payloadstring   = NULL;
    }

    void ListNode_setPayload(struct ListNode *self, int payloadtype, void *payload) {
        self->payloadtype = payloadtype;
        if (self->payloadtype == type_int) {
            self->payload = (int *) payload;
        }
        if (self->payloadtype == type_float) {
            self->payload = (float *) payload;
        }
        if (self->payloadtype == type_double) {
            self->payload = (double *) payload;
        }
        if (self->payloadtype == type_string) {
            self->payload = (char *) payload;
        }
        if (self->payloadtype == type_list) {
            self->payload = (struct List *) payload;
        }
    }

    int ListNode_getPayloadStringSize(struct ListNode *self) {
        if (self->payloadtype == type_int) {
            char num[MAXNUMCHARS];
            sprintf(num, "%d", *((int *) self->payload));
            return strlen(num) + 1;
        }
        if (self->payloadtype == type_float) {
            char num[MAXNUMCHARS];
            sprintf(num, "%f", *((float *) self->payload));
            return strlen(num) + 1;
        }
        if (self->payloadtype == type_double) {
            char num[MAXNUMCHARS];
            sprintf(num, "%f", *((double *) self->payload));
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
        } else if (self->payloadtype == type_float) {
            sprintf(self->payloadstring, "%f", *((float *) self->payload));
        } else if (self->payloadtype == type_double) {
            sprintf(self->payloadstring, "%f", *((double *) self->payload));
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

    void ListNode_destruct(struct ListNode *self, enum bool freepayload) {
        if (self->payloadtype == type_list && freepayload == True) {
            List_destruct(self->payload, True);
        }
        if (self->payloadtype == type_string && freepayload == True) {
            free(self->payload);
        }
        free(self->payloadstring);
        free(self);
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
        struct ListNode *newnode = ListNode_init();
        ListNode_setPayload(newnode, payloadtype, payload);

        /* Connecting the nodes: */
        self->current        = self->last->previous;
        newnode->next        = self->last;
        newnode->previous    = self->current;
        self->last->previous = newnode;
        self->current->next  = newnode;
        List_updatePrintString(self);
    }

    void List_appendString(struct List *self, char *s) {
        /* Appending a string to the list, including allocating memory for it. */
        int s2mem = strlen(s) + 1;
        char *s2 = mymalloc(s2mem);
        strcpy(s2, s);
        List_append(self, type_string, (void *) s2);
    }

    void List_unshift(struct List *self, int payloadtype, void *payload) {
        /* Creating a new node: */
        struct ListNode *newnode = ListNode_init();
        ListNode_setPayload(newnode, payloadtype, payload);

        /* Connecting the nodes: */
        self->current           = self->first->next;
        newnode->previous       = self->first;
        newnode->next           = self->current;
        self->first->next       = newnode;
        self->current->previous = newnode;
        List_updatePrintString(self);
    }

    void List_unshiftString(struct List *self, char *s) {
        /* Appending a string at the beginning of the list, including allocating memory for it. */
        char *s2 = mymalloc(strlen(s) + 1);
        strcpy(s2, s);
        List_unshift(self, type_string, (void *) s2);
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

    void List_Redefine(struct List *self, int number, int newpayloadtype, void *newpayload) {
        int i;
        if (number < 0 || number > (List_len(self) - 1)) {
            printf("Warning: Number %d out of range. Not possible to redefine list element.\n", number);
            return;
        }
        self->current = self->first->next;
        for (i = 0; i < number; i++) {
            self->current = self->current->next;
        }
        self->current->payloadtype = newpayloadtype;
        self->current->payload     = newpayload;
        List_updatePrintString(self);
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
            if (self->current->payloadtype == type_string) {
                /* 2, because of "''" : */
                data[1] += 2;
            }
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
            /* Already updated in "List_getPrintstringSize()": 
                   ListNode_updatePayloadString(self->current);
            */
            if (self->current->payloadtype == type_string) {
                strcat(self->printstring, "'");
            }
            strcat(self->printstring, self->current->payloadstring);
            if (self->current->payloadtype == type_string) {
                strcat(self->printstring, "'");
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

    void List_destruct(struct List *self, enum bool freepayload) {
        struct ListNode *temp;
        self->current = self->first;
        while (self->current->next != NULL) {
            temp = self->current;
            self->current = self->current->next;
            ListNode_destruct(temp, freepayload);
        }
        free(self->printstring);
        free(self);
    }

/* End of class List. */

/*
    linkedlistexample 0.3 - Trying to implement a linked list.

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

#ifndef general_headers
    #define general_headers

    #define MAXNUMCHARS 30

    void *mymalloc(size_t s);
    void *myrealloc(void *p, size_t s);

#endif

#ifndef listnode_headers
    #define listnode_headers

    enum datatypes { type_none = -1, type_int, type_string, type_list };

    /* Headers class ListNode: */

        struct ListNode {
            struct ListNode *previous;
            struct ListNode *next;
            int payloadtype;
            void *payload;
            char *payloadstring;
        };

        struct ListNode *ListNode_init(void);
        int ListNode_getPayloadStringSize(struct ListNode *self);
        void ListNode_updatePayloadString(struct ListNode *self);
        void ListNode_printPayloadString(struct ListNode *self);

    /* End of headers class ListNode. */

#endif


#ifndef list_headers
    #define list_headers

    /* Headers class List: */

        struct List {
            struct ListNode *first;
            struct ListNode *last;
            struct ListNode *current;
            char *printstring;
        };

        struct List *List_init(void);
        void List_append(struct List *self, int payloadtype, void *payload);
        struct ListNode *List_pop(struct List *self);
        int List_len(struct List *self);
        int *List_getPrintstringSize(struct List *self);
        void List_updatePrintString(struct List *self);
        void List_print(struct List *self);
        void List_destruct(struct List *self);
   
    /* End of headers class List. */

#endif

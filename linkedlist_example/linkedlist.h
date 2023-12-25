/*
    linkedlistexample 0.1 - Trying to implement a linked list.

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


#ifndef listheaders
#define listheaders

    enum datatypes { type_none = -1, type_int, type_string };

    /* Headers class List: */

        struct ListNode {
            struct ListNode *previous;
            struct ListNode *next;
            int payloadtype;
            void *payload;
        };

        struct List {
            struct ListNode *first;
            struct ListNode *last;
            struct ListNode *current;
        };

        struct List *List_init(void);
        void List_append(struct List *self, int payloadtype, void *payload);
        struct ListNode *List_pop(struct List *self);
        int List_len(struct List *self);
        int *List_getBytesForPrinting(struct List *self);
        void List_print(struct List *self);
        void List_destruct(struct List *self);
   
    /* End of headers class List. */

#endif


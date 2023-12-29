#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

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

int main(void) {
    struct List *l1 = List_init();
    int a = 3;
    int b = 6;

    puts("Adding three elements.");
    List_append(l1, type_int, &a);
    printf("The length of the list is now: %d\n", List_len(l1));
    List_append(l1, type_int, &b);
    printf("The length of the list is now: %d\n", List_len(l1));
    char *h = mymalloc(10);
    strcpy(h, "Hello");
    List_append(l1, type_string, h);
    printf("The length of the list is now: %d\n", List_len(l1));
    List_print(l1);

    puts("Removing one element.");
    struct ListNode *ln = List_pop(l1);
    List_print(l1);
    printf("The length of the list is now: %d\n", List_len(l1));
    printf("The payload of the removed element is: \"%s\".\n", ln->payloadstring);
    puts("Adding \"Hello\" again:");
    List_append(l1, type_string, h);
    puts("Creating a second list and appending it to the first:");
    struct List *l2 = List_init();
    int c[] = {7, 8, 9};
    int i;
    for (i = 0; i < 3; i++) {
        List_append(l2, type_int, &(c[i]));
    }
    List_print(l2);
    List_append(l1, type_list, l2);
    List_print(l1);
    puts("Removing everything:");
    while (List_len(l1) > 0) {
        ln = List_pop(l1);
        printf("Removed: ");
        ListNode_printPayloadString(ln);
        List_print(l1);
    }
    free(h);
    free(ln);
    List_destruct(l2);
    List_destruct(l1);
    return EXIT_SUCCESS;
}

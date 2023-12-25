#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

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

int main(void) {
    struct List *l = List_init();
    int a = 3;
    int b = 6;

    puts("Adding three elements.");
    List_append(l, type_int, &a);
    printf("The length of the list is now: %d\n", List_len(l));
    List_append(l, type_int, &b);
    printf("The length of the list is now: %d\n", List_len(l));
    List_append(l, type_string, "Hello");
    printf("The length of the list is now: %d\n", List_len(l));
    List_print(l);

    puts("Removing one element.");
    struct ListNode *n = List_pop(l);
    List_print(l);
    printf("The length of the list is now: %d\n", List_len(l));

    printf("The payload of the removed element is: \"%s\".\n", n->payload);
    free(n);
    List_destruct(l);
}

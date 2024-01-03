#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

/*
    linkedlistexample 0.4 - Trying to implement a linked list.

    Comment on "Write in C" ( https://www.youtube.com/watch?v=1S1fISh-pag ) :
    @predatortheme: "First thing to do in C is implement a dynamic list and String wrapper. Lol :D"

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
    puts("Adding three elements.");
    int a[] = {1, 2, 3};
    int i;
    for (i = 0; i < 3; i++) {
        List_append(l1, type_int, &(a[i]));
    }
    float f = 32.567;
    List_append(l1, type_float, &(f));
    double d = 7632.1213;
    List_append(l1, type_double, &(d));
 
 
    printf("The length of the list is now: %d\n", List_len(l1));
    List_appendString(l1, "Hello");
    printf("The length of the list is now: %d\n", List_len(l1));
    List_print(l1);

    puts("Removing one element.");
    struct ListNode *ln = List_pop(l1);
    List_print(l1);
    printf("The length of the list is now: %d\n", List_len(l1));
    puts("The payload of the removed element is:");
    ListNode_printPayloadString(ln);
    puts("Adding \"Hello\" again:");
    List_appendString(l1, "Hello");

    puts("Creating a second list and appending it to the first:");
    struct List *l2 = List_init();
    int b[] = {4, 5, 6};
    for (i = 0; i < 3; i++) {
        List_append(l2, type_int, &(b[i]));
    }
    List_print(l2);
    List_append(l1, type_list, l2);
    List_print(l1);

    char *s = mymalloc(10);
    strcpy(s, "Welt");
    List_Redefine(l1, 3, type_string, s);
    List_print(l1);

    List_unshiftString(l1, "Test");
    List_print(l1);

    puts("Removing everything:");
    while (List_len(l1) > 0) {
        ln = List_pop(l1);
        printf("Removed: ");
        ListNode_printPayloadString(ln);
        List_print(l1);
    }
 
    free(s);
    free(ln);
    List_destruct(l1, True);

    puts("\n\"abconeabctwoabcthreeabcfourabc\" is split at \"abc\" to:");
    struct List *l = split("abc", "abconeabctwoabcthreeabcfourabc");
    List_print(l);
    List_destruct(l, True);

    return EXIT_SUCCESS;
}

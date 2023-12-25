#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
    classemulation 1.0 - Emulating a class in (pure) C.

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

/* class Lamp: */

    struct Lamp {
        char name[100];
        int lightintensity;
        char state[10];
    };

    struct Lamp *Lamp_new(char *name, int lightintensity, char *state) {
        struct Lamp *self = malloc(sizeof(struct Lamp));
        strcpy(self->name, name);
        self->lightintensity = lightintensity;
        strcpy(self->state, state);
        return self;
    }

    void Lamp_switchOn(struct Lamp *self) {
        strcpy(self->state, "on");
        printf("'%s' is on at %d Watt.\n", self->name, self->lightintensity);
    }

    void Lamp_switchOff(struct Lamp *self) {
        strcpy(self->state, "off");
        printf("'%s' is off.\n", self->name);
    }

    void Lamp_newLightBulb(struct Lamp *self, int light) {
        if (strcmp(self->state, "on") == 0) {
            puts("Light bulb can not be changed.");
            printf("First, '%s' has to be switched off.\n", self->name);
        } else {
            self->lightintensity = light;
            printf("Light bulb in '%s' has been changed.\n", self->name);
            printf("The new bulb has %d Watt.\n", self->lightintensity);
            Lamp_switchOn(self);
        }
    }

    void Lamp_destruct(struct Lamp *self) {
        free(self);
    }

/* End of class Lamp. */


int main(void) {
    struct Lamp *lamp1 = Lamp_new("First Lamp", 50, "off");
    struct Lamp *lamp2 = Lamp_new("Second Lamp", 40, "off");
    Lamp_switchOn(lamp1);
    Lamp_switchOn(lamp2);
    Lamp_newLightBulb(lamp2, 100);
    Lamp_switchOff(lamp2);
    Lamp_newLightBulb(lamp2, 100);
    Lamp_destruct(lamp1);
    Lamp_destruct(lamp2);
    return 1;
}

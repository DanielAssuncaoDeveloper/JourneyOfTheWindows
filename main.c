#include <stdio.h>

#include "src/lab/display/mapService.h"
#include "src/lab/display/structs/Entity.h"


int main(void) {
    struct EntityMapper mappers[] = {
        {
            .position = {
                .xPosition = 10,
                .yPosition = 20,
            },
            .entity = {
                .id = 1,
                .type = ACTOR,
                .direction = RIGHT,
                .actor = {
                    .type = HERO,
                }
            }
        }
    };

    map_init(10, 20, mappers);
    map_print();
    return 0;
}

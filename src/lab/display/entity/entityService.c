#include "entityService.h"

#include <stdlib.h>
#include "../position/positionService.h"

struct Entity* get_pointer_to_array_entities(int lentgh) {
    return malloc(sizeof(struct Entity) * lentgh);
}

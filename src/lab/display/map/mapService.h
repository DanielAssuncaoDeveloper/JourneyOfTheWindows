#ifndef MAPSERVICE_H
#define MAPSERVICE_H

struct Map {
    char name[];
    int height;
    int width;
    struct Position** positions;
};

void map_print();
struct Map map_init(int height, int width);

#endif //MAPSERVICE_H

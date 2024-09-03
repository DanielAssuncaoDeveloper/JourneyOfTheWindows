//
// Created by danie on 03/09/2024.
//

#ifndef POSITIONSERVICE_H
#define POSITIONSERVICE_H

struct Position {
    struct Entity* entity;
    int xPosition;
    int yPosition;
};

struct Position** create_matrix_position(int height, int width);

#endif //POSITIONSERVICE_H

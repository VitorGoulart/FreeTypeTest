
#ifndef LEARNOPENGL_PLAYER_H
#define LEARNOPENGL_PLAYER_H


#include "Sprite.h"

class Player : public Sprite {
public:
    void moveRight(float distance, int limit);
    void moveLeft(float distance);
    void moveUp(float distance, int limit);
    void moveDown(float distance);
};


#endif //LEARNOPENGL_PLAYER_H

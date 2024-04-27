
#ifndef LEARNOPENGL_PLAYER_H
#define LEARNOPENGL_PLAYER_H


#include "Sprite.h"

class Player : public Sprite {
public:
    void moveRight(float distance);
    void moveLeft(float distance);
    void moveUp(float distance);
    void moveDown(float distance);
private:
    bool validateMove();
};


#endif //LEARNOPENGL_PLAYER_H

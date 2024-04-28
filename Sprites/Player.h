
#ifndef LEARNOPENGL_PLAYER_H
#define LEARNOPENGL_PLAYER_H


#include "Sprite.h"
#include <unordered_map>

class Player : public Sprite {
public:
    void move(float distance, std::unordered_map<int,bool>& wasdMap);
private:
    void moveRight(float distance);
    void moveLeft(float distance);
    void moveUp(float distance);
    void moveDown(float distance);
};


#endif //LEARNOPENGL_PLAYER_H

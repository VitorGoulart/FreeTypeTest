
#include "Player.h"

void Player::moveRight(float distance, int limit) {
    if (this->pos.x + (this->width/2) < (float) limit) {
        this->pos.x += distance;
    }
}

void Player::moveLeft(float distance) {
    if (this->pos.x - (this->width/2) > 0) {
        this->pos.x -= distance;
    }
}

void Player::moveUp(float distance, int limit) {
    if (this->pos.y + (this->height/2) < (float) limit) {
        this->pos.y += distance;
    }
}

void Player::moveDown(float distance) {
    if (this->pos.y - (this->height/2) > 0) {
        this->pos.y -= distance;
    }
}


#include "Player.h"
#include <GLFW/glfw3.h>

void Player::moveRight(float distance) {
    if (this->pos.x + (this->width/2) < (float) this->screenWidth && validateMove()) {
        this->pos.x += distance;
    }
}

void Player::moveLeft(float distance) {
    if (this->pos.x - (this->width/2) > 0 && validateMove()) {
        this->pos.x -= distance;
    }
}

void Player::moveUp(float distance) {
    if (this->pos.y + (this->height/2) < (float) this->screenHeight && validateMove()) {
        this->pos.y += distance;
    }
}

void Player::moveDown(float distance) {
    if (this->pos.y - (this->height/2) > 0 && validateMove()) {
        this->pos.y -= distance;
    }
}

bool Player::validateMove() {
    if (glfwGetTime() - this->lastMovementUpdateTime > this->movementInterval) {
        this->lastMovementUpdateTime = glfwGetTime();
        return true;
    }
    return false;
}



#include "Player.h"
#include <GLFW/glfw3.h>

void Player::moveRight(float distance) {
    if (this->pos.x + (this->width/2) < (float) this->screenWidth) {
        this->pos.x += distance;
    }
}

void Player::moveLeft(float distance) {
    if (this->pos.x - (this->width/2) > 0) {
        this->pos.x -= distance;
    }
}

void Player::moveUp(float distance) {
    if (this->pos.y + (this->height/2) < (float) this->screenHeight) {
        this->pos.y += distance;
    }
}

void Player::moveDown(float distance) {
    if (this->pos.y - (this->height/2) > 0) {
        this->pos.y -= distance;
    }
}

void Player::move(float distance, std::unordered_map<int, bool>& wasdMap) {
    if (glfwGetTime() - this->lastMovementUpdateTime > this->movementInterval) {
        this->lastMovementUpdateTime = glfwGetTime();
        if (wasdMap[GLFW_KEY_W]) {
            this->moveUp(distance);
        }
        if (wasdMap[GLFW_KEY_A]) {
            this->moveLeft(distance);
        }
        if (wasdMap[GLFW_KEY_S]) {
            this->moveDown(distance);
        }
        if (wasdMap[GLFW_KEY_D]) {
            this->moveRight(distance);
        }
    }
}


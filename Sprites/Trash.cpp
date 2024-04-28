
#include "Trash.h"
#include "GLFW/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "../GameValues.h"

Trash::~Trash() {
    glDeleteVertexArrays(1, &VAO);
}

void Trash::initialize(GLuint texId_, float angle_, int screenWidth_, int screenHeight_, double movementInterval_) {
    glm::vec3 scale_ = glm::vec3(32.0, 32.0, 1.0);
    this->texId = texId_;
    this->scale = scale_;
    this->angle =(float) (rand() % 180);
    this->screenWidth = screenWidth_;
    this->screenHeight = screenHeight_;
    this->width = scale_.x;
    this->height = scale_.y;
    this->spriteRows = 1;
    this->spriteColumns = 1;
    this->currentRow = 0;
    this->lastAnimationUpdateTime = glfwGetTime();
    this->lastMovementUpdateTime = glfwGetTime();
    this->animationInterval = 1;
    this->movementInterval = movementInterval_;
    this->resetPosition();

    this->setVAO();
}

void Trash::resetPosition() {
    this->pos.x = (float) (this->screenWidth + (rand() % (this->screenWidth * 2)));
    this->pos.y = (float) (this->screenHeight + 100 + (rand() % 400));
}

void Trash::update() {
    if (this->pos.x < -100.0 || this->pos.y < -100.0) {
        this->resetPosition();
    }

    if (glfwGetTime() - this->lastMovementUpdateTime > this->movementInterval) {
        this->lastMovementUpdateTime = glfwGetTime();
        this->pos.x -= playerMoveSpeed;
        this->pos.y -= 1.0f;
        this->rotate();
    }

    Sprite::update();
}

void Trash::rotate() {
    int direction = rand() % 4;
    switch (direction) {
        case 0:
            this->angle -= 2.0f;
            break;
        case 1:
            this->angle += 2.0f;
            break;
        default:
            break;
    }
}



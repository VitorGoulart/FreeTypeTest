
#include "Fish.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <random>
#include <GLFW/glfw3.h>

void Fish::update() {
    if (this->pos.x < -100.0) {
        this->resetPosition();
    }

    if (glfwGetTime() - this->lastMovementUpdateTime > this->movementInterval) {
        this->lastMovementUpdateTime = glfwGetTime();
        this->pos.x -= step;
    }

    Sprite::update();
}

void Fish::initialize(GLuint texId_, glm::vec3 scale_, float angle_, float step_, int screenWidth_, int screenHeight_,
                      int rows, int columns, int startingRow,
                      double animationInterval_, double movementInterval_) {
    this->texId = texId_;
    this->scale = scale_;
    this->angle = angle_;
    this->step = step_;
    this->screenWidth = screenWidth_;
    this->screenHeight = screenHeight_;
    this->width = scale_.x;
    this->height = scale_.y;
    this->spriteRows = rows;
    this->spriteColumns = columns;
    this->currentRow = startingRow;
    this->lastAnimationUpdateTime = glfwGetTime();
    this->lastMovementUpdateTime = glfwGetTime();
    this->animationInterval = animationInterval_;
    this->movementInterval = movementInterval_;
    this->resetPosition();

    this->setVAO();
}

void Fish::resetPosition() {
    this->pos.x = (float) (this->screenWidth + 100 + (rand() % 600));
    this->pos.y = (float) (100 + (rand() % (this->screenHeight - 300)));
}

Fish::~Fish() {
    glDeleteVertexArrays(1, &VAO);
}

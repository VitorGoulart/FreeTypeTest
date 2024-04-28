
#include "WaterElement.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <random>
#include <GLFW/glfw3.h>

void WaterElement::update() {
    if (this->pos.x < -100.0) {
        this->resetPosition();
    }

    if (glfwGetTime() - this->lastMovementUpdateTime > this->movementInterval) {
        this->lastMovementUpdateTime = glfwGetTime();
        this->pos.x -= step;
    }

    this->updateAnimation();

    glm::mat4 model = glm::mat4(1);
    model = glm::translate(model, pos);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0, 0.0, 1.0));
    model = glm::scale(model, scale);
    this->shader->setMat4("model", glm::value_ptr(model));
}

void WaterElement::initialize(GLuint texId_, glm::vec3 scale_, float angle_, float step_, int screenWidth_, int screenHeight_,
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

void WaterElement::resetPosition() {
    this->pos.x = (float) (this->screenWidth + 100.0);
    this->pos.y = (float) (100 + (rand() % (this->screenHeight - 300)));
}


#ifndef LEARNOPENGL_FISH_H
#define LEARNOPENGL_FISH_H


#include "Sprite.h"
#include "glm/vec3.hpp"

class Fish : public Sprite {
public:
    Fish() = default;
    ~Fish();
    void initialize(GLuint texId_, glm::vec3 scale_, float angle_, float step_, int screenWidth_, int screenHeight_,
                    int rows, int columns, int startingRow,
                    double animationInterval_, double movementInterval_);
    void resetPosition();
private:
    void update() override;
    float step;
};


#endif //LEARNOPENGL_FISH_H

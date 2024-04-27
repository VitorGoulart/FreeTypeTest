
#ifndef LEARNOPENGL_WATERELEMENT_H
#define LEARNOPENGL_WATERELEMENT_H


#include "Sprite.h"
#include "glm/vec3.hpp"

class WaterElement : public Sprite {
public:
    void initialize(GLuint texId_, glm::vec3 scale_, float angle_, float step_, int screenWidth_, int screenHeight_,
                    int rows, int columns, int startingRow,
                    double animationInterval_, double movementInterval_);
private:
    void update() override;
    void resetPosition();
    float step;
};


#endif //LEARNOPENGL_WATERELEMENT_H

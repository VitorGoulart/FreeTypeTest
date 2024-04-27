#pragma once

#include "glad/glad.h"
#include "glm/vec3.hpp"
#include "../shader.h"

class Sprite {
public:
    Sprite() = default;
    ~Sprite();
    virtual void initialize(GLuint texId_, glm::vec3 pos_, glm::vec3 scale_,
                            float angle_, int screenWidth, int screenHeight,
                            int rows, int columns, int startingRow,
                            double animationInterval, double movementInterval);
    void draw();
    //void terminate();
    inline void setShader(Shader *shader_) {
        this->shader = shader_;
    }
    float getXMax() const;
    float getXMin() const;
    float getYMax() const;
    float getYMin() const;
    bool collidesWith(Sprite *object);
    int screenWidth;
    int screenHeight;

protected:
    virtual void update();
    void setVAO();
    GLuint VAO;
    GLuint texId;
    glm::vec3 pos, scale;
    float angle;
    Shader *shader;
    float width;
    float height;
    int spriteRows;
    int spriteColumns;
    int currentRow;
    int currentColumn;
    double lastAnimationUpdateTime;
    double lastMovementUpdateTime;
    double animationInterval;
    double movementInterval;
};

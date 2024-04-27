#pragma once

#include "glad/glad.h"
#include "glm/vec3.hpp"
#include "../shader.h"

class Sprite {
public:
    Sprite() = default;
    ~Sprite();
    void initialize(GLuint texId_, glm::vec3 pos_ = glm::vec3(0.0, 0.0, 0.0),
                    glm::vec3 scale_ = glm::vec3(1.0, 1.0, 1.0), float angle_ = 0.0);
    void draw();
    //void terminate();
    inline void setShader(Shader *shader_) {
        this->shader = shader_;
    }
    float getXMax();
    float getXMin();
    float getYMax();
    float getYMin();
    bool collidesWith(Sprite *object);

protected:
    void update();
    GLuint VAO;
    GLuint texId;
    glm::vec3 pos, sprite_scale;
    float angle;
    Shader *shader;
    float width;
    float height;
};

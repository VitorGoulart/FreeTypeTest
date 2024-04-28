
#ifndef LEARNOPENGL_TRASH_H
#define LEARNOPENGL_TRASH_H


#include "Sprite.h"

class Trash : public Sprite {
public:
    Trash() = default;
    ~Trash();
    void initialize(GLuint texId_, float angle_, int screenWidth_, int screenHeight_, double movementInterval_);
private:
    void update() override;
    void resetPosition();
    void rotate();
};


#endif //LEARNOPENGL_TRASH_H

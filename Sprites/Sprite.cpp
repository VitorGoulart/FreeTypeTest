#include "Sprite.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

Sprite::~Sprite() {
    glDeleteVertexArrays(1, &VAO);
}

void Sprite::initialize(GLuint texId_, glm::vec3 pos_, glm::vec3 scale_, float angle_) {
    this->texId = texId_;
    this->pos = pos_;
    this->sprite_scale = scale_;
    this->angle = angle_;
    this->width = scale_.x;
    this->height = scale_.y;

    GLfloat vertices[] = {
            //x     y    z    r    g    b    s    t
            //Triangulo 0
            -0.5 , 0.5, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0,  //v0
            -0.5 ,-0.5, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,  //v1
            0.5 , 0.5, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,  //v2
            //Triangulo 1
            -0.5 ,-0.5, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,  //v1
            0.5 ,-0.5, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,  //v3
            0.5 , 0.5, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0   //v2

    };

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //Atributo 0 - posição
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    //Atributo 1 - cor
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    //Atributo 2 - coordenadas de textura
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Sprite::draw() {
    update();

    glBindTexture(GL_TEXTURE_2D, texId);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

void Sprite::update() {
    glm::mat4 model = glm::mat4(1);
    model = glm::translate(model, pos);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0, 0.0, 1.0));
    model = glm::scale(model, sprite_scale);
    shader->setMat4("model", glm::value_ptr(model));
}

float Sprite::getXMax() {
    return this->pos.x + (this->width/2);
}

float Sprite::getXMin() {
    return this->pos.x - (this->width/2);
}

float Sprite::getYMax() {
    return this->pos.y + (this->height/2);
}

float Sprite::getYMin() {
    return this->pos.y - (this->height/2);
}

bool Sprite::collidesWith(Sprite *object) {
    return (this->getXMax() >= object->getXMin() && object->getXMax() >= this->getXMin()) &&
           (this->getYMax() >= object->getYMin() && object->getYMax() >= this->getYMin());
}

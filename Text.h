#pragma once

#include <glad/glad.h>
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "shader.h"
#include <ft2build.h>
#include <map>
#include <GLFW/glfw3.h>
#include FT_FREETYPE_H

class Text {
public:
    Text() = default;
    ~Text();
    int initialize();
    void RenderText(Shader shader, std::string text, float x, float y, float scale, glm::vec3 color);
protected:
    GLuint VAO;
    GLuint VBO;
    Shader* shader;
    FT_Library ft;
    FT_Face face;
    struct Character {
        unsigned int TextureID;  // ID handle of the glyph texture
        glm::vec2   Size;       // Size of glyph
        glm::vec2   Bearing;    // Offset from baseline to left/top of glyph
        unsigned int Advance;    // Offset to advance to next glyph
    };
    std::map<char, Character> Characters; // Estrutura para armazenar cada caracter unico a ser renderizado
};
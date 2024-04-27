#include <iostream>
#include <string>
#include <glad/glad.h>
#include "shader.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"
#include "Sprites/Sprite.h"
#include "Sprites/Player.h"
#include "GameConstants.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow * window, int windowWidth, int windowHeight, Player * player);

void error_callback(int error, const char *msg);

GLuint loadTexture(const std::string& texturePath);

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    srand((int)glfwGetTime());

    glfwSetErrorCallback(error_callback);

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(GameConstants::SCREEN_WIDTH, GameConstants::SCREEN_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader shader("../shaders/texture.vert", "../shaders/texture.frag");

    GLuint backgroundTexId = loadTexture("../Textures/Backgrounds/1_game_background/1_game_background.png");
    GLuint playerTexId = loadTexture("../Textures/Characters/Shark/Idle.png");

    Sprite background;
    background.setShader(&shader);
    background.initialize(backgroundTexId, glm::vec3(800.0, 450.0, 0.0), glm::vec3(GameConstants::SCREEN_WIDTH, GameConstants::SCREEN_HEIGHT, 1.0));

    Player player;
    player.setShader(&shader);
    player.initialize(playerTexId, glm::vec3(200.0, 450.0, 0.0), glm::vec3(200.0, 50.0, 1.0));

    glActiveTexture(GL_TEXTURE0);

    shader.use();

    glm::mat4 projection = glm::ortho(0.0f,1600.0f,0.0f,900.0f,-1.0f,1.0f);
    shader.setMat4("projection", glm::value_ptr(projection));

    shader.setInt("texBuffer", 0);

    // game loop
    while(!glfwWindowShouldClose(window)) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        // input
        glfwPollEvents();
        processInput(window, width, height, &player);

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        background.draw();
        player.draw();

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow * window, int windowWidth, int windowHeight, Player * player) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        player->moveUp(0.5f, windowHeight);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        player->moveLeft(0.5f);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        player->moveDown(0.5f);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        player->moveRight(0.5f, windowWidth);
    }
}

void error_callback(int error, const char *msg) {
    std::string s;
    s = " [" + std::to_string(error) + "] " + msg + '\n';
    std::cerr << s << std::endl;
}

GLuint loadTexture(const std::string& texturePath)
{
    GLuint texId;

    // Gera o identificador da textura na memória
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);

    //Configuração do parâmetro WRAPPING nas coords s e t
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //Confirugação do parâmetro FILTERING na minificação e magnificação da textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        if (nrChannels == 3) //jpg, bmp
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else //png
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texId;
}
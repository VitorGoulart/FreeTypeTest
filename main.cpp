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
#include "Sprites/Fish.h"
#include "Text.h"
#include <unordered_map>
#include "TextRenderer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow * window, Player * player);

void error_callback(int error, const char *msg);

GLuint loadTexture(const std::string& texturePath);

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    srand((int)glfwGetTime());

    glfwSetErrorCallback(error_callback);

    int screenWidth = 1600;
    int screenHeight = 900;

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", nullptr, nullptr);
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

    Shader shader("../../shaders/texture.vert", "../../shaders/animatedTexture.frag");
    Shader textShader("../../shaders/text.vert", "../../shaders/text.frag");

    GLuint backgroundTexId = loadTexture("../../Textures/Backgrounds/1_game_background/1_game_background.png");
    GLuint playerTexId = loadTexture("../../Textures/Characters/Shark/Idle.png");
    GLuint fishTexId = loadTexture("../../Textures/Fish/4.png");


    Sprite background;
    background.setShader(&shader);
    background.initialize(backgroundTexId, glm::vec3(800.0, 450.0, 0.0), glm::vec3(screenWidth, screenHeight, 1.0),
                          0.0, screenWidth, screenHeight, 1, 1, 0, 1, 1);

    Player player;
    player.setShader(&shader);
    player.initialize(playerTexId, glm::vec3(200.0, 450.0, 0.0), glm::vec3(100.0, 100.0, 1.0), 0.0, screenWidth, screenHeight, 1, 4, 0, 0.15, 0.01);

    Fish fish;
    fish.setShader(&shader);
    fish.initialize(fishTexId, glm::vec3(52.0, 16.0, 1.0), 0.0, 3.0, screenWidth, screenHeight, 1, 2, 0, 0.15, 0.01);

    glActiveTexture(GL_TEXTURE0);
    shader.use();

    glm::mat4 projection = glm::ortho(0.0f,1600.0f,0.0f,900.0f,-1.0f,1.0f);
    shader.setMat4("projection", glm::value_ptr(projection));

    TextRenderer text(&textShader, projection);
    text.Load("../../Fontes/arial.ttf", 24);

    shader.setInt("texBuffer", 0);

    // game loop
    while (!glfwWindowShouldClose(window)) {
        glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
        glViewport(0, 0, screenWidth, screenHeight);

        // input
        glfwPollEvents();
        processInput(window, &player);

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        

        background.draw();
        player.draw();
        fish.draw();

        text.RenderText("TEST", 5.0f, 5.0f, 1.0f, glm::vec3(1.0f, 1.0f, 0.0f));

        shader.use();
        

        if (player.collidesWith(&fish)) {
            std::cout << "COLIDIU!!!!!" << std::endl;
        }

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow * window, Player * player) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    std::unordered_map<int,bool> wasdMap = {};
    wasdMap[GLFW_KEY_W] = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
    wasdMap[GLFW_KEY_A] = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
    wasdMap[GLFW_KEY_S] = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
    wasdMap[GLFW_KEY_D] = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
    player->move(10.0f, wasdMap);
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
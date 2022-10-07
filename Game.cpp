#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include "Shader.h"
#include "Button.h"
#include "SpriteRenderer.h"
#include "Input.h"
#include "FrameBuffer.h"
#include "Entity.h"
#include "Font.h"
#include "Level.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void fullscreen();
int init();
bool fscreen = true;


GLFWwindow* window;
GLFWmonitor* monitor;
GLFWvidmode return_struct;


// settings
unsigned int SCR_WIDTH = 1280;
unsigned int SCR_HEIGHT = 720;

int maxWidth;
int maxHeight;

float scr_width = SCR_WIDTH;
float scr_height = SCR_HEIGHT;


glm::mat4 projection;
glm::mat4 altProjection;

//main method
int main()
{
    //if the program does not initialise properly close it
    int i = init();
    if (i != 0) {
        return -1;
    }
    //enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    //init shaders
    ShaderManager sm;
    sm = ShaderManager();
    sm.initShader("texShader", "res/vertex.vs", "res/frag.fs");
    sm.initShader("screenShader", "res/FBOvert.vs", "res/FBOfrag.fs");
    sm.initShader("fontShader", "res/fontVertex.vs", "res/fontFrag.fs");

    //init textures
    TextureManager tm;
    tm = TextureManager();
    tm.initTex("res/homeBackground.png", "background", false);
    tm.initTex("res/colourTile.png", "void", false);
    tm.initTex("res/Ball.png", "ball", true);
    tm.initTex("res/colourCircle.png", "colourCircle", true);
    tm.initTex("res/SquishyMouth.png", "squishyMouth", true);

    //projection matrix
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::ortho(0.f, scr_width, scr_height, 0.f, -1.0f, 1.0f);

    //font for text rendering
    Font font(projection, "res/Amatic-Bold.ttf", 5, sm.getShader("fontShader"));

    //Texture renderer
    TextureRenderer texRender(sm.getShader("texShader"), font);
    //Tile renderer never used (Planned to be used for other levels in the game)
    TileRenderer tileRender(sm.getShader("texShader"));

    //input
    MouseInput mInput(window, SCR_WIDTH, SCR_HEIGHT);
    KeyInput keyInput(window);

    //Frame buffer
    FrameBuffer f(SCR_WIDTH, SCR_HEIGHT);

    //Squishy object, falls into screen from the sky
    Squishy s(glm::vec2(scr_width / 2.f, 128.f), glm::vec2(256, 256), 96, mInput, 0);

    //create the level manager, and give it the correct static Mouse Input value
    LevelManager::mInput = mInput;
    LevelManager level(scr_width, scr_height);
    //add Squishy to level
    level.addSquishy(s);

    //Game Loop
    double secsPerUpdate = 1.0 / 60.0;
    double previous = glfwGetTime();
    double steps = 0.0;
    double lastTime = glfwGetTime();
    int frames = 0;
    int ticks = 0;

    //set clearColour (its never seen, but just in case)
    glClearColor(0.2f, 0.4f, 0.65f, 1.0f);
    while (!glfwWindowShouldClose(window)) {
        //input for closing window
        processInput(window);
        
        double loopStartTime = glfwGetTime();
        double elapsed = loopStartTime - previous;
        previous = loopStartTime;
        steps += elapsed;

        while (steps >= secsPerUpdate) {
            //UPDATE
            level.tick();
            mInput.tick();

            if (keyInput.firstInstance(GLFW_KEY_ENTER)) {
                fullscreen();
            }
            keyInput.tick();
            ticks++;

            steps -= secsPerUpdate;
        }


        //Measure speed
        frames++;
        if (previous - lastTime >= 1.0) {
            std::cout<<frames << "- frames" << std::endl;
            std::cout << ticks << "- ticks" << std::endl;
            frames = 0;
            ticks = 0;
            lastTime += 1.0;
        }

        //RENDER
        f.bind();
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        sm.getShader("texShader").use();
        sm.getShader("texShader").setMat4("projection", projection, false);
        texRender.render(TextureManager::getTex("background"), glm::vec2(0, 0), glm::vec2(scr_width, scr_height), 0, glm::vec3(1.f, 1.f, 1.f));
        level.render(texRender);

        sm.getShader("texShader").setMat4("projection", altProjection, false);

        f.unbind();

        glClear(GL_COLOR_BUFFER_BIT);
        sm.getShader("screenShader").use();

        f.draw();
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //de-allocate all resources
    glDeleteVertexArrays(1, &texRender.quadVAO);
    glDeleteBuffers(1, &texRender.VBO);
    glDeleteBuffers(1, &texRender.EBO);
    glDeleteVertexArrays(1, &tileRender.quadVAO);
    glDeleteBuffers(1, &tileRender.VBO);
    glDeleteBuffers(1, &tileRender.EBO);

    //glfw: terminate
    glfwTerminate();
    return 0;
}

//toggle fullscreen with ENTER
void fullscreen() {
    if (fscreen) {
        glfwSetWindowMonitor(window, monitor, 0, 0, SCR_WIDTH, SCR_HEIGHT, GLFW_DONT_CARE);
        fscreen = false;
    }
    else {
        glfwSetWindowMonitor(window, NULL, maxWidth/2 - SCR_WIDTH/2, maxHeight / 2 - SCR_HEIGHT / 2, SCR_WIDTH, SCR_HEIGHT, GLFW_DONT_CARE);
        fscreen = true;
    }
    scr_width = SCR_WIDTH;
    scr_height = SCR_HEIGHT;
    projection = glm::ortho(0.f, scr_width, scr_height, 0.f, -1.0f, 1.0f);
}

//process any simple inputs, only used for closing the program at the moment
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

//glfw: whenever the window size changed this function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    //make sure the viewport matches the new window dimensions
    glViewport(0, 0, width, height);
}

int init() {
    //glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    //glfw: window creation
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    monitor = glfwGetPrimaryMonitor();

    //get the size of the monitor
    maxWidth = glfwGetVideoMode(monitor)->width; 
    maxHeight = glfwGetVideoMode(monitor)->height;

    glfwSetWindowMonitor(window, NULL, maxWidth / 2 - SCR_WIDTH / 2, maxHeight / 2 - SCR_HEIGHT / 2, SCR_WIDTH, SCR_HEIGHT, GLFW_DONT_CARE);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    return 0;
}
#define STB_IMAGE_IMPLEMENTATION

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Shader.h"
#include "oGL_Tools.h"
#include "Font.h"

#include "Unit/Unit.h"
#include "Unit/Ship.h"
#include "Game/Game.h"
#include "Game/DBase.h"
#include "Game/Clock.h"

// Function prototypes
void processInput(GLFWwindow* window);

// Global variables
Font arialBlk = Font("fonts/ArialBlackLarge.bmp", "fonts/ArialBlack.csv");
Shader stdProgram("vShader.glsl", "fShader.glsl");

double deltaTime = 0.0;
double lastFrame = 0.0;

int lastKeyPressed = 0;

Game gameObj = Game();
Clock c = Clock();

int main() {
    // OpenGL Setup
    GLFWwindow* window = setupOpenGL(800, 800, "Fear God and Dreadnought");
    if (window == NULL) return -1;

    glfwSetWindowPos(window, 850, 50);
    glViewport(0, 0, 800, 800);
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Initialize objects and classes
    stdProgram.initialize();
    gameObj.initialize();

    Ship y = Ship();
    y.loadRecord(gameObj.getDB().getShipRec(1));
    std::cout << y.getHeading() << " with name " << y.getPitch() << "\n";
    y.draw(stdProgram);
    std::cout << "NAME: " << y.getClass() << "\n";




    std::cout << "THIS SHIP IS DA BOMB: " << gameObj.getDB().getShipRec(1).printSummary() << "\n";
    //std::cout << "Number of records: " << x.size() << "\n";

    c.setClock(1984, 7, 21, 8, 30, 0);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT);

        std::cout << c.printDateTime() << "\n";
        c.incrementSec(60*60*24);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

///// Callback functions /////



///// Keyboard input /////


void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (!glfwGetKey(window, lastKeyPressed)) lastKeyPressed = 0;
}

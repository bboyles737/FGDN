#include "oGL_Tools.h"
#include <stb_image.h>

#include <stdio.h>
#include <iostream>

int loadTexture(std::string name, GLenum format) {
    unsigned int tex = 0;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(name.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture: " << name << "\n";
    }
    stbi_image_free(data);

    return tex;
}

int grids(float startX, float startY, float spacing, int num, GLenum usage) {
    float vertices[num*2*4*3] = {0.0f};
    double span = spacing * (num-1);

    for (int i = 0; i < num; i++) {
        int startLine = i*4*3;
        double offset = spacing*i;

        // Horizontal line
        vertices[startLine + 0] = startX;
        vertices[startLine + 1] = startY + offset;
        vertices[startLine + 3 + 0] = startX + span;
        vertices[startLine + 3 + 1] = startY + offset;

        // Vertical line
        vertices[startLine + 6 + 0] = startX + offset;
        vertices[startLine + 6 + 1] = startY;
        vertices[startLine + 9 + 0] = startX + offset;
        vertices[startLine + 9 + 1] = startY + span;
    }
    return setupVAO(vertices, sizeof(vertices), usage);
}

void drawGrids(int gridVAO, int numVerts, glm::vec4 color, glm::vec3 offset, Shader sProgram) {
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, offset);
    sProgram.setMatrix("model", trans);
    sProgram.setDrawColor(color.r, color.g, color.b, color.a);
    glBindVertexArray(gridVAO);
    glDrawArrays(GL_LINES, 0, numVerts);
}

/** Creates a VBO and VAO of four vertexes of a rectangle with
  * the provided upper left hand corner and specified size.
  * To draw, you use GL_TRIANGLE_FAN
  */
int rectangle(float ulX, float ulY, float sizeX, float sizeY, GLenum usage) {
    float vertices[] = {
        ulX,            ulY,            0.0f,
        ulX + sizeX,    ulY,            0.0f,
        ulX + sizeX,    ulY - sizeY,    0.0f,
        ulX,            ulY - sizeY,    0.0f
    };

    return setupVAO(vertices, sizeof(vertices), usage);
}
int rectangleTex(float ulX, float ulY, float sizeX, float sizeY, GLenum usage) {
    float vertices[] = {
        ulX,            ulY,            0.0f,   0.0f, 1.0f,
        ulX + sizeX,    ulY,            0.0f,   1.0f, 1.0f,
        ulX + sizeX,    ulY - sizeY,    0.0f,   1.0f, 0.0f,
        ulX,            ulY - sizeY,    0.0f,   0.0f, 0.0f
    };

    return setupVAOTex(vertices, sizeof(vertices), usage);
}


float capAmount(float amt, float minVal, float maxVal) {
    if (amt < minVal) return minVal;
    else if (amt > maxVal) return maxVal;
    return amt;
}

/** Returns vec3 capped to [0.0-1.0] in x/y/z */
glm::vec3 capVec3(glm::vec3 inVec) {
    inVec.x = capAmount(inVec.x, 0.0, 1.0);
    inVec.y = capAmount(inVec.y, 0.0, 1.0);
    inVec.z = capAmount(inVec.z, 0.0, 1.0);

    return inVec;
}

/** setupVAO will create and return the ID for a VAO given vertex data, size,
  * and how to use it.  You can also tie this in with an EBO if you provide
  * the last two arguments.
  */
int setupVAO(const void* data, GLsizeiptr sizedata, GLenum usage, const void* indexdata, GLsizeiptr sizeindex) {
    unsigned int VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    if (indexdata != NULL) glGenBuffers(1, &EBO);
    else EBO = 0;

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizedata, data, usage);

    if (indexdata != NULL) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeindex, indexdata, usage);
    }

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    return VAO;
}

int setupVAOTex(const void* data, GLsizeiptr sizedata, GLenum usage, const void* indexdata, GLsizeiptr sizeindex) {
    unsigned int VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    if (indexdata != NULL) glGenBuffers(1, &EBO);
    else EBO = 0;

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizedata, data, usage);

    if (indexdata != NULL) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeindex, indexdata, usage);
    }

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    return VAO;
}

int setupVAONormTex(const void* data, GLsizeiptr sizedata, GLenum usage, const void* indexdata, GLsizeiptr sizeindex) {
    unsigned int VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    if (indexdata != NULL) glGenBuffers(1, &EBO);
    else EBO = 0;

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizedata, data, usage);

    if (indexdata != NULL) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeindex, indexdata, usage);
    }

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    return VAO;
}

/** setupOpenGL will initialize GLFW to use OpenGL v3.3 in core profile mode
  * It will also initialize GLAD and return the new window
  * Will print an error message and return NULL if GLFW or GLAD fails.
  */
GLFWwindow* setupOpenGL(int width, int height, std::string name) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return NULL;
    }

    return window;
}

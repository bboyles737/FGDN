#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
    public:
        unsigned int ID;        // program ID

        // Constructor reads and builds the shader
        Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

        void initialize();
        void use(); // Use the active shader

        // Utility functions for uniforms
        // const keyword at end of function declaration means these functions can't
        // change any member variables in the Shader class, such as our program ID
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;

        void setDrawColor(float r, float g, float b, float a) const;
        void setDrawColor(glm::vec4 rgba) const;
        void setMatrix(const std::string &name, glm::mat4 matrix) const;
        void setVec3(const std::string &name, glm::vec3 v) const;
        void setVec4(const std::string &name, glm::vec4 v) const;

        void useOneTex(unsigned int tex1=0) const;
        void useTwoTex(float mixT2 = 0.5, unsigned int tex1=0, unsigned int tex2=1) const;
        void noTextures() const;

    private:
        const GLchar* vertexPath;
        const GLchar* fragmentPath;

};

#endif // SHADER_H

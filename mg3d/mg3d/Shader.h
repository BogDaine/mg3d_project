#pragma once
#include "Renderer.h"
#include "Maths.h"
#include <fstream>
#include <sstream>
#include <unordered_map>

class Shader
{
public:
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const char* vertexPath, const char* fragmentPath);
    
    ~Shader();
    

    // activate the shader
    // ------------------------------------------------------------------------
    void Use() const;
    void Bind() const;
    void Unbind() const;

    void Unbind();

    unsigned int GetID() const;

    // MVP
    unsigned int loc_model_matrix;
    unsigned int loc_view_matrix;
    unsigned int loc_projection_matrix;

    // utility uniform functions
    void SetVec3(const std::string& name, const glm::vec3& value);
    
    void SetVec3(const std::string& name, float x, float y, float z);
    
    void SetMat4(const std::string& name, const glm::mat4& mat);
    
    void SetFloat(const std::string& name, const float& value);

private:
    void Init(const char* vertexPath, const char* fragmentPath);

    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void CheckCompileErrors(unsigned int shader, std::string type);
    
    int GetUniformLocation(const std::string& name);

private:
    unsigned int ID;
    std::unordered_map<std::string, int> uniformLocationCache;
};


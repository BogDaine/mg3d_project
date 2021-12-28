#include "Skybox.h"
#include "Shaders.h"
#include "Cube.h"

//#define STB_IMAGE_IMPLEMENTATION



static bool initialised = false;
static VertexBuffer *VBO;
static VertexArray *VAO;
static IndexArray *IBO;
static VertexBufferLayout *layout;

namespace shaders
{
    //Shader SkyboxShader("..\\shaders\\skybox_vert.shader", "..\\ shaders\\skybox_frag.shader");
    Shader *SkyboxShader;
}

Skybox::Skybox(const GLuint& texture)
{
    m_TextureID = texture;

    if (!initialised)
    {

        VBO = new VertexBuffer;
        VAO = new VertexArray;
        IBO = new IndexArray;
        layout = new VertexBufferLayout;

        layout->push<float>(3); // COORDINATES

        VBO->setData(&qb::skyboxVertices[0], sizeof(qb::skyboxVertices));
        IBO->setData(&qb::skyboxIndices[0], sizeof(qb::skyboxIndices));

        //IBO = IndexArray(&indices[0], indices.size() * sizeof(unsigned int));
        //IBO.bind();

        //std::cout << " yesss" << std::endl;

        VAO->addBuffer(*VBO, *layout);
        shaders::SkyboxShader = new Shader("..\\shaders\\skybox_vert.shader", "..\\shaders\\skybox_frag.shader");
        initialised = true;
    }
}

Skybox::Skybox(std::vector<std::string>& faces)
    :Skybox(Skybox::LoadCubemap(faces))
{

}

Skybox::~Skybox()
{
    glDeleteTextures(1, &m_TextureID);
}

void Skybox::Draw(Camera *pCamera)
{


    glDepthMask(GL_FALSE);
    // ... set view and projection matrix
    shaders::SkyboxShader->Bind();

    shaders::SkyboxShader->SetMat4("view", glm::mat4(glm::mat3(pCamera->GetViewMatrix())));
    shaders::SkyboxShader->SetMat4("projection", pCamera->GetProjectionMatrix());

    glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID);

    VAO->bind();
    IBO->bind();
    GLCall(glDrawElements(GL_TRIANGLES, IBO->getCount(), GL_UNSIGNED_INT, nullptr));
    VAO->unbind();
    IBO->unbind();

    glDepthMask(GL_TRUE);

}

GLuint Skybox::LoadCubemap(std::vector<std::string>& faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    stbi_set_flip_vertically_on_load(false);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}
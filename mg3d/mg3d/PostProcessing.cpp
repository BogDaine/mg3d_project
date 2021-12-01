#include "PostProcessing.h"

static bool initialised = false;
static VertexBuffer* VBO;
static VertexArray* VAO;
static IndexArray* IBO;
static VertexBufferLayout* layout;


namespace shaders
{
	Shader* BlackAndWhite;
}


namespace PostPr
{
	float rectangleVertices[] =
	{
		// Coords    // texCoords
		 1.0f, -1.0f,  1.0f, 0.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		-1.0f,  1.0f,  0.0f, 1.0f,

		 1.0f,  1.0f,  1.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f,  0.0f, 1.0f
	};

}


static void init()
{

    VBO = new VertexBuffer;
    VAO = new VertexArray;
    //IBO = new IndexArray;
    layout = new VertexBufferLayout;

    layout->push<float>(2);
    layout->push<float>(2);

    VBO->setData(&PostPr::rectangleVertices[0], sizeof(PostPr::rectangleVertices));

    //IBO = IndexArray(&indices[0], indices.size() * sizeof(unsigned int));
    //IBO.bind();

    VAO->addBuffer(*VBO, *layout);
    initialised = true;
}

void Renderer::BlackAndWhite(const unsigned int&)
{
	if (!initialised)
		init();



}
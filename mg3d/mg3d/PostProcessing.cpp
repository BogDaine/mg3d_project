#include "PostProcessing.h"
#include "Cfg.h"

static bool initialised = false;
static VertexBuffer* VBO;
static VertexArray* VAO;
static IndexArray* IBO;
static VertexBufferLayout* layout;


namespace shaders
{
	Shader* NoEffects = nullptr;
	Shader* BlackAndWhite = nullptr;
	Shader* Kernel = nullptr;
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


void PostProcess::Init()
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

void PostProcess::NoEffects(const unsigned int& texture)
{
	if (shaders::NoEffects == nullptr)
	{
		shaders::NoEffects = new Shader("..\\shaders\\postprocess\\default_vert.shader",
			"..\\shaders\\postprocess\\black_and_white_frag.shader");
	}

	shaders::NoEffects->Bind();

	VAO->bind();

	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	VAO->unbind();

	shaders::NoEffects->Unbind();
}

void PostProcess::BlackAndWhite(const unsigned int& texture)
{
	if (shaders::BlackAndWhite == nullptr)
	{
		shaders::BlackAndWhite = new Shader("..\\shaders\\postprocess\\default_vert.shader",
											"..\\shaders\\postprocess\\black_and_white_frag.shader");
	}

	shaders::BlackAndWhite->Bind();
	
	VAO->bind();

	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	VAO->unbind();

	shaders::BlackAndWhite->Unbind();
}

void PostProcess::Kernel(const unsigned int& texture)
{
	if (shaders::Kernel == nullptr)
	{
		shaders::Kernel = new Shader("..\\shaders\\postprocess\\default_vert.shader",
			"..\\shaders\\postprocess\\no_effects_frag.shader");
	}

	shaders::Kernel->Bind();

	shaders::Kernel->SetFloat("scr_width", cfg::GetWindowWidth());
	shaders::Kernel->SetFloat("scr_height", cfg::GetWindowHeight());

	VAO->bind();

	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	VAO->unbind();

	shaders::Kernel->Unbind();
}

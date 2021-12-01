#pragma once
#include"Shader.h"

#include "FrameBuffer.h"



namespace PostProcess
{
	void Init();

	void NoEffects(const unsigned int&);

	void BlackAndWhite(const unsigned int&);

	void Kernel(const unsigned int&);
}
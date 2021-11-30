#pragma once

#include <GLCall.h>
#include <IndexArray.h>
#include <VertexBuffer.h>
#include <VertexArray.h>
#include <VertexBufferLayout.h>
#include <vector>

#include "Scene.h"
#include "Camera.h"

class Scene;

namespace Renderer
{
	void Clear();

	void DrawScene(Scene&, Camera*&);
}
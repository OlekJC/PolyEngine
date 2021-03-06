#pragma once

#include "GLUtils.hpp"
#include <Dynarray.hpp>

namespace Poly
{
	struct DebugRenderingBuffers : public BaseObject<>
	{
		DebugRenderingBuffers();
		~DebugRenderingBuffers();

		GLuint VAO = 0;
		GLuint VBO = 0;
	};
}
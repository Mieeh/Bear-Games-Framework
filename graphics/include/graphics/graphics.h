#pragma once

namespace bear { namespace graphics {

	class Graphics {
	public:
		/* Initalize GLEW OpenGL bindings */
		static bool init();

		/* */
		static bool exit();
	};

} }

// Include files for the graphics module to work 
#include"shader.h"
#include"renderable.h"
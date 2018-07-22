#pragma once

namespace bear { namespace ecs { 

#define COMPONENT_COUNT 2

enum component_types {
	TRANSFORM_COMPONENT = 0,
	RENDERABLE_COMPONENT = 1,

	// Used to identify shape type, OBS: placera alltid l�ngst ner f�r sj�lvklara anledningar
	RECTANGLE_COMPONENT,
	TRIANGLE_COMPONENT,
	SPRITE_COMPONENT
};

} } 
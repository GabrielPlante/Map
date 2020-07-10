#pragma once
#include <SDL.h>

#include "TextureWrapper.h"
#include "Color.h"

namespace ge {
	class Circle
	{
	private:
		TextureWrapper texture;
	public:
		//Constructor
		Circle(int32_t radius, Color color, bool disk = false);

		//Get the texture of the circle
		TextureWrapper getTexture() const { return texture; }
	};
}


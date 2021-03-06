#pragma once
#include <SDL.h>

#include "../GameEngine2D/TextureWrapper.h"
#include "../GameEngine2D/Vector2.h"

namespace ian {
	class RendererComponent
	{
	public:
		//Get the size of the texture
		ge::Vector2<int> getSize() const {
			int w, h;
			SDL_QueryTexture(texture.get(), NULL, NULL, &w, &h);
			return { w, h };
		}

		//The texture
		ge::TextureWrapper texture;

		//The position
		unsigned int positionComponentId;

		//The source rectangle, basically what you take of the texture. Keep to null to take the entire texture
		SDL_Rect* srcRect{ nullptr };
	};
}

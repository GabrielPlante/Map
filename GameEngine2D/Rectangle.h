#pragma once
#include <SDL.h>
#include "Vector2.h"

namespace ge {
	//A simple rectangle
	struct Rectangle {
		//The coordinate of the upper left corner of the rectangle
		long int x{ 0 };
		long int y{ 0 };
		//The width and height of the rectangle
		int w{ 0 };
		int h{ 0 };

		//Default constructor
		Rectangle() {}

		//Constructor taking an SDL_Rect
		Rectangle(const SDL_Rect& rect) :x{ rect.x }, y{ rect.y }, w{ rect.w }, h{ rect.h } {}

		//Constructor taking a Vector2, the width and the height
		Rectangle(const Vector2<>& position, const int w, const int h) :x{ position.x }, y{ position.y }, w{ w }, h{ h } {}

		//Constructor taking coordinate as int, the width and the height
		Rectangle(const long int x, const long int y, const int w, const int h) :x{ x }, y{ y }, w{ w }, h{ h } {}

		//Operator override
		bool operator==(const Rectangle& other) const { return x == other.x && y == other.y && w == other.w && h == other.h; }

		//Resize the rectangle with a delta
		inline void resize(double delta);

		//Rectangle to SDL_Rect
		inline SDL_Rect toSDL_Rect() const;

		//Check if two rectangle are overlapping, return true if they are
		inline bool overlap(const Rectangle& rectangle) const;
	};

	SDL_Rect Rectangle::toSDL_Rect() const {
		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
		return rect;
	}

	bool Rectangle::overlap(const Rectangle& rectangle) const {
		//Check if an rectangle is more left than the other
		if (x > rectangle.x + rectangle.w || rectangle.x > x + w)
			return false;
		//Check if an rectangle is above the other
		if (y > rectangle.y + rectangle.h || rectangle.y > y + h)
			return false;
		return true;
	}

	void Rectangle::resize(double delta) {
		w = static_cast<int>(w * delta);
		h = static_cast<int>(h * delta);
	}
}

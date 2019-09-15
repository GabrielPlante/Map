#pragma once
#include <SDL.h>
#include "Angle.h"

//Find the minimum of two element
template <typename P>
P min(P arg1, P arg2) {
	return arg1 > arg2 ? arg2 : arg1;
}

//Find the maximum of two element
template <typename P>
P max(P arg1, P arg2) {
	return arg1 < arg2 ? arg2 : arg1;
}

//Everything is public in a struct if not defined
template <typename T = long int>
struct Position
{
	//The position is stocked here
	T x;
	T y;

	//Constructor taking position
	Position(T x, T y) {
		this->x = x;
		this->y = y;
	}

	//Constructor with a SDL_Point
	Position(const SDL_Point& point)
		:x{ point.x }, y{ point.y }
	{
	}

	//Default constructor
	Position() {}

	//Position to a SDL_Point
	SDL_Point toSDL_Point() const {
		SDL_Point point;
		point.x = static_cast<int>(x);
		point.y = static_cast<int>(y);
		return point;
	}

	//Find the angle between the point and the direction
	Angle angle(const Position<float> destination) const {
		constexpr float PI = 3.14159265f;
		Angle directionAngle{ static_cast<float>(atan2(-(destination.y - y), destination.x - x)) };
		if (directionAngle.get() < 0)
			directionAngle.set(std::abs(directionAngle.get()));
		else
			directionAngle.set(2 * PI - directionAngle.get());
		return directionAngle;
	}

	//http://mathworld.wolfram.com/Circle-LineIntersection.html
	//Return true if the line formed by this position and the endLinePoint intersect with the given circle
	bool lineIntersectCircle(const Position<T>& endLinePoint, const Position<>& circlePosition, int circleRadius) {
		int x1 = static_cast<int>(x - circlePosition.x);
		int y1 = static_cast<int>(y - circlePosition.y);
		int x2 = static_cast<int>(endLinePoint.x - circlePosition.x);
		int y2 = static_cast<int>(endLinePoint.y - circlePosition.y);
		return pow(circleRadius, 2) * (pow(x2 - x1, 2) + pow(y2 - y1, 2)) - pow(x1 * y2 - x2 * y1, 2) >= 0;
	}

	//https://yal.cc/rectangle-circle-intersection-test/
	//Return true if the rectangle intersect the circle, with this position the center of the circle
	//The position x and y are the circle position and the rectangle position should be the center of the rectangle
	bool rectIntersectCircle(const Position<>& rectanglePosition, int w, int h, int circleRadius) {
		int deltaX = static_cast<int>(x - max(rectanglePosition.x, min(x, rectanglePosition.x + w)));
		int deltaY = static_cast<int>(y - max(rectanglePosition.y, min(y, rectanglePosition.x + h)));
		return (pow(deltaX, 2) + pow(deltaY, 2)) <= pow(circleRadius, 2);
	}

	//Return the distance between two point, squared. The other point is a float
	int distanceSquared(const Position<float> destination) const {
		return static_cast<int>(pow(x - destination.x, 2) + pow(y - destination.y, 2));
	}

	//Return the distance between two point, squared. The other point is a long
	int distanceSquared(const Position<> destination) const {
		return distanceSquared(Position<float>{static_cast<float>(destination.x), static_cast<float>(destination.y)});
	}

	//Operator == override
	bool operator==(const Position<T>& other) {
		return x == other.x && y == other.y;
	}
};

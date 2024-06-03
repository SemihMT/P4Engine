#pragma once
#include <glm/vec2.hpp>

namespace dae
{
	/*struct Rectangle
	{
		glm::vec2 topLeft;
		float width;
		float height;
	};*/

	struct IColor
	{
		int r;
		int g;
		int b;
		bool operator<(const IColor& other) const
		{
			return std::tie(r, g, b) < std::tie(other.r, other.g, other.b);
		}

	};
}

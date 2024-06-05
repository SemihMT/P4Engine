#pragma once
#include <SDL_render.h>
#include <glm/vec2.hpp>

namespace dae
{
	inline void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
	{
		const int32_t diameter = (radius * 2);

		int32_t x = (radius - 1);
		int32_t y = 0;
		int32_t tx = 1;
		int32_t ty = 1;
		int32_t error = (tx - diameter);

		while (x >= y)
		{
			//  Each of the following renders an octant of the circle
			SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
			SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
			SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
			SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
			SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
			SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
			SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
			SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

			if (error <= 0)
			{
				++y;
				error += ty;
				ty += 2;
			}

			if (error > 0)
			{
				--x;
				tx += 2;
				error += (tx - diameter);
			}
		}
	}

	struct Collider
	{
		glm::vec2 pos;
		glm::vec2 size;
	};

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
	struct Ray
	{
		glm::vec2 origin;
		glm::vec2 direction;
	};

	struct HitResult
	{
		bool hit{ false };
		glm::vec2 hitPoint{};
		glm::vec2 hitNormal{};
		float hitDistance{};
	};

	inline bool PointVsRect(const glm::vec2& p, const Collider& r)
	{
		return (p.x >= r.pos.x && p.y >= r.pos.y && p.x < r.pos.x + r.size.x && p.y < r.pos.y + r.size.y);
	}

	inline bool RectVsRect(const Collider& r1, const Collider& r2)
	{
		return (r1.pos.x < r2.pos.x + r2.size.x && r1.pos.x + r1.size.x > r2.pos.x && r1.pos.y < r2.pos.y + r2.size.y && r1.pos.y + r1.size.y > r2.pos.y);
	}

	inline bool RayVsRect(const Ray& ray, const Collider& target, HitResult& result)
	{
		glm::vec2 invDir = 1.0f / ray.direction;

		glm::vec2 tNear = (target.pos - ray.origin) * invDir;
		glm::vec2 tFar = (target.pos + target.size - ray.origin) * invDir;

		if (std::isnan(tFar.y) || std::isnan(tFar.x)) return false;
		if (std::isnan(tNear.y) || std::isnan(tNear.x)) return false;

		if (tNear.x > tFar.x) std::swap(tNear.x, tFar.x);
		if (tNear.y > tFar.y) std::swap(tNear.y, tFar.y);

		if (tNear.x > tFar.y || tNear.y > tFar.x) return false;

		result.hitDistance = std::max(tNear.x, tNear.y);
		float tHitFar = std::min(tFar.x, tFar.y);

		if (tHitFar < 0) return false;

		result.hit = true;
		result.hitPoint = ray.origin + result.hitDistance * ray.direction;

		if (tNear.x > tNear.y)
		{
			if (ray.direction.x < 0)
				result.hitNormal = { 1,0 };
			else
				result.hitNormal = { -1,0 };
		}
		else if (tNear.x < tNear.y)
		{
			if (ray.direction.y < 0)
				result.hitNormal = { 0,1 };
			else
				result.hitNormal = { 0,-1 };
		}
		return true;
	}


}

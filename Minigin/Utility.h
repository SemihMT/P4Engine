#pragma once
#include <random>
#include <limits>
#include "glm/glm.hpp"

namespace dae
{


	struct Collider
	{
		glm::vec2 pos;
		glm::vec2 size;
	};

	enum class ColliderType
	{
		Platform,
		Wall,
		Trigger
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


	inline float GetRandomFloat()
	{
		static std::default_random_engine engine(std::random_device{}());
		static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
		return dist(engine);
	}

#undef max
#undef min
	// Tutorial Javidx9: https://www.youtube.com/watch?v=8JJ-4JgR7Dg&t=2552s
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

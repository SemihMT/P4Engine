#pragma once
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <variant>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace dae
{
	enum class Event
	{
		Player_Spawn,
		Player_Idle,
		Player_Death,
		Player_Respawn,
		Player_Damaged,
		Player_ShootBubble,
		Player_Jump,
		Player_Fall,
		Player_Move,

		Bubble_Spawn,
		Bubble_Shot,
		Bubble_HitEnemy, //Bubble has touched an enemy
		Bubble_PopEnemy, //Bubble with enemy in has been popped
		Bubble_PopNoEnemy,
		Bubble_PlayerJump,

		Item_Collected,


		Maita_Damaged,
	};

	struct EventData
	{
		// std::variant is a type safe union, allowing us to store different datatypes
		// This way we can send multiple types of data along with the event
		using PossibleEventData = std::variant<int, float, std::string, glm::vec3, glm::vec2, GameObject*>;
		std::unordered_map<std::string, PossibleEventData> data;


		template <typename T>
		T Get(const std::string& key) const
		{
			//Check if the map contains the key we searched for
			if(data.contains(key))
			{
				//get the variant at the key we specified
				const auto& value = data.at(key);
				//Check if the variant of type T actually holds data, will be nullptr if there is a type mismatch
				if(const auto* dataPtr = std::get_if<T>(&value))
				{
					return *dataPtr;
				}
			}
			throw std::runtime_error("Data not found or type mismatch for key: " + key);
		}

	};
}

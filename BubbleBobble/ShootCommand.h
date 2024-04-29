#pragma once
#include "GameObjectCommand.h"
#include "ShootBubble.h"

namespace dae
{
	class ShootCommand final : public GameObjectCommand
	{
	public:
		ShootCommand(GameObject* gameObject): GameObjectCommand(gameObject)
		{
		}
		void Execute() override
		{
			GetGameObject()->GetComponent<ShootBubble>()->Shoot();
			ServiceLocator::getService<ISoundService>("Sound")->PlaySound("ShootBullet.wav");
		}

	};
}

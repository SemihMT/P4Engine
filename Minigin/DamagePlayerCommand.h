#pragma once
#include "GameObjectCommand.h"
#include "HealthComponent.h"

namespace dae
{
	class DamagePlayerCommand final : public GameObjectCommand
	{
	public:
		DamagePlayerCommand(GameObject* gameObject, GameObject* playerToDamage)
			: GameObjectCommand(gameObject),
			m_pPlayerToDamage(playerToDamage)
		{
		}

		void Execute() override
		{
			if(auto* healthComp = m_pPlayerToDamage->GetComponent<HealthComponent>())
			{
				healthComp->Damage(1);
			}
		}
	private:
		GameObject* m_pPlayerToDamage{};
	};
}

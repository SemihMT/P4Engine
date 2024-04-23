#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class HealthComponent : public BaseComponent, public Subject
	{

	public:
		HealthComponent(GameObject* owner, int maxHealth);
		~HealthComponent() override = default;

		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

		void SetCurrentHealth(int health);
		int GetCurrentHealth() const;

		void SetMaxHealth(int maxHealth);
		int GetMaxHealth() const;

		void Damage(int damage);
		void Heal(int healing);


	private:
		int m_maxHealth{};
		int m_currentHealth{};
	};


}

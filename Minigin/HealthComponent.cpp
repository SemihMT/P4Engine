#include "HealthComponent.h"

dae::HealthComponent::HealthComponent(GameObject* owner, int maxHealth) : BaseComponent(owner), m_maxHealth(maxHealth), m_currentHealth(maxHealth)
{
}

void dae::HealthComponent::SetCurrentHealth(int health)
{
	m_currentHealth = health;
}

void dae::HealthComponent::Damage(int damage)
{
	m_currentHealth -= damage;
	if (m_currentHealth < 0)
	{
		m_currentHealth = 0;
		Notify(Event::Player_Death,
			{
				.data = {{"Health", m_currentHealth}, {"Player", GetOwner()}}
			});
	}
	else
	{
		Notify(Event::Player_Damaged,
			{
				.data = {{"Health", m_currentHealth}, {"Player", GetOwner()}}
			});
	}

}

void dae::HealthComponent::Heal(int healing)
{
	m_currentHealth += healing;
	if (m_currentHealth > m_maxHealth)
		m_currentHealth = m_maxHealth;

}

int dae::HealthComponent::GetCurrentHealth() const
{
	return m_currentHealth;
}

void dae::HealthComponent::SetMaxHealth(int maxHealth)
{
	//set the new max health
	if (maxHealth > m_currentHealth)
		m_maxHealth = maxHealth;
	else
	{
		//if the new max health is less than what we currently have (a debuff?)
		//set the current health to the new max 
		m_currentHealth = maxHealth;
		m_maxHealth = m_currentHealth;
	}
}

int dae::HealthComponent::GetMaxHealth() const
{
	return m_maxHealth;
}

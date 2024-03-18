#pragma once
#include "Command.h"
#include "GameObject.h"

namespace dae
{
	class GameObjectCommand : public Command
	{
	public:
		GameObjectCommand(GameObject* gameObject) : m_pGameObject(gameObject) {}
		virtual ~GameObjectCommand() override {};
	protected:
		GameObject* GetGameObject() const { return m_pGameObject; }
	private:
		GameObject* m_pGameObject{};
	};

}

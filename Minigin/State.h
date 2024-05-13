#pragma once
#include "GameObject.h"

namespace dae
{
	
	class State
	{
	public:
		
		virtual ~State() = default;
		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;
		virtual void Update() = 0;
	protected:
		State(GameObject* owner) :m_owner{ owner }
		{}
		GameObject* GetOwner() const { return m_owner; }
	private:
		GameObject* m_owner;
	};

}

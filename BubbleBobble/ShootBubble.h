#pragma once
#include <BaseComponent.h>
#include <string>
#include <vector>

#include "BubbleComponent.h"

namespace dae
{
	class ShootBubble final:  public BaseComponent
	{
	public:
		ShootBubble(GameObject* owner, std::vector<GameObject*>& bubbles);
		virtual ~ShootBubble() override = default;

		ShootBubble(const ShootBubble& other) = delete;
		ShootBubble(ShootBubble&& other) = delete;
		ShootBubble& operator=(const ShootBubble& other) = delete;
		ShootBubble& operator=(ShootBubble&& other) = delete;

		//Called from the ShootCommand
		void Shoot() const;
	private:
		std::vector<GameObject*>& m_bubbles;

	};
}

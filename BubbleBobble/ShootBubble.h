#pragma once
#include <BaseComponent.h>

namespace dae
{
	class ShootBubble final:  public BaseComponent
	{
	public:
		ShootBubble(GameObject* owner, GameObject* bubble); //TODO: Replace bubble with an object pool of bubbles, so we can reuse them
		virtual ~ShootBubble() override = default;

		ShootBubble(const ShootBubble& other) = delete;
		ShootBubble(ShootBubble&& other) = delete;
		ShootBubble& operator=(const ShootBubble& other) = delete;
		ShootBubble& operator=(ShootBubble&& other) = delete;

		//Called from the ShootCommand
		void Shoot() const;

	private:
		GameObject* m_pBubble{ nullptr };

	};
}

#pragma once
#include <BaseComponent.h>

namespace dae
{
	class ShootBubble final:  public BaseComponent
	{
	public:
		ShootBubble(GameObject* owner);
		virtual ~ShootBubble() override = default;

		ShootBubble(const ShootBubble& other) = delete;
		ShootBubble(ShootBubble&& other) = delete;
		ShootBubble& operator=(const ShootBubble& other) = delete;
		ShootBubble& operator=(ShootBubble&& other) = delete;

		//Called from the ShootCommand
		void Shoot() const;
	private:
		std::unique_ptr<GameObject> m_bubble{};

	};
}

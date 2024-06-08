#include "ShootBubble.h"

#include "BubbleMovementComponent.h"
#include "BubbleShotState.h"
#include "BubbleSpawnState.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "StateComponent.h"

dae::ShootBubble::ShootBubble(GameObject* owner, std::vector<GameObject*>& bubbles) :
	BaseComponent(owner),
	m_bubbles{ bubbles }
{
}

void dae::ShootBubble::Shoot() const
{
	const auto iterator = std::ranges::find_if(m_bubbles, [](const GameObject* bubble) { return bubble->GetComponent<BubbleComponent>()->IsAvailable() == true; });
	if (iterator != m_bubbles.end())
	{
		(*iterator)->GetComponent<StateComponent>()->SetState(std::make_unique<BubbleShotState>((*iterator),GetOwner()->GetTransform()));

		/*(*iterator)->GetTransform()->SetLocalPosition(bubbleShootPos);
		(*iterator)->GetComponent<BubbleMovementComponent>()->SetMovementDirection(playerDir);*/
	}
}

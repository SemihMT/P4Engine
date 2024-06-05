#include "PlayerComponent.h"

#include "AnimationComponent.h"
#include "GameObject.h"

dae::PlayerComponent::PlayerComponent(GameObject* owner, int playerNumber) :
	BaseComponent(owner)
{
	std::string spriteSheet{};
	if (playerNumber == 1)
		spriteSheet = "Sprites/Characters/Player/BubSpriteSheet.png";
	if (playerNumber == 2)
		spriteSheet = "Sprites/Characters/Player/BobSpriteSheet.png";

	owner->AddComponent<AnimationComponent>(spriteSheet);

}

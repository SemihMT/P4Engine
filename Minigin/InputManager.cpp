#include <SDL.h>
#include "InputManager.h"


bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type)
		{
		case SDL_QUIT:
		{
			return false;
		}
		break;
		/*case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_a:
			{
				TimeManager::GetInstance().SetFrameTime(165);
			}
			break;
			case SDLK_z:
			{
				TimeManager::GetInstance().SetFrameTime(60);
			}
			}
			break;*/
		default:
			return true;
		}

	}

	return true;
}

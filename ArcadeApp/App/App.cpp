#include <iostream>
#include "App.h"
#include "SDL.h"
#include "ArcadeScene.h"
#include <memory>


App& App::Singleton()
{
	static App theApp;
	return theApp;
}
bool App::Init(uint32_t width, uint32_t height, uint32_t mag)
{
	mnoptrWindow = mScreen.Init(width, height, mag);
	return mnoptrWindow != nullptr;
}
void App::Run()
{
	if (mnoptrWindow)
	{
		SDL_Event sdlEvent;
		bool running = true;

		uint32_t lastTick = SDL_GetTicks();
		uint32_t currentTick = lastTick;

		uint32_t dt = 10;
		uint32_t accumulator = 0;

		std::unique_ptr<ArcadeScene> arcadeScene = std::make_unique<ArcadeScene>();
		arcadeScene->Init();

		while(running)
		{
			currentTick = SDL_GetTicks();
			uint32_t frameTime = currentTick - lastTick;

			if (frameTime > 300)
			{
				frameTime = 300;
			}
			lastTick = currentTick;

			accumulator += frameTime;

			//Input
			while(SDL_PollEvent(&sdlEvent))
			{
				switch (sdlEvent.type)
				{
				case SDL_QUIT:
					running = false;
					break;
				}
			}
			//Update
			while(accumulator >= dt)
			{ //Update current scene by delta time
				arcadeScene->Update(dt);
				std::cout << "Delta time step: " << dt << std::endl;
				accumulator -= dt;
			}
			//Render
			arcadeScene->Draw(mScreen);
			mScreen.SwapScreen();
			
		}
	}
}


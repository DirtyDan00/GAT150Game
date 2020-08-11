#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "../Graphics/Texture.h"
#include "../Graphics/Renderer.h"
#include "Resources/ResourceManager.h"
#include "Input/InputSystem.h"
#include "Core/Timer.h"
#include "pch.h"

nc::ResourceManager resourceManager;
nc::Renderer renderer;
nc::InputSystem inputSystem;
nc::FrameTimer timer;


int main(int, char**)
{
    //nc::Timer timer;
    //for (size_t i = 0; i < 100; i++) { std::sqrt(rand() % 100); }
    //std::cout << timer.ElapsedSeconds() << std::endl;

    renderer.Startup();
    renderer.Create("GAT150", 800, 600);
    inputSystem.Startup();

    //create textures
    int width = 128;
    int height = 128;
    //nc::Texture* texture1 = resourceManager.Get<nc::Texture>("cellsmart.png", &renderer);
    nc::Texture* background = resourceManager.Get<nc::Texture>("background.png", &renderer);
    nc::Texture* car = resourceManager.Get<nc::Texture>("cars.png", &renderer);


    float angle{ 0 };
    nc::Vector2 position = nc::Vector2{ 400,300 };


    SDL_Event event;
    bool forQuit = false;
    while (!forQuit)
    {
        
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            forQuit = true;
        default:
            break;
        }
        timer.Tick();
        inputSystem.Update();
        if (inputSystem.GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::PRESSED)
        {
           forQuit = true;
        }

        if (inputSystem.GetButtonState(SDL_SCANCODE_LEFT) == nc::InputSystem::eButtonState::HELD)
        {
            position.x = position.x - 200.0f * timer.DeltaTime();
        }
        if (inputSystem.GetButtonState(SDL_SCANCODE_RIGHT) == nc::InputSystem::eButtonState::HELD)
        {
            position.x = position.x + 200.0f * timer.DeltaTime();
        }

        renderer.BeginFrame();

        angle = angle + 180 * timer.DeltaTime();
        background->Draw({0,0}, { 1.0f,1.0f }, 0);
       //texture1->Draw(position, { 3.0f,3.0f }, angle);
        car->Draw({0, 16, 64, 144}, position, { 1.0f,1.0f }, 0);

        renderer.EndFrame();
    }
    inputSystem.Shutdown();
    renderer.Shutdown();
    SDL_Quit();
    
    return 0;

}
#include "pch.h"
#include "../Graphics/Texture.h"
#include "../Math/Math.h"
#include "Engine.h"
#include "Object/GameObject.h"
#include "Componet/PhysicsComponet.h"
#include "Componet/SpriteComponet.h"

nc::Engine engine;
nc::GameObject player;


int main(int, char**)
{
    //nc::Timer timer;
    //for (size_t i = 0; i < 100; i++) { std::sqrt(rand() % 100); }
    //std::cout << timer.ElapsedSeconds() << std::endl;
    engine.Startup();

    player.Create(&engine);
    player.m_transform.position = { 400,300 };
    player.m_transform.angle = 45;
    nc::Componet* componet = new nc::PhysicsComponet;
    player.AddComponet(componet);
    componet->Create();
    componet = new nc::SpriteComponet;
    player.AddComponet(componet);
    componet->Create();

    //create textures
    int width = 128;
    int height = 128;
    //nc::Texture* texture1 = resourceManager.Get<nc::Texture>("cellsmart.png", &renderer);
    nc::Texture* background = engine.GetSystem<nc::ResourceManager>()->Get<nc::Texture>("background.png", engine.GetSystem<nc::Renderer>());



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
        engine.Update();
        player.Update();
        if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::PRESSED)
        {
           forQuit = true;
        }

        //if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_LEFT) == nc::InputSystem::eButtonState::HELD)
        //{
        //    position.x = position.x - 200.0f * engine.GetTimer().DeltaTime();
        //}
        //if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_RIGHT) == nc::InputSystem::eButtonState::HELD)
        //{
        //    position.x = position.x + 200.0f * engine.GetTimer().DeltaTime();
        //}
        if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD)
        {
            player.m_transform.angle = player.m_transform.angle - 200.f * engine.GetTimer().DeltaTime();
        }
        if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD)
        {
            player.m_transform.angle = player.m_transform.angle + 200.f * engine.GetTimer().DeltaTime();
        }

        nc::Vector2 force{ 0,0 };
        if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_W) == nc::InputSystem::eButtonState::HELD)
        {
            force = nc::Vector2::forward * 1000.0f;
        }
        if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_S) == nc::InputSystem::eButtonState::HELD)
        {
            force = nc::Vector2::forward * -1000.0f;
        }
        nc::Vector2::Rotate(force, nc::DegreesToRadian(player.m_transform.angle));

        engine.GetSystem<nc::Renderer>()->BeginFrame();

        //angle = angle + 180 * timer.DeltaTime();
        background->Draw({0,0}, { 1.0f,1.0f }, 0);
       //texture1->Draw(position, { 3.0f,3.0f }, angle);
        //render sprite
        player.Draw();

        engine.GetSystem<nc::Renderer>()->EndFrame();
    }
    SDL_Quit();
    
    return 0;

}
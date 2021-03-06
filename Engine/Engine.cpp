#include "pch.h"
#include "Engine.h"
#include "Physics/PhysicsSystem.h"
#include <time.h>

namespace nc
{
    
    bool nc::Engine::Startup()
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            std::cout << "SDL_Init Error." << SDL_GetError() << std::endl;
            return false;
        }
        m_systems.push_back(new Renderer);
        m_systems.push_back(new InputSystem);
        m_systems.push_back(new ResourceManager);
        m_systems.push_back(new AudioSystem);
        m_systems.push_back(new PhysicsSystem);

        for (auto system : m_systems)
        {
            system->Startup();
        }

        GetSystem<Renderer>()->Create("GAT150", 800, 600);

        return true;
    }
    
    void nc::Engine::Shutdown()
    {
        for (auto system : m_systems)
        {
            system->Shutdown();
            delete system;
        }
        m_systems.clear();
        SDL_Quit();
    }
    
    void nc::Engine::Update()
    {
        m_timer.Tick();
        for (auto system : m_systems)
        {
            system->Update();
        }
    }
    //void Engine::RestartGame()
    //{
    //    for (auto system : m_systems)
    //    {
    //        system->Shutdown();
    //        delete system;
    //    }
    //    m_systems.clear();
    //    SDL_Quit();
    //
    //}
}

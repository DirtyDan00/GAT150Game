#include "pch.h"
#include "../Graphics/Texture.h"
#include "Engine.h"
#include "Object/GameObject.h"
#include "Componet/PlayerComponet.h"
#include "Core/Factory.h"
#include "Core/Json.h"
#include "Core/EventManager.h"
#include "Object/ObjectFactory.h"
#include "Object/Scene.h"
#include "Physics/PhysicsSystem.h"
#include "Componet/EnemyComponent.h"
#include "TileMap.h"

nc::Engine engine;
nc::Scene scene;

void GameEvent(const nc::Event& event)
{
    std::cout << "You have died!" << std::endl;
    
}
void GameEvent2(const nc::Event& event)
{
        std::cout << "You've Collected a Coin!" << std::endl;
}


int main(int, char**)
{

    //nc::json::Load("json.txt", document);
    //
    //
    //std::string str;
    //nc::json::Get(document, "string", str);
    //std::cout << str << std::endl;
    //
    //bool b;
    //nc::json::Get(document, "bool", b);
    //std::cout << b << std::endl;
    //
    //int i1;
    //nc::json::Get(document, "integer1", i1);
    //std::cout << i1 << std::endl;
    //
    //int i2;
    //nc::json::Get(document, "integer2", i2);
    //std::cout << i2 << std::endl;
    //
    //float f;
    //nc::json::Get(document, "float", f);
    //std::cout << f << std::endl;
    //
    //nc::Vector2 v2;
    //nc::json::Get(document, "vector2", v2);
    //std::cout << v2 << std::endl;
    //
    //nc::Color color;
    //nc::json::Get(document, "color", color);
    //std::cout << color << std::endl;


    engine.Startup();
    nc::ObjectFactory::Instance().Initialize();
    nc::ObjectFactory::Instance().Register("PlayerComponent", new nc::Creator<nc::PlayerComponet, nc::Object>);
    nc::ObjectFactory::Instance().Register("EnemyComponent", new nc::Creator<nc::EnemyComponet, nc::Object>);

    nc::EventManager::Instance().Subscribe("PlayerDead", &GameEvent);
    nc::EventManager::Instance().Subscribe("CollectedCoin", &GameEvent2);

    rapidjson::Document document;
    scene.Create(&engine);
    nc::json::Load("scene.txt", document);

    scene.Read(document);
    nc::TileMap tileMap;
    nc::json::Load("tileMap.txt", document);
    tileMap.Read(document);
    tileMap.Create(&scene);


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
        scene.Update();
        if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::PRESSED)
        {
           forQuit = true;
        }

        engine.GetSystem<nc::Renderer>()->BeginFrame();

        scene.Draw();

        engine.GetSystem<nc::Renderer>()->EndFrame();
    }
    SDL_Quit();
    scene.Destroy();
    return 0;

}
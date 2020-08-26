#include "pch.h"
#include "../Graphics/Texture.h"
#include "Engine.h"
#include "Object/GameObject.h"
#include "Componet/PlayerComponet.h"
#include "Core/Factory.h"
#include "Core/Json.h"
#include "Object/ObjectFactory.h"
#include "Object/Scene.h"
#include "Physics/PhysicsSystem.h"

nc::Engine engine;
nc::GameObject player;
nc::Scene scene;
//nc::ObjectFactory objectFactory;


int main(int, char**)
{
    rapidjson::Document document;

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

    scene.Create(&engine);
    nc::json::Load("scene.txt", document);
    scene.Read(document);

 /*   for (size_t i = 0; i < 10; i++)
    {
        nc::GameObject* gameObject = nc::ObjectFactory::Instance().Create<nc::GameObject>("ProtoExplosion");
        gameObject->m_transform.position = nc::Vector2{ nc::random(0,800), nc::random(0,600) };
        gameObject->m_transform.angle = nc::random(0, 360);
        scene.AddGameObject(gameObject);
    }*/


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
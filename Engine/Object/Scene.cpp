#include "pch.h"
#include "Scene.h"
#include "Object/GameObject.h"
#include "Object/ObjectFactory.h"

bool nc::Scene::Create(void* data)
{
    m_engine = static_cast<Engine*>(data);
    return false;
}

void nc::Scene::Destroy()
{
    RemoveAllGameObject();
}

void nc::Scene::Read(const rapidjson::Value& value)
{
    if (value.HasMember("Prototypes"))
    {
        const rapidjson::Value& objectValue = value["Prototypes"];
        if (objectValue.IsArray())
        {
            ReadPrototypes(objectValue);
        }
    }
    if (value.HasMember("GameObjects"))
    {
        const rapidjson::Value& objectValue = value["GameObjects"];
        if (objectValue.IsArray())
        {
            ReadAllGameObjects(objectValue);
        }
    }

   
}

void nc::Scene::Update()
{
    for (auto gameObject : m_gameObjects)
    {
        gameObject->Update();
    }
    auto iter = m_gameObjects.begin();
    while (iter != m_gameObjects.end())
    {
        if ((*iter)->m_flags[GameObject::eFlags::DESTROY])
        {
            (*iter)->Destroy();
            delete (*iter);
            iter = m_gameObjects.erase(iter);
        }
        else
        {
            iter++;
        }
        
    }
}

void nc::Scene::Draw()
{
    for (auto gameObject : m_gameObjects)
    {
        gameObject->Draw();
    }
}

nc::GameObject* nc::Scene::Find(const std::string& name)
{
    for (auto gameObject : m_gameObjects)
    {
        if(gameObject->m_name == name)
        {
            return gameObject;
        }
    }
    return nullptr;
    
}

void nc::Scene::AddGameObject(GameObject* gameObject)
{
    m_gameObjects.push_back(gameObject);
}

void nc::Scene::RemoveGameObject(GameObject* gameObject)
{
    auto iter = std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject);
    if (iter != m_gameObjects.end())
    {
        (*iter)->Destroy();
        delete(*iter);
    }
}

void nc::Scene::RemoveAllGameObject()
{
    for (GameObject* gameObject : m_gameObjects)
    {
        gameObject->Destroy();
        delete gameObject;
    }
    m_gameObjects.clear();
}

void nc::Scene::ReadAllGameObjects(const rapidjson::Value& value)
{
    for (rapidjson::SizeType i = 0; i < value.Size(); i++)
    {
        const rapidjson::Value& objectValue = value[i];
    if (objectValue.IsObject())
    {
        std::string typeName;
        nc::json::Get(objectValue, "type", typeName);
        nc::GameObject* gameObject = nc::ObjectFactory::Instance().Create<nc::GameObject>(typeName);

        if (gameObject)
        {
            gameObject->Create(this);
            gameObject->Read(objectValue);
            AddGameObject(gameObject);
        }

    }
    }
}

void nc::Scene::ReadPrototypes(const rapidjson::Value& value)
{
    for (rapidjson::SizeType i = 0; i < value.Size(); i++)
    {
        const rapidjson::Value& objectValue = value[i];
        if (objectValue.IsObject())
        {
            std::string typeName;
            nc::json::Get(objectValue, "type", typeName);
            nc::GameObject* gameObject = nc::ObjectFactory::Instance().Create<nc::GameObject>(typeName);

            if (gameObject)
            {
                gameObject->Create(this);
                gameObject->Read(objectValue);
                ObjectFactory::Instance().Register(gameObject->m_name, new Prototype<Object>(gameObject));
            }

        }
    }
}

std::vector<nc::GameObject*> nc::Scene::FindGameObjectsWithTag(const std::string& tag)
{
    std::vector<GameObject*> gameObjects;
    for (auto gameObject : m_gameObjects)
    {
        if (gameObject->m_tag == tag)
        {
            gameObjects.push_back(gameObject);
        }
    }
    return gameObjects;
}

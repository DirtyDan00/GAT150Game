#include "pch.h"
#include "GameObject.h"
#include "Componet/Componet.h"
#include "Componet/RenderComponet.h"
#include "ObjectFactory.h"
#include "Scene.h"

namespace nc
{
    GameObject::GameObject(const GameObject& other)
    {
        m_name = other.m_name;
        m_tag = other.m_tag;
        m_lifeTime = other.m_lifeTime;
        m_flags = other.m_flags;
        m_transform = other.m_transform;
        m_engine = other.m_engine;
        m_scene = other.m_scene;

        for (Componet* componet : other.m_componets)
        {
            Componet* clone = dynamic_cast<Componet*>(componet->Clone());
            clone->m_owner = this;
            AddComponet(clone);
        }
    }
    bool nc::GameObject::Create(void* data)
    {

        m_scene = static_cast<Scene*>(data);
        m_engine = m_scene->m_engine;
        return true;
    }
    
    void nc::GameObject::Destroy()
    {
        RemoveAllComponet();
    }
    void GameObject::Read(const rapidjson::Value& value)
    {
        nc::json::Get(value, "name", m_name);
        nc::json::Get(value, "tag", m_tag);
        nc::json::Get(value, "lifetime", m_lifeTime);

        bool transient = m_flags[eFlags::TRANSIENT];
        nc::json::Get(value, "transient", transient);
        m_flags[eFlags::TRANSIENT] = transient;

        nc::json::Get(value, "position", m_transform.position);
        nc::json::Get(value, "scale", m_transform.scale);
        nc::json::Get(value, "angle", m_transform.angle);

        if (value.HasMember("Components")) 
        {
            const rapidjson::Value& componetsValue = value["Components"];
            if (componetsValue.IsArray())
            {
                ReadComponents(componetsValue);
            }
        }
    }
    void GameObject::AddComponet(Componet* componet)
    {
        componet->m_owner = this;
        m_componets.push_back(componet);
    }
    void GameObject::RemoveComponet(Componet* componet)
    {
        auto iter = std::find(m_componets.begin(), m_componets.end(), componet);
        if (iter != m_componets.end())
        {
            (*iter)->Destroy();
            delete(*iter);
        }
    }
    void GameObject::RemoveAllComponet()
    {
        for (auto componet : m_componets)
        {
            componet->Destroy();
            delete componet;
        }
        m_componets.clear();
    }
    void GameObject::Update()
    {
        for (auto componet : m_componets)
        {
            componet->Update();
        }
        if (m_flags[eFlags::TRANSIENT])
        {
            m_lifeTime = m_lifeTime - m_engine->GetTimer().DeltaTime();
            m_flags[eFlags::DESTROY] = m_lifeTime <= 0;
        }

    }
    void GameObject::Draw()
    {
        RenderComponet* componet = GetComponet<RenderComponet>();
        if (componet)
        {
            componet->Draw();
        }
    }
    void GameObject::BeginContact(GameObject* gameObject)
    {
        m_contacts.push_back(gameObject);
        Event event;
        event.type = "CollisionEnter";
        event.sender = gameObject;
        event.receiver = this;

        EventManager::Instance().Notify(event);
    }
    void GameObject::EndContact(GameObject* gameObject)
    {
        m_contacts.remove(gameObject);

        Event event;
        event.type = "CollisionExit";
        event.sender = gameObject;
        event.receiver = this;

        EventManager::Instance().Notify(event);

    }
    std::vector<GameObject*> GameObject::GetContactsWithTag(const std::string& tag)
    {
        std::vector<GameObject*> contacts;
        for (auto contact : m_contacts)
        {
            if (contact->m_tag == tag)
            {
                contacts.push_back(contact);
            }
        }

        return contacts;
    }
    void GameObject::ReadComponents(const rapidjson::Value& value)
    {
        for (rapidjson::SizeType i = 0; i < value.Size(); i++)
        {
            const rapidjson::Value& componentValue = value[i];
            if (componentValue.IsObject())
            {
                std::string typeName;
                nc::json::Get(componentValue, "type", typeName);

                Componet* comp = nc::ObjectFactory::Instance().Create<nc::Componet>(typeName);

                if (comp)
                {
                    comp->Create(this);
                    comp->Read(componentValue);
                    AddComponet(comp);

                }
            }
        }
    }
}

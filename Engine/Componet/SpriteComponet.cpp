#include "pch.h"
#include "SpriteComponet.h"
#include "../Graphics/Texture.h"


namespace nc
{
    
    bool nc::SpriteComponet::Create(void* data)
    {

        m_owner = static_cast<GameObject*>(data);
        return true;
    }
    
    void nc::SpriteComponet::Destroy()
    {
    }

    void SpriteComponet::Read(const rapidjson::Value& value)
    {
        nc::json::Get(value, "texture", m_textureName);
        nc::json::Get(value, "origin", m_origin);
        nc::json::Get(value, "rect", m_rect);
    }
    
    void nc::SpriteComponet::Update()
    {
    }
    
    void nc::SpriteComponet::Draw()
    {
        Texture* texture = m_owner->m_engine->GetSystem<nc::ResourceManager>()->Get<nc::Texture>(m_textureName, m_owner->m_engine->GetSystem<nc::Renderer>());
        texture->Draw(m_rect, m_owner->m_transform.position, m_owner->m_transform.angle, nc::Vector2{ 1.0f,1.0f } * m_owner->m_transform.scale, m_origin, m_flip);
    }
}

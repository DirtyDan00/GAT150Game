#include "pch.h"
#include "SpriteComponet.h"
#include "../Graphics/Texture.h"


namespace nc
{
    
    bool nc::SpriteComponet::Create(void* data)
    {
        m_texture = m_owner->m_engine->GetSystem<nc::ResourceManager>()->Get<nc::Texture>("cars.png", m_owner->m_engine->GetSystem<nc::Renderer>());

        return true;
    }
    
    void nc::SpriteComponet::Destroy()
    {
    }
    
    void nc::SpriteComponet::Update()
    {
    }
    
    void nc::SpriteComponet::Draw()
    {
        m_texture->Draw({ 128, 120, 48, 98 }, m_owner->m_transform.position, { 1.0f,1.0f }, m_owner->m_transform.angle);
    }
}

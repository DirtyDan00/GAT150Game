#include "pch.h"
#include "PhysicsComponet.h"
#include "Object/GameObject.h"

bool nc::PhysicsComponet::Create(void* data)
{
    m_velocity = nc::Vector2::forward * 100;
    return true;
}

void nc::PhysicsComponet::Destroy()
{
}

void nc::PhysicsComponet::Update()
{
    m_velocity = m_velocity + m_force * m_owner->m_engine->GetTimer().DeltaTime();
    m_velocity = m_velocity * m_drag;
    m_owner->m_transform.position = m_owner->m_transform.position + m_velocity * m_owner->m_engine->GetTimer().DeltaTime();
}

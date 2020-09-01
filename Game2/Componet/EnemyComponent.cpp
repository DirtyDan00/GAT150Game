#include "pch.h"
#include "Componet/PhysicsComponet.h"
#include "EnemyComponent.h"
#include "Object/GameObject.h"
#include "Object/Scene.h"

bool nc::EnemyComponet::Create(void* data)
{
    m_owner = static_cast<GameObject*>(data);
    return true;
}

void nc::EnemyComponet::Destroy()
{

}

void nc::EnemyComponet::Update()
{
    GameObject* player = m_owner->m_scene->Find("Player");
    if (player)
    {
        Vector2 direction = player->m_transform.position - m_owner->m_transform.position;
        Vector2 force = direction.Normalized() * 5.0f;

        PhysicsComponet* physicsComponent = m_owner->GetComponet<PhysicsComponet>();
        physicsComponent->ApplyForce(force);
    }
}

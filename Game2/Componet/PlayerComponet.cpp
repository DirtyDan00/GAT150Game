#include "pch.h"
#include "PlayerComponet.h"
#include "Input/InputSystem.h"
#include "Componet/PhysicsComponet.h"
#include "Componet/RigidBodyComponent.h"
#include "Componet/AudioComponent.h"
#include "Engine.h"

namespace nc
{
	bool nc::PlayerComponet::Create(void* data)
	{
		return true;
	}

	void nc::PlayerComponet::Destroy()
	{
	}

	void nc::PlayerComponet::Update()
	{
        auto contacts = m_owner->GetContactsWithTag("Floor");
        bool onGround = !contacts.empty();

        nc::Vector2 force{ 0,0 };
        if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD)
        {
            force.x = -100;
            //m_owner->m_transform.angle = m_owner->m_transform.angle - 200.f * m_owner->m_engine->GetTimer().DeltaTime();
        }
        if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD)
        {
            force.x = 100;
            //m_owner->m_transform.angle = m_owner->m_transform.angle + 200.f * m_owner->m_engine->GetTimer().DeltaTime();
        }
        if (onGround && m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_SPACE) == nc::InputSystem::eButtonState::PRESSED)
        {
              force.y = -1500;
              AudioComponent* audioComponent = m_owner->GetComponet<AudioComponent>();
              if (audioComponent)
              {
                  audioComponent->Play();
              }
        }


 
        //if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_W) == nc::InputSystem::eButtonState::HELD)
        //{
        //    force = nc::Vector2::forward * 1000.0f;
        //}
        //if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_S) == nc::InputSystem::eButtonState::HELD)
        //{
        //    force = nc::Vector2::forward * -1000.0f;
        //}
        //force = nc::Vector2::Rotate(force, nc::DegreesToRadian(m_owner->m_transform.angle));

        PhysicsComponet* component = m_owner->GetComponet<RigidBodyComponent>();
        if (component)
        {
            component->ApplyForce(force);
        }

        auto coinContacts = m_owner->GetContactsWithTag("Coin");
        for (GameObject* contact : coinContacts)
        {
            contact->m_flags[GameObject::eFlags::DESTROY] = true;
        }
	}
}


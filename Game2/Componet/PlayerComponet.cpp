#include "pch.h"
#include "PlayerComponet.h"
#include "Input/InputSystem.h"
#include "Componet/PhysicsComponet.h"
#include "Componet/RigidBodyComponent.h"
#include "Componet/AudioComponent.h"
#include "Componet/SpriteComponet.h"
#include "Core/EventManager.h"
#include "Core/Timer.h"
#include "Engine.h"

namespace nc
{
	bool nc::PlayerComponet::Create(void* data)
	{
        m_owner = static_cast<GameObject*>(data);
        EventManager::Instance().Subscribe("CollisionEnter", std::bind(&PlayerComponet::OnCollisionEnter, this, std::placeholders::_1), m_owner);
        EventManager::Instance().Subscribe("CollisionExit", std::bind(&PlayerComponet::OnCollisionExit, this, std::placeholders::_1), m_owner);
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
            force.x = -200;
            //m_owner->m_transform.angle = m_owner->m_transform.angle - 200.f * m_owner->m_engine->GetTimer().DeltaTime();
        }
        if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD)
        {
            force.x = 200;
            //m_owner->m_transform.angle = m_owner->m_transform.angle + 200.f * m_owner->m_engine->GetTimer().DeltaTime();
        }
        if (onGround && m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_SPACE) == nc::InputSystem::eButtonState::PRESSED)
        {
              force.y = -1900;
              AudioComponent* audioComponent = m_owner->GetComponet<AudioComponent>();
              if (audioComponent)
              {
                  audioComponent->SetSoundName("audio/jump.wav");
                  audioComponent->Play();
              }
        }
        if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_B) == nc::InputSystem::eButtonState::PRESSED)
        {
            force.x = -200;
            //m_owner->m_transform.angle = m_owner->m_transform.angle - 200.f * m_owner->m_engine->GetTimer().DeltaTime();
        }

        PhysicsComponet* component = m_owner->GetComponet<PhysicsComponet>();
        if (component)
        {
            component->ApplyForce(force);

            Vector2 velocity = component->GetVelocity();

            SpriteComponet* spriteComponenet = m_owner->GetComponet<SpriteComponet>();
            if (velocity.x <= -0.5f) spriteComponenet->Flip();
            if (velocity.x >= 0.5f) spriteComponenet->Flip(false);
        }
	}
    void PlayerComponet::OnCollisionEnter(const Event& event)
    {
        
        GameObject* gameObject = dynamic_cast<GameObject*>(event.sender);
        if (gameObject->m_tag == "Enemy")
        {
            AudioComponent* audioComponent = m_owner->GetComponet<AudioComponent>();
            audioComponent->SetSoundName("audio/grunt.wav");
            audioComponent->Play();
            
            m_owner->m_flags[GameObject::eFlags::DESTROY] = true;
            //send dead player event
            Event event;
            event.type = "PlayerDead";
            EventManager::Instance().Notify(event);

        }
        if (gameObject->m_tag == "Coin")
        {
            AudioComponent* audioComponent = m_owner->GetComponet<AudioComponent>();
            audioComponent->SetSoundName("audio/coin.wav");
            audioComponent->Play();
            gameObject->m_flags[GameObject::eFlags::DESTROY] = true;
            Event event;
            event.type = "CollectedCoin";
            EventManager::Instance().Notify(event);
        }

        if (gameObject->m_tag == "Lava")
        {
            
            AudioComponent* audioComponent = m_owner->GetComponet<AudioComponent>();
            audioComponent->SetSoundName("audio/mario-fire.wav");
            audioComponent->Play();
            //send dead player event
            m_owner->m_flags[GameObject::eFlags::DESTROY] = true;
            Event event;
            event.type = "PlayerDead";
            EventManager::Instance().Notify(event);

        }


       // std::cout << "On collision enter: " << gameObject->m_name << std::endl;
    }
    void PlayerComponet::OnCollisionExit(const Event& event)
    {
        GameObject* gameObject = dynamic_cast<GameObject*>(event.sender);
      // std::cout << "On collision exit: " << gameObject->m_name << std::endl;
    }
}


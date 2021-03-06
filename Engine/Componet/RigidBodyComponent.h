#pragma once
#include "PhysicsComponet.h"
#include "Physics/PhysicsSystem.h"
#include "box2d/box2d.h"

namespace nc
{
	class RigidBodyComponent : public PhysicsComponet 
	{


		// Inherited via Componet
		virtual bool Create(void* data = nullptr) override;

		virtual void Destroy() override;

		virtual Object* Clone() const override { return new RigidBodyComponent{ *this }; }

		void Read(const rapidjson::Value& value) override;

		virtual void Update() override;

		void ApplyForce(const Vector2& force);

	protected:
		PhysicsSystem::RigidBodyData m_data;
		b2Body* m_body{ nullptr };
	};
}

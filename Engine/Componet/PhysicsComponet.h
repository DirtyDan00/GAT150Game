#pragma once
#include "Componet.h"
#include "../Math/Vector2.h"

namespace nc
{
	class PhysicsComponet : public Componet
	{
	public:


		// Inherited via Componet
		virtual bool Create(void* data = nullptr) override;

		virtual void Destroy() override;

		virtual Object* Clone() const override { return new PhysicsComponet{ *this }; }

		virtual void Update() override;

		virtual void ApplyForce(const Vector2& force) { m_force = force; }

		virtual Vector2& GetVelocity() { return m_velocity; }
	protected:
		nc::Vector2 m_velocity;
		nc::Vector2 m_force;
		float m_drag{ 1 };
	};
}

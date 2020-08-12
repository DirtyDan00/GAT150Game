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

		virtual void Update() override;
	private:
		nc::Vector2 m_velocity;
		nc::Vector2 m_force;
		float m_drag{ 1 };
	};
}

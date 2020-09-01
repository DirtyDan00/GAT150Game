#pragma once
#include "Componet/Componet.h"

namespace nc
{
	class EnemyComponet : public Componet
	{
	public:


		// Inherited via Componet
		virtual bool Create(void* data = nullptr) override;

		virtual void Destroy() override;

		virtual Object* Clone() const override { return new EnemyComponet{ *this }; }

		virtual void Update() override;

	};
}
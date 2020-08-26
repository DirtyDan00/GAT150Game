#pragma once
#include "Componet/Componet.h"

namespace nc
{
	class PlayerComponet : public Componet 
	{
	public:


		// Inherited via Componet
		virtual bool Create(void* data = nullptr) override;

		virtual void Destroy() override;

		virtual Object* Clone() override { return new PlayerComponet{ *this }; }

		virtual void Update() override;

	};
}
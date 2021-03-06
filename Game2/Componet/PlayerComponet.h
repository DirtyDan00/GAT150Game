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

		virtual Object* Clone() const override { return new PlayerComponet{ *this }; }

		virtual void Update() override;

		void OnCollisionEnter(const Event& event);
		void OnCollisionExit(const Event& event);

	};
}
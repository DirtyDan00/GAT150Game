#pragma once
#include "Object/GameObject.h"


namespace nc
{
	class GameObject;
	class Componet : public Object
	{
	public:
		virtual void Update() = 0;

		friend class GameObject;

	protected:
		GameObject* m_owner{ nullptr };
	};
}

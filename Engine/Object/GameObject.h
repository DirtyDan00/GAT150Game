#pragma once
#include "Object/Object.h"
#include "../Math/Transform.h"
#include "Engine.h"
#include <vector>

namespace nc
{
	class Componet;

	class GameObject : public Object
	{
	public:

		bool Create(void* data = nullptr);
		void Destroy();

		void AddComponet(Componet* componet);
		void RemoveComponet(Componet* componet);
		void RemoveAlComponet();

		void Update();
		void Draw();

		template<typename T>
		T* GetComponet()
		{
			T* result{ nullptr };
			for (auto componet : m_componets)
			{
				result = dynamic_cast<T*>(componet);
				if (result) break;
			}
			return result;
		}


		friend class Componet;
		friend class PhysicsComponet;

	public:
		Transform m_transform;
		Engine* m_engine;

	protected:
		std::vector<Componet*> m_componets;
	};
}
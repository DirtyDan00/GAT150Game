#pragma once
#include "Object/Object.h"
#include "../Math/Transform.h"
#include "Engine.h"
#include <bitset>

namespace nc
{
	class Componet;

	class GameObject : public Object
	{

	public:
		enum eFlags
		{
			ACTIVE,
			VISABLE,
			DESTROY,
			TRANSIENT
		};


	public:
		GameObject() = default;
		GameObject(const GameObject& other);

		virtual bool Create(void* data = nullptr);
		virtual void Destroy() override;
		virtual Object* Clone() override { return new GameObject{*this}; }

		void Read(const rapidjson::Value& value) override;

		void AddComponet(Componet* componet);
		void RemoveComponet(Componet* componet);
		void RemoveAlComponet();

		void Update();
		void Draw();

		void ReadComponents(const rapidjson::Value& value);

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
		std::string m_name;
		std::string m_tag;
		float m_lifeTime{ 0 };

		std::bitset<32> m_flags;

		Transform m_transform;
		Engine* m_engine{nullptr};

	protected:
		std::vector<Componet*> m_componets;
	};
}
#pragma once
#include "Object/Object.h"

namespace nc
{
	class Engine;
	class GameObject;

	class Scene : public Object
	{
	public:
		

		// Inherited via Object
		virtual bool Create(void* data = nullptr) override;

		virtual void Destroy() override;
		void Read(const rapidjson::Value& value) override;
		void ReadAllGameObjects(const rapidjson::Value& value);
		void ReadPrototypes(const rapidjson::Value& value);
		std::vector<GameObject*> FindGameObjectsWithTag(const std::string& tag);
		void Update();
		void Draw();
		GameObject* Find(const std::string& name);

		void AddGameObject(GameObject* gameObject);
		void RemoveGameObject(GameObject* gameObject);
		void RemoveAllGameObject();
	public:
		Engine* m_engine{ nullptr };

	protected:
		std::list<GameObject*> m_gameObjects;


	};
}

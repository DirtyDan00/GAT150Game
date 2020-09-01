#include "pch.h"
#include "TileMap.h"
#include "Object/Scene.h"
#include "Object/GameObject.h"
#include "Object/ObjectFactory.h"

void nc::TileMap::Read(const rapidjson::Value& value)
{
	json::Get(value, "numX", m_numX);
	json::Get(value, "numY", m_numY);
	json::Get(value, "size", m_size);
	json::Get(value, "start", m_start);
	json::Get(value, "tileNames", m_tileNames);
	json::Get(value, "tiles", m_tiles);
}

void nc::TileMap::Create(Scene* scene)
{
	for (size_t i = 0; i < m_tiles.size(); i++)
	{
		int index = m_tiles[i];
		if (index != 0)
		{
			GameObject* gameObject = ObjectFactory::Instance().Create<GameObject>(m_tileNames[index]);

			float x = i % m_numX;
			float y = i / m_numX;
			gameObject->m_transform.position = m_start + nc::Vector2{x,y} * m_size;
			scene->AddGameObject(gameObject);
		}
	}
}

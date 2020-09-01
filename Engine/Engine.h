#pragma once
#include <vector>
#include "../Graphics/Renderer.h"
#include "Resources/ResourceManager.h"
#include "Input/InputSystem.h"
#include "Core/Timer.h"
#include "Audio/AudioSystem.h"

namespace nc
{
	class System;

	class Engine
	{

	public:
		bool Startup();
		void Shutdown();

		void Update();

		//void RestartGame();

		template<typename T>
		inline T* GetSystem();

		nc::FrameTimer& GetTimer() { return m_timer; }
		

	protected:
		std::vector<System*> m_systems;
		nc::FrameTimer m_timer;

	};

	template<typename T>
	inline T* Engine::GetSystem()
	{
		T* result{ nullptr };
		for (auto system : m_systems)
		{
			result = dynamic_cast<T*>(system);
			if (result) break;
		}
		return result;
	}
}
	
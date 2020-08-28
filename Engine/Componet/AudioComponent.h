#pragma once
#include "Componet/Componet.h"
#include "Audio/AudioChannel.h"

namespace nc
{
	class AudioComponent : public Componet
	{
	public:
		// Inherited via Componet
		virtual bool Create(void* data = nullptr) override;
		virtual void Destroy() override;

		virtual Object* Clone() const { return new AudioComponent{*this}; }//override ask maple why it wont let me

		virtual void Update() override;

		void Read(const rapidjson::Value& value) override;

		void Play();


		void Stop();
		void SetSoundName(const std::string& soundName) { m_soundName = soundName; }

	protected:
		std::string m_soundName;
		bool m_loop{ false };
		bool m_playOnAwake{ false };

		AudioChannel m_channel;
	};
}

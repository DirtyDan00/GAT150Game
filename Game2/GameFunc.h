#pragma once

namespace nc
{
	class GameFunc
	{
	public:
		enum class eState
		{
			INIT,
			TITLE,
			START_GAME,
			GAME,
			GAME_WAIT,
			PLAYER_DEAD,
			GAME_OVER
		};

	public:
		bool Update(float dt);
	protected:
		eState m_state{ eState::TITLE };
		int m_lives{ 3 };
		int m_score{ 0 };
	};
}

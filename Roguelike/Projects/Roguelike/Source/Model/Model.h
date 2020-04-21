#pragma once

// Project Includes
#include <RL/Model/Component/Map/Map.h>
#include <RL/Model/Component/GameState.h>
#include <RL/Model/Component/Player.h>

namespace RL
{
	struct Model
	{
		GameState	game_state;
		Map			map;
		Player		player;

		Model()
			: game_state {GameState::Map}
			, map {}
			, player {}
		{
		}
	};
}
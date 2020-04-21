#pragma once

// Project Includes
#include <RL/Game/Event.h>

namespace RL
{
	struct State;
}

namespace RLConsole
{
	//-----------------------------------------------------------------------------------------------------
	// Player
	//-----------------------------------------------------------------------------------------------------

	void event_player_item_change(RL::EventPlayerItemChange event, const RL::State& state);
	void event_player_stat_change(RL::EventPlayerStatChange event, const RL::State& state);
}
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
	// Map
	//-----------------------------------------------------------------------------------------------------

	void event_map_move(RL::EventMapMove event, const RL::State& state);
}
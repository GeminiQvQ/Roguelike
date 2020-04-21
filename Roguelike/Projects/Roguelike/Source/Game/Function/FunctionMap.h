#pragma once

// Project Includes
#include <RL/Model/Component/Map/MapTypes.h>

namespace RL
{
	struct State;
}

namespace RL
{
	void map_move(RL::MapDirection direction, State& state);
	void map_generate(RL::MapCoordinates origin, State& state);
}
#pragma once

// Project Includes
#include <RL/Command/Command.h>
#include <RL/Core/TypeAlias.h>
#include <RL/Game/Event.h>
#include <RL/Model/Model.h>

// Stdlib Includes
#include <chrono>
#include <vector>

namespace RL
{
	struct State
	{
		Model				 model;
		std::vector<Command> commands;
		std::vector<Event>	 events;
		RNG					 rng;

		State()
			: model {}
			, commands {}
			, rng {(unsigned int)std::chrono::system_clock::now().time_since_epoch().count()}
		{
		}
	};
}
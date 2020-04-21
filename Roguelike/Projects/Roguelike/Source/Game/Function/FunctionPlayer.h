#pragma once

// Project Includes
#include <RL/Model/Component/Map/MapTypes.h>
#include <RL/Model/Component/Item.h>
#include <RL/Model/Component/Player.h>

namespace RL
{
	struct State;
}

namespace RL
{
	void player_add_item	(Item item, State& state);
	void player_remove_item	(Item item, State& state);
	void player_use_item	(Item item, State& state);
	void player_modify_stat	(PlayerStat stat, int value, State& state);
}
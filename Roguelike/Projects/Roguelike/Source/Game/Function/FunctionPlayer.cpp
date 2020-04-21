// Local Includes
#include <RL/Game/Function/FunctionPlayer.h>

// Project Includes
#include <RL/Game/State.h>

// Stdlib Includes
#include <cassert>

namespace RL
{
	void player_add_item(Item item, State& state)
	{
		state.model.player.items.emplace_back(item);
		state.events.emplace_back(EventPlayerItemChange{EventPlayerItemChange::Type::Add, item});
	}

	void player_remove_item(Item item, State& state)
	{
		const auto it = std::find(state.model.player.items.begin(), state.model.player.items.end(), item);
		assert(it != state.model.player.items.end());
		state.model.player.items.erase(it);
		state.events.emplace_back(EventPlayerItemChange{EventPlayerItemChange::Type::Remove, item});
	}

	void player_use_item(Item item, State& state)
	{
		const auto it = std::find(state.model.player.items.begin(), state.model.player.items.end(), item);
		assert(it != state.model.player.items.end());
		state.model.player.items.erase(it);
		state.events.emplace_back(EventPlayerItemChange{EventPlayerItemChange::Type::Use, item});
		std::visit([&state] (auto&& item) { item.use(state); }, item);
	}

	void player_modify_stat(PlayerStat stat, int value, State& state)
	{
		const auto stat_ptr = GX::EnumReflection<PlayerStat>::info(stat).stat_ptr;
		const auto value_old = state.model.player.*stat_ptr;
		state.model.player.*stat_ptr = value;
		state.events.emplace_back(EventPlayerStatChange{stat, value_old, value});
	}
}
// Local Includes
#include <RL/Game/Function/FunctionMap.h>

// Project Includes
#include <GXLib/StdExt/VariantIndex.h>
#include <RL/Game/Function/FunctionPlayer.h>
#include <RL/Game/State.h>
#include <RL/Model/Component/Map/MapNode.h>
#include <RL/Model/Utility/MapGenerator.h>

// Stdlib Includes
#include <cassert>

namespace RL
{
	void map_move(MapDirection direction, State& state)
	{
		const auto current_node_it = state.model.map.coordinates_to_nodes.find(state.model.player.location);
		assert(current_node_it != state.model.map.coordinates_to_nodes.end());
		const auto new_node = current_node_it->second->edges[direction];

		if (new_node == nullptr)
		{
			state.events.emplace_back(EventMapMove{direction, false});
			return;
		}

		if (new_node->is_ghost)
		{
			map_generate(new_node->coordinates, state);
		}

		new_node->is_explored = true;
		new_node->is_revealed = true;

		state.model.player.location = new_node->coordinates;

		state.events.emplace_back(EventMapMove{direction, true});

		switch (new_node->event.index())
		{
		case GX::VariantIndex<MNEItem, MapNodeEvent>():
			player_add_item(std::get<MNEItem>(new_node->event).item, state);
			new_node->event = MapNodeEvent{};
			break;
		}
	}

	void map_generate(MapCoordinates origin, State& state)
	{
		MapGenerateParameters parameters;
		parameters.origin = origin;
		generate_map(state.model.map, state.rng, parameters);

		state.events.emplace_back(EventMapGenerate{origin});
	}
}
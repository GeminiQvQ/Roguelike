#pragma once

// Project Includes
#include <GXLib/StdExt/EnumArray.h>
#include <RL/Model/Component/Map/MapTypes.h>
#include <RL/Model/Component/Item.h>

// Stdlib Includes
#include <variant>
#include <vector>

namespace RL
{
	struct MNEChest
	{
	};

	struct MNEItem
	{
		Item item;
	};

	using MapNodeEvent = std::variant
	<
		std::monostate,
		MNEChest,
		MNEItem
	>;

	struct MapNode
	{
		MapCoordinates							 coordinates;
		GX::EnumArray<MapDirection, MapNode*, 4> edges;
		MapNodeEvent							 event;
		bool									 is_explored = false;
		bool									 is_revealed = false;
		bool									 is_ghost = false;
	};
}
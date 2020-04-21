#pragma once

// Project Includes
#include <RL/Model/Component/Map/MapTypes.h>
#include <RL/Model/Component/Map/MapNode.h>

// Stdlib Includes
#include <memory>
#include <unordered_map>
#include <vector>

namespace RL
{
	struct Map
	{
		std::vector<std::unique_ptr<MapNode>>		 nodes;
		std::unordered_map<MapCoordinates, MapNode*> coordinates_to_nodes;
	};
}


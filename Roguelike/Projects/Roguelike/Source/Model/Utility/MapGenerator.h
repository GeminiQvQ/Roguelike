#pragma once

// Project Includes
#include <RL/Model/Component/Map/Map.h>
#include <RL/API.h>

namespace RL
{
	struct MapGenerateParameters
	{
		MapCoordinates	origin;

		unsigned int	min_nodes;
		unsigned int	max_nodes;

		unsigned int	min_edges;
		unsigned int	max_edges;

		unsigned int	min_ghosts;
		unsigned int	max_ghosts;

		RL_API MapGenerateParameters();
	};

	RL_API void generate_map(Map& map, RNG& rng, const MapGenerateParameters& parameters);
}
// Local Includes
#include <RL/Model/Utility/MapGenerator.h>

// Project Includes
#include <GXLib/StdExt/Algorithm.h>
#include <GXLib/StdExt/Random.h>

// Stdlib Includes
#include <cassert>

namespace RL
{
	MapNodeEvent generate_event(RNG& rng)
	{
		MapNodeEvent event;

		// TODO
		MNEItem item;
		item.item = ItemFood{rng};
		event = item;

		return event;
	}

	MapGenerateParameters::MapGenerateParameters()
		: origin {}
		, min_nodes {10}
		, max_nodes {20}
		, min_edges {0}
		, max_edges {4}
		, min_ghosts {1}
		, max_ghosts {5}
	{
	}

	void generate_map(Map& map, RNG& rng, const MapGenerateParameters& parameters)
	{
		std::vector<MapNode*> nodes_to_process;
		std::vector<MapNode*> nodes_to_reprocess;
		std::vector<MapNode*> nodes_processed;

		// Function for retrieving a node for given coordinates, and create one if it doesn't exist.
		auto get_node = [&map, &rng] (MapCoordinates coordinates)
		{
			const auto coordinates_to_nodes_it = map.coordinates_to_nodes.find(coordinates);
			if (coordinates_to_nodes_it != map.coordinates_to_nodes.end())
			{
				coordinates_to_nodes_it->second->is_ghost = false;
				return coordinates_to_nodes_it->second;
			}
			else
			{
				const bool is_starting_node = map.nodes.empty();
				
				map.nodes.emplace_back(std::make_unique<MapNode>());
				auto node = map.nodes.back().get();
				map.coordinates_to_nodes.insert(std::pair{coordinates, node});
				
				node->coordinates = coordinates;
				node->is_explored = is_starting_node;
				node->is_revealed = is_starting_node;

				if (!is_starting_node)
				{
					node->event = generate_event(rng);
				}

				return node;
			}
		};

		// Add initial node to the queue.
		nodes_to_process.emplace_back(get_node(parameters.origin));

		// Determine the number of nodes to generate.
		const unsigned int num_nodes_to_generate = GX::random(parameters.min_nodes, parameters.max_nodes, rng);
		unsigned int num_nodes_generated = 0;

		// Process until the required node count has been hit, or until it's no longer possible to generate more nodes.
		while (!nodes_to_process.empty() && num_nodes_generated < num_nodes_to_generate)
		{
			// Get the next node.
			auto node = nodes_to_process.front();
			nodes_to_process.erase(nodes_to_process.begin());

			// Randomize the direction order and determine the number of edges to generate.
			std::vector<size_t> direction_indices = { 0, 1, 2, 3 };
			std::shuffle(direction_indices.begin(), direction_indices.end(), rng);

			const unsigned int num_edges_to_generate = GX::random(parameters.min_edges, parameters.max_edges, rng);
			unsigned int num_edges_generated = 4 - (unsigned int)std::count(node->edges.begin(), node->edges.end(), nullptr);

			// Process until the required edge count has been hit, or until it's no longer possible to generate more edges.
			for (size_t i = 0; i < direction_indices.size() && num_edges_generated < num_edges_to_generate; ++i)
			{
				const auto& direction_info = GX::EnumReflection<MapDirection>::info(direction_indices[i]);

				// Bail if edge has already been generated.
				if (node->edges[direction_info.type] != nullptr)
				{
					continue;
				}

				const auto neighbour_coordinates = node->coordinates + direction_info.offset;
				const auto neighbour_coordinates_to_nodes_it = map.coordinates_to_nodes.find(neighbour_coordinates);

				// Bail if the neighbouring node exists and is not a ghost.
				if (neighbour_coordinates_to_nodes_it != map.coordinates_to_nodes.end() && !neighbour_coordinates_to_nodes_it->second->is_ghost)
				{
					continue;
				}

				// Create neighbouring node and link them up.
				auto neighbour_node = get_node(neighbour_coordinates);
				node->edges[direction_info.type] = neighbour_node;
				neighbour_node->edges[direction_info.inverse_type] = node;

				nodes_to_process.emplace_back(neighbour_node);
				++num_edges_generated;
			}

			// If this is a new node, generate a tile for it.
			if (!GX::contains(nodes_processed, node))
			{
				// TODO: Events.
				nodes_processed.emplace_back(node);
				++num_nodes_generated;
			}

			// If there are still remaining edges that can be made, mark it for reprocessing.
			if ((4 - std::count(node->edges.begin(), node->edges.end(), nullptr)) < parameters.max_edges)
			{
				nodes_to_reprocess.emplace_back(node);
			}
			
			// If we're out of nodes, and there are available nodes to reprocess, and we still want to make more nodes, keep trying.
			while (nodes_to_process.empty() && !nodes_to_reprocess.empty() && num_nodes_generated < num_nodes_to_generate)
			{
				// Find a random eligible node to reprocess.
				auto nodes_to_reprocess_it = nodes_to_reprocess.begin();
				std::advance(nodes_to_reprocess_it, GX::random(0, (int)nodes_to_reprocess.size() - 1, rng));
				auto node_to_reprocess = *nodes_to_reprocess_it;
				nodes_to_reprocess.erase(nodes_to_reprocess_it);

				for (const auto& direction_info : GX::EnumReflection<MapDirection>::info())
				{
					if (node_to_reprocess->edges[direction_info.type] == nullptr)
					{
						const auto neighbour_coordinates = node_to_reprocess->coordinates + direction_info.offset;
						const auto neighbour_coordinates_to_nodes_it = map.coordinates_to_nodes.find(neighbour_coordinates);

						// If the neighbouring space is empty, or it's a ghost, reprocess the node.
						if (neighbour_coordinates_to_nodes_it == map.coordinates_to_nodes.end() || neighbour_coordinates_to_nodes_it->second->is_ghost)
						{
							nodes_to_process.emplace_back(node_to_reprocess);
							break;
						}
					}
				}
			}
		}

		// Generate ghosts if requirements are met.
		if (nodes_processed.size() <= parameters.min_ghosts)
		{
			return;
		}

		// Randomize the nodes list in preparation for ghost generation.
		std::shuffle(nodes_processed.begin(), nodes_processed.end(), rng);

		// Determine the number of ghosts to generate.
		const unsigned int num_ghosts_to_generate = GX::random(parameters.min_ghosts, parameters.max_ghosts, rng);
		unsigned int num_ghosts_generated = 0;

		// Loop through the nodes until the node list is exhausted, or we've generated enough ghosts.
		for (auto node : nodes_processed)
		{
			if (num_ghosts_generated == num_ghosts_to_generate)
			{
				break;
			}

			// A ghost requires only one edge to be present.
			if ((4 - std::count(node->edges.begin(), node->edges.end(), nullptr)) == 1)
			{
				node->is_ghost = true;
				++num_ghosts_generated;
			}
		}
	}
}
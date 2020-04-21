// Local Includes
#include <RLConsole/Command/Spec/CommandLocal.h>

// Project Includes
#include <GXLib/StdExt/Console.h>
#include <RL/Game/State.h>
#include <RLConsole/Kernel/KernelState.h>

// Stdlib Includes
#include <iostream>

namespace RLConsole
{
	//-----------------------------------------------------------------------------------------------------
	// Local
	//-----------------------------------------------------------------------------------------------------

	void cmd_local_cls(const RL::State& /*state*/, KernelState& kernel_state)
	{
		kernel_state.cls = true;
	}

	//-----------------------------------------------------------------------------------------------------

	void cmd_local_quit(const RL::State& /*state*/, KernelState& kernel_state)
	{
		kernel_state.quit = true;
	}

	//-----------------------------------------------------------------------------------------------------

	void cmd_local_map(const RL::State& state, KernelState& /*kernel_state*/)
	{
		const auto x_min_it = std::min_element(state.model.map.nodes.begin(), state.model.map.nodes.end(), [] (auto&& a, auto&& b) { return (a->coordinates.first < b->coordinates.first); });
		const auto x_max_it = std::max_element(state.model.map.nodes.begin(), state.model.map.nodes.end(), [] (auto&& a, auto&& b) { return (a->coordinates.first < b->coordinates.first); });
		const auto y_min_it = std::min_element(state.model.map.nodes.begin(), state.model.map.nodes.end(), [] (auto&& a, auto&& b) { return (a->coordinates.second < b->coordinates.second); });
		const auto y_max_it = std::max_element(state.model.map.nodes.begin(), state.model.map.nodes.end(), [] (auto&& a, auto&& b) { return (a->coordinates.second < b->coordinates.second); });

		const auto x_min = (*x_min_it)->coordinates.first;
		const auto x_max = (*x_max_it)->coordinates.first;
		const auto y_min = (*y_min_it)->coordinates.second;
		const auto y_max = (*y_max_it)->coordinates.second;

		const auto x_num = x_max - x_min + 1;
		const auto y_num = y_max - y_min + 1;

		auto print_edge = [&state] (RL::MapCoordinates coordinates, RL::MapDirection direction, std::string_view forward, std::string_view backward, std::string_view both, std::string_view neither)
		{
			const auto coordinates_to_nodes_it = state.model.map.coordinates_to_nodes.find(coordinates);
			const auto coordinates_to_nodes_edge_it = state.model.map.coordinates_to_nodes.find(coordinates + GX::EnumReflection<RL::MapDirection>::info(direction).offset);

			if (coordinates_to_nodes_it != state.model.map.coordinates_to_nodes.end() && coordinates_to_nodes_edge_it != state.model.map.coordinates_to_nodes.end())
			{
				const auto node_valid = (!coordinates_to_nodes_it->second->is_ghost && coordinates_to_nodes_it->second->is_revealed && coordinates_to_nodes_it->second->edges[direction] != nullptr);
				const auto edge_node_valid = (!coordinates_to_nodes_edge_it->second->is_ghost && coordinates_to_nodes_edge_it->second->is_revealed && coordinates_to_nodes_edge_it->second->edges[ GX::EnumReflection<RL::MapDirection>::info(direction).inverse_type] != nullptr);

				if (node_valid && !edge_node_valid)
				{
					std::cout << forward;
				}
				else if (!node_valid && edge_node_valid)
				{
					std::cout << backward;
				}
				else if (node_valid && edge_node_valid)
				{
					std::cout << both;
				}
				else
				{
					std::cout << neither;
				}
			}
			else
			{
				std::cout << neither;
			}
		};

		auto print_node = [&state] (RL::MapCoordinates coordinates)
		{
			const auto coordinates_to_nodes_it = state.model.map.coordinates_to_nodes.find(coordinates);
			if (coordinates_to_nodes_it != state.model.map.coordinates_to_nodes.end() && !coordinates_to_nodes_it->second->is_ghost && coordinates_to_nodes_it->second->is_revealed)
			{
				const auto node = coordinates_to_nodes_it->second;

				char character = 'O';
				GX::ConsoleColorFG color = GX::ConsoleColorFG::White;

				if (!node->is_explored)
				{
					color = GX::ConsoleColorFG::Black;
				}
				
				if (state.model.player.location == coordinates)
				{
					character = '@';
					color = GX::ConsoleColorFG::Blue;
				}

				std::cout << color << GX::ConsoleWeightFG::Intense << character << GX::ConsoleColorFG::Default << GX::ConsoleWeightFG::Default;
			}
			else
			{
				std::cout << " ";
			}
		};

		auto print_edge_line = [x_min, x_num, y_max, &state, &print_edge] (int y_index)
		{
			for (int x_index = 0; x_index < x_num; ++x_index)
			{
				const auto coordinates = RL::MapCoordinates{x_min + x_index, y_max - y_index};
				print_edge(coordinates, RL::MapDirection::North, "  ^", "  v", "  |", "   ");
			}

			std::cout << std::endl;
		};

		auto print_node_line = [x_min, x_num, y_max, &state, &print_edge, &print_node] (int y_index)
		{
			for (int x_index = 0; x_index < x_num; ++x_index)
			{
				const auto coordinates = RL::MapCoordinates{x_min + x_index, y_max - y_index};
				print_edge(coordinates, RL::MapDirection::West, "<-", "->", "--", "  ");
				print_node(coordinates);
			}

			std::cout << std::endl;
		};

		for (int y_index = 0; y_index < y_num; ++y_index)
		{
			print_edge_line(y_index);
			print_node_line(y_index);
		}
	}
}
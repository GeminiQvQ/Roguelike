// Local Includes
#include <RLConsole/Event/Spec/EventMap.h>

// Stdlib Includes
#include <iostream>

namespace RLConsole
{
	//-----------------------------------------------------------------------------------------------------
	// Map
	//-----------------------------------------------------------------------------------------------------

	void event_map_move(RL::EventMapMove event, const RL::State& /*state*/)
	{
		std::cout << (event.ok ? "Moved " : "Unable to move ") << GX::EnumReflection<RL::MapDirection>::info(event.direction).type_name << "." << std::endl;
	}
}
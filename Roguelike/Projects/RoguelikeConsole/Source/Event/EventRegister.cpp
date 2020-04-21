// Local Includes
#include <RLConsole/Event/EventRegister.h>

// Project Includes
#include <GXLib/StdExt/VariantIndex.h>
#include <RLConsole/Event/Spec/EventMap.h>
#include <RLConsole/Event/Spec/EventPlayer.h>
#include <RLConsole/Event/EventHandler.h>

namespace RLConsole
{
	//-----------------------------------------------------------------------------------------------------
	// Register Wrapper
	//-----------------------------------------------------------------------------------------------------

	template <class EventT>
	void register_event(EventHandler& handler, void(*fn)(EventT, const RL::State&))
	{
		const auto event_fn = [fn] (RL::Event event, const RL::State& state)
		{
			fn(std::get<EventT>(event), state);
		};

		handler.register_event(GX::VariantIndex<EventT, RL::Event>(), event_fn);
	}

	//-----------------------------------------------------------------------------------------------------
	// Register
	//-----------------------------------------------------------------------------------------------------

	void register_events(EventHandler& handler)
	{
		// Map.
		register_event(handler, &event_map_move);

		// Player.
		register_event(handler, &event_player_item_change);
		register_event(handler, &event_player_stat_change);
	}
}
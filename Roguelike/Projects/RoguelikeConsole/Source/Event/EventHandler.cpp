// Local Includes
#include <RLConsole/Event/EventHandler.h>

// Project Includes
#include <RL/Game/State.h>
#include <RLConsole/Event/EventRegister.h>

// Stdlib Includes
#include <unordered_map>

namespace RLConsole
{
	//-----------------------------------------------------------------------------------------------------
	// Internal
	//-----------------------------------------------------------------------------------------------------

	struct EventHandler::Internal
	{
		std::unordered_map<RL::EventID, EventFunction> events;
	};

	//-----------------------------------------------------------------------------------------------------
	// Construction & Destruction
	//-----------------------------------------------------------------------------------------------------

	EventHandler::EventHandler()
		: m {std::make_unique<Internal>()}
	{
		register_events(*this);
	}

	EventHandler::~EventHandler()
	{
	}

	//-----------------------------------------------------------------------------------------------------
	// Events
	//-----------------------------------------------------------------------------------------------------

	void EventHandler::handle_events(RL::State& state)
	{
		while (!state.events.empty())
		{
			const auto event = state.events.front();
			state.events.erase(state.events.begin());

			const auto it = m->events.find(event.index());
			if (it != m->events.end())
			{
				it->second(event, state);
			}
		}
	}

	void EventHandler::register_event(RL::EventID id, EventFunction fn)
	{
		m->events.insert(std::pair{id, fn});
	}
}
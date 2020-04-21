#pragma once

// Project Includes
#include <RL/Game/Event.h>
#include <RLConsole/API.h>

// Stdlib Includes
#include <functional>

// Forward Declarations
namespace RL
{
	struct State;
}

namespace RLConsole
{
	struct KernelState;
}

namespace RLConsole
{
	//-----------------------------------------------------------------------------------------------------
	// Types
	//-----------------------------------------------------------------------------------------------------

	using EventFunction = std::function<void(RL::Event, const RL::State&)>;

	//-----------------------------------------------------------------------------------------------------
	// Event Handler
	//-----------------------------------------------------------------------------------------------------

	class EventHandler
	{
	public:
		// Construction & Destruction
				EventHandler	();
				~EventHandler	();

		// Events
		void	handle_events	(RL::State& state);
		void	register_event	(RL::EventID id, EventFunction fn);

	private:
		struct Internal;
		const UPtr<Internal> m;
	};
}
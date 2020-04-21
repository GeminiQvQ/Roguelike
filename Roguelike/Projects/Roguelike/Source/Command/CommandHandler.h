#pragma once

// Project Includes
#include <RL/Command/Command.h>
#include <RL/API.h>

// Stdlib Includes
#include <vector>

// Forward Declarations
namespace RL
{
	struct State;
}

namespace RL
{
	class RL_API CommandHandler
	{
	public:
		// Construction & Destruction
								CommandHandler		();
								~CommandHandler		();

		// Commands
		void					run_command			(const Command& command, State& state);
		std::vector<CommandID>	available_commands	(const State& state) const;
		void					register_command	(CommandID id, CommandFunction fn, CommandPredicate pred);

	private:
		struct Internal;
		const UPtr<Internal> m;
	};
}
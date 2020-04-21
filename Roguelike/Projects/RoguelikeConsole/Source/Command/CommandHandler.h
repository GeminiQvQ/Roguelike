#pragma once

// Project Includes
#include <RL/Command/Command.h>
#include <RLConsole/API.h>

// Stdlib Includes
#include <functional>
#include <string>
#include <vector>

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

	enum class CommandResult
	{
		Ok,
		InvalidCommand,
		InvalidArgumentFormat,
		InvalidArgumentCount
	};
	
	using CommandFunction = std::function<void(const RL::State&, KernelState&)>;
	using CommandBuilderFunction = std::function<bool(const RL::State&, RL::Command&, std::string_view)>;

	//-----------------------------------------------------------------------------------------------------
	// Command Handler
	//-----------------------------------------------------------------------------------------------------

	class CommandHandler
	{
	public:
		// Construction & Destruction
						CommandHandler		();
						~CommandHandler		();

		// Commands
		CommandResult	run_command			(std::string_view text, RL::State& state, KernelState& kernel_state);
		void			register_command	(std::string text, RL::Command cmd, const std::vector<CommandBuilderFunction>& cmd_builders);
		void			register_command	(std::string text, CommandFunction fn);

	private:
		struct Internal;
		const UPtr<Internal> m;
	};
}
// Local Includes
#include <RLConsole/Command/CommandHandler.h>

// Project Includes
#include <GXLib/StdExt/Algorithm.h>
#include <GXLib/StdExt/String.h>
#include <RL/Command/CommandHandler.h>
#include <RLConsole/Command/CommandRegister.h>

// Stdlib Includes
#include <unordered_map>

namespace RLConsole
{
	//-----------------------------------------------------------------------------------------------------
	// Internal
	//-----------------------------------------------------------------------------------------------------

	struct CommandHandler::Internal
	{
		struct Entry
		{
			RL::Command							cmd;
			std::vector<CommandBuilderFunction> cmd_builders;
			CommandFunction						cmd_fn;
		};

		RL::CommandHandler						rl_command_handler;
		std::unordered_map<std::string, Entry>	commands;
	};

	//-----------------------------------------------------------------------------------------------------
	// Construction & Destruction
	//-----------------------------------------------------------------------------------------------------

	CommandHandler::CommandHandler()
		: m {std::make_unique<Internal>()}
	{
		register_commands(*this);
	}

	CommandHandler::~CommandHandler()
	{
	}

	//-----------------------------------------------------------------------------------------------------
	// Commands
	//-----------------------------------------------------------------------------------------------------

	CommandResult CommandHandler::run_command(std::string_view text, RL::State& state, KernelState& kernel_state)
	{
		auto arguments = GX::split_string(text, ' ');

		if (arguments.empty())
		{
			return CommandResult::InvalidCommand;
		}

		const auto cmd_name = arguments.front();
		arguments.erase(arguments.begin());

		const auto cmd_it = std::find_if(m->commands.begin(), m->commands.end(), [cmd_name] (auto&& value)
		{
			return (value.first == cmd_name);
		});

		if (cmd_it == m->commands.end())
		{
			return CommandResult::InvalidCommand;
		}

		if (cmd_it->second.cmd.index() > 0)
		{
			if (!GX::contains(m->rl_command_handler.available_commands(state), cmd_it->second.cmd.index()))
			{
				return CommandResult::InvalidCommand;
			}

			if (arguments.size() != cmd_it->second.cmd_builders.size())
			{
				return CommandResult::InvalidArgumentCount;
			}

			auto cmd = cmd_it->second.cmd;

			bool arguments_valid = true;
			for (size_t i = 0; i < cmd_it->second.cmd_builders.size() && arguments_valid; ++i)
			{
				arguments_valid = cmd_it->second.cmd_builders[i](state, cmd, arguments[i]);
			}

			if (!arguments_valid)
			{
				return CommandResult::InvalidArgumentFormat;
			}

			m->rl_command_handler.run_command(cmd, state);
		}
		else
		{
			cmd_it->second.cmd_fn(state, kernel_state);
		}

		return CommandResult::Ok;
	}

	void CommandHandler::register_command(std::string text, RL::Command cmd, const std::vector<CommandBuilderFunction>& cmd_builders)
	{
		m->commands.insert(std::pair{std::move(text), Internal::Entry{std::move(cmd), std::move(cmd_builders), CommandFunction{}}});
	}

	void CommandHandler::register_command(std::string text, CommandFunction fn)
	{
		m->commands.insert(std::pair{std::move(text), Internal::Entry{RL::Command{}, {}, fn}});
	}
}
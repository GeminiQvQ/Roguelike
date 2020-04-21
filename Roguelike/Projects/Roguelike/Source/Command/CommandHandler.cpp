// Local Includes
#include <RL/Command/CommandHandler.h>

// Project Includes
#include <RL/Command/CommandRegister.h>

// Stdlib Includes
#include <cassert>

namespace RL
{
	//-----------------------------------------------------------------------------------------------------
	// Internal
	//-----------------------------------------------------------------------------------------------------

	struct CommandHandler::Internal
	{
		struct Entry
		{
			CommandFunction  fn;
			CommandPredicate pred;
		};

		std::unordered_map<CommandID, Entry, std::hash<size_t>> commands;
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

	void CommandHandler::run_command(const Command& command, State& state)
	{
		const auto it = m->commands.find(command.index());
		assert(it != m->commands.end());
		it->second.fn(command, state);
	}

	std::vector<CommandID> CommandHandler::available_commands(const State& state) const
	{
		std::vector<CommandID> result;

		for (auto&& [id, entry] : m->commands)
		{
			if (entry.pred(state))
			{
				result.emplace_back(id);
			}
		}

		return result;
	}

	void CommandHandler::register_command(CommandID id, CommandFunction fn, CommandPredicate pred)
	{
		m->commands.insert(std::pair{id, Internal::Entry{fn, pred}});
	}
}
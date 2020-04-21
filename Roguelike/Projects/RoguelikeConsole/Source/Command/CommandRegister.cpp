// Local Includes
#include <RLConsole/Command/CommandRegister.h>

// Project Includes
#include <RL/Game/State.h>
#include <RLConsole/Command/Spec/CommandLocal.h>
#include <RLConsole/Command/CommandHandler.h>

// Stdlib Includes
#include <sstream>

namespace RLConsole
{
	//-----------------------------------------------------------------------------------------------------
	// Command Argument Builders
	//-----------------------------------------------------------------------------------------------------

	template <class T, class CmdT>
	CommandBuilderFunction arg(T CmdT::* var)
	{
		return [var] (const RL::State& /*state*/, RL::Command& cmd, std::string_view str)
		{
			std::stringstream ss{str.data()};
			ss >> (std::get<CmdType>(cmd)).*var;
			return !ss.fail();
		};
	}

	//-----------------------------------------------------------------------------------------------------

	template <class T, class CmdT>
	CommandBuilderFunction arg_enum(T CmdT::* var)
	{
		return [var] (const RL::State& /*state*/, RL::Command& cmd, std::string_view str)
		{
			std::stringstream ss{str.data()};
			
			std::string type_name;
			ss >> type_name;

			const auto enum_info = GX::EnumReflection<T>::info(type_name);
			if (enum_info == nullptr)
			{
				return false;
			}

			(std::get<CmdT>(cmd)).*var = enum_info->type;

			return true;
		};
	}

	//-----------------------------------------------------------------------------------------------------

	template <class T, class CmdT>
	CommandBuilderFunction arg_item(T CmdT::* var)
	{
		return [var] (const RL::State& state, RL::Command& cmd, std::string_view str)
		{
			const auto it = std::find_if(state.model.player.items.begin(), state.model.player.items.end(), [str] (auto&& item)
			{
				return (std::visit([] (auto&& item) { return item.name(); }, item) == str);
			});

			if (it == state.model.player.items.end())
			{
				return false;
			}

			(std::get<CmdT>(cmd)).*var = *it;

			return true;
		};
	}

	//-----------------------------------------------------------------------------------------------------
	// Register
	//-----------------------------------------------------------------------------------------------------

	void register_commands(CommandHandler& handler)
	{
		// Local.
		handler.register_command("cls", &cmd_local_cls);
		handler.register_command("quit", &cmd_local_quit);
		handler.register_command("map", &cmd_local_map);

		// Map.
		handler.register_command("move", RL::CmdMapMove{}, {arg_enum(&RL::CmdMapMove::direction)});
		handler.register_command("use", RL::CmdMapUseItem{}, {arg_item(&RL::CmdMapUseItem::item)});
	}
}
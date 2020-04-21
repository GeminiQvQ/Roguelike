// Local Includes
#include <RL/Command/CommandRegister.h>

// Project Includes
#include <GXLib/StdExt/VariantIndex.h>
#include <RL/Command/Command.h>
#include <RL/Command/CommandHandler.h>
#include <RL/Game/Function/FunctionMap.h>
#include <RL/Game/Function/FunctionPlayer.h>
#include <RL/Game/State.h>

namespace RL
{
	//-----------------------------------------------------------------------------------------------------
	// Predicates
	//-----------------------------------------------------------------------------------------------------

	CommandPredicate pred_state(GameState game_state)
	{
		return [game_state] (const State& state)
		{
			return (state.model.game_state == game_state);
		};
	}

	//-----------------------------------------------------------------------------------------------------
	// Register Wrapper
	//-----------------------------------------------------------------------------------------------------

	template <class CmdT>
	void register_command(CommandHandler& handler, CommandPredicate pred, std::function<void(CmdT, State&)> fn)
	{
		auto cmd_fn = [fn] (Command cmd, State& state)
		{
			fn(std::get<CmdT>(cmd), state);
		};

		handler.register_command(GX::VariantIndex<CmdT, Command>(), cmd_fn, pred);
	}

	//-----------------------------------------------------------------------------------------------------
	// Register
	//-----------------------------------------------------------------------------------------------------

	void register_commands(CommandHandler& handler)
	{
		register_command<CmdMapMove>(handler, pred_state(GameState::Map), [] (auto&& cmd, State& state) { map_move(cmd.direction, state); });
		register_command<CmdMapUseItem>(handler, pred_state(GameState::Map), [] (auto&& cmd, State& state) { player_use_item(cmd.item, state); });
	}
}
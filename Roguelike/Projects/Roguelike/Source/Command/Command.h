#pragma once

// Project Includes
#include <RL/Model/Component/Map/MapTypes.h>
#include <RL/Model/Component/Item.h>

// Stdlib Includes
#include <functional>
#include <variant>

// Forward Declarations
namespace RL
{
	struct State;
}

namespace RL
{
	//-----------------------------------------------------------------------------------------------------
	// Command Types
	//-----------------------------------------------------------------------------------------------------

	struct CmdMapMove
	{
		MapDirection direction;
	};

	struct CmdMapUseItem
	{
		Item item;
	};

	//-----------------------------------------------------------------------------------------------------
	// Command
	//-----------------------------------------------------------------------------------------------------

	using Command = std::variant
	<
		std::monostate,
		CmdMapMove,
		CmdMapUseItem
	>;

	using CommandID = size_t;

	using CommandFunction = std::function<void(Command, State&)>;
	using CommandPredicate = std::function<bool(const State&)>;
}
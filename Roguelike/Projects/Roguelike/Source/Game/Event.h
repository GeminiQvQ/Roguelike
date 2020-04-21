#pragma once

// Project Includes
#include <RL/Model/Component/Map/MapTypes.h>
#include <RL/Model/Component/Item.h>
#include <RL/Model/Component/Player.h>

// Stdlib Includes
#include <variant>

namespace RL
{
	struct EventMapMove
	{
		RL::MapDirection direction;
		bool			 ok;
	};

	struct EventMapGenerate
	{
		RL::MapCoordinates origin;
	};

	struct EventPlayerItemChange
	{
		enum class Type
		{
			Add,
			Remove,
			Use
		};

		Type	 type;
		RL::Item item;
	};

	struct EventPlayerStatChange
	{
		PlayerStat stat;
		int		   value_old;
		int		   value;
	};

	using Event = std::variant
	<
		std::monostate,
		EventMapMove,
		EventMapGenerate,
		EventPlayerItemChange,
		EventPlayerStatChange
	>;

	using EventID = std::size_t;
}
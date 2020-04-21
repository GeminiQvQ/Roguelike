#pragma once

// Project Includes
#include <GXLib/Core/EnumReflection.h>
#include <RL/Model/Component/Map/MapTypes.h>
#include <RL/Model/Component/Item.h>
#include <RL/API.h>

// Stdlib Includes
#include <vector>

namespace RL
{
	struct Player
	{
		MapCoordinates		location;
		std::vector<Item>	items;

		int					hp;
		int					hp_max;
		int					hunger;
		int					hunger_max;
		int					damage;
		int					shield;

		RL_API Player();
	};

	enum class PlayerStat
	{
		HP,
		HPMax,
		Hunger,
		HungerMax,
		Damage,
		Shield
	};

	struct PlayerStatInfo : public GX::EnumReflectionInfo<PlayerStat>
	{
		int Player::* stat_ptr;
	};
}

DECL_ENUM_REFLECTION_INFO_EXPORT(RL::PlayerStat, RL::PlayerStatInfo, RL_API)
// Local Includes
#include <RL/Model/Component/Player.h>

//-----------------------------------------------------------------------------------------------------
// Enum Reflection
//-----------------------------------------------------------------------------------------------------

DEF_ENUM_REFLECTION_INFO(RL::PlayerStat, RL::PlayerStatInfo)
{
	{ RL::PlayerStat::HP,		 "hp",		   "HP",		 &RL::Player::hp		 },
	{ RL::PlayerStat::HPMax,	 "hp_max",	   "Max HP",	 &RL::Player::hp_max	 },
	{ RL::PlayerStat::Hunger,	 "hunger",	   "Hunger",	 &RL::Player::hunger	 },
	{ RL::PlayerStat::HungerMax, "hunger_max", "Max Hunger", &RL::Player::hunger_max },
	{ RL::PlayerStat::Damage,	 "damage",	   "Damage",	 &RL::Player::damage	 },
	{ RL::PlayerStat::Shield,	 "shield",	   "Shield",	 &RL::Player::shield	 }
};

namespace RL
{
	//-----------------------------------------------------------------------------------------------------
	// Player
	//-----------------------------------------------------------------------------------------------------

	Player::Player()
		: location {}
		, items {}
		, hp {15}
		, hp_max {15}
		, hunger {10}
		, hunger_max {10}
		, damage {2}
		, shield {0}
	{
	}
}
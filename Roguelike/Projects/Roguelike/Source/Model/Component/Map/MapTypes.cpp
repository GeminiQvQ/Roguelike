// Local Includes
#include <RL/Model/Component/Map/MapTypes.h>

DEF_ENUM_REFLECTION_INFO(RL::MapDirection, RL::MapDirectionInfo)
{
	{ RL::MapDirection::North, "north", "North", std::pair{ 0,  1}, RL::MapDirection::South },
	{ RL::MapDirection::East,  "east",  "East",  std::pair{ 1,  0}, RL::MapDirection::West  },
	{ RL::MapDirection::South, "south", "South", std::pair{ 0, -1}, RL::MapDirection::North },
	{ RL::MapDirection::West,  "west",  "West",  std::pair{-1,  0}, RL::MapDirection::East  }
};
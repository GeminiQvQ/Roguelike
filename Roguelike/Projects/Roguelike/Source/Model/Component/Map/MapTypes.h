#pragma once

// Project Includes
#include <GXLib/Core/EnumReflection.h>
#include <RL/API.h>

namespace RL
{
	//-----------------------------------------------------------------------------------------------------
	// Types
	//-----------------------------------------------------------------------------------------------------

	using MapCoordinates = std::pair<int, int>;

	enum class MapDirection
	{
		North,
		East,
		South,
		West,

		None
	};

	struct MapDirectionInfo : GX::EnumReflectionInfo<MapDirection>
	{
		MapCoordinates offset;
		MapDirection   inverse_type;
	};
}

namespace std
{
	//-----------------------------------------------------------------------------------------------------
	// Operators
	//-----------------------------------------------------------------------------------------------------

	RL::MapCoordinates	operator +	(RL::MapCoordinates lhs, RL::MapCoordinates rhs);
	RL::MapCoordinates	operator -	(RL::MapCoordinates lhs, RL::MapCoordinates rhs);
	RL::MapCoordinates& operator += (RL::MapCoordinates& lhs, RL::MapCoordinates rhs);
	RL::MapCoordinates& operator -= (RL::MapCoordinates& lhs, RL::MapCoordinates rhs);

	//-----------------------------------------------------------------------------------------------------
	// Hash
	//-----------------------------------------------------------------------------------------------------

	template <>
	struct hash<RL::MapCoordinates>
	{
		size_t operator () (RL::MapCoordinates v) const;
	};
}

// Enum Reflection
DECL_ENUM_REFLECTION_INFO_EXPORT(RL::MapDirection, RL::MapDirectionInfo, RL_API)

// Inline Includes
#include <RL/Model/Component/Map/MapTypes.inl>
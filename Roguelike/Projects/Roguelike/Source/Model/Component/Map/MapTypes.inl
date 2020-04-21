namespace std
{
	//-----------------------------------------------------------------------------------------------------
	// Operators
	//-----------------------------------------------------------------------------------------------------

	inline RL::MapCoordinates operator + (RL::MapCoordinates lhs, RL::MapCoordinates rhs)
	{
		return RL::MapCoordinates{lhs.first + rhs.first, lhs.second + rhs.second};
	}

	inline RL::MapCoordinates operator - (RL::MapCoordinates lhs, RL::MapCoordinates rhs)
	{
		return RL::MapCoordinates{lhs.first - rhs.first, lhs.second - rhs.second};
	}

	inline RL::MapCoordinates& operator += (RL::MapCoordinates& lhs, RL::MapCoordinates rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}

	inline RL::MapCoordinates& operator -= (RL::MapCoordinates& lhs, RL::MapCoordinates rhs)
	{
		lhs = lhs - rhs;
		return lhs;
	}

	//-----------------------------------------------------------------------------------------------------
	// Hash
	//-----------------------------------------------------------------------------------------------------

	inline size_t hash<RL::MapCoordinates>::operator()(RL::MapCoordinates v) const
	{
		return (v.first << 16) | v.second;
	}
}
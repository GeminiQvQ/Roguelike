#pragma once

// Project Includes
#include <RL/API.h>

// Stdlib Includes
#include <string>
#include <variant>

// Forward Declarations
namespace RL
{
	struct State;
}

namespace RL
{
	//-----------------------------------------------------------------------------------------------------
	// Items
	//-----------------------------------------------------------------------------------------------------

	class RL_API ItemNone
	{
	public:
		std::string name		() const;
		std::string description	() const;
		void		use			(State& state) const;
		bool		operator == (ItemNone rhs) const;
	};

	//-----------------------------------------------------------------------------------------------------

	class RL_API ItemFood
	{
	public:
					ItemFood	(RNG& rng);

		std::string name		() const;
		std::string description	() const;
		void		use			(State& state) const;
		bool		operator == (ItemFood rhs) const;

	private:
		int			m_value;
	};

	//-----------------------------------------------------------------------------------------------------
	// Item
	//-----------------------------------------------------------------------------------------------------

	using Item = std::variant
	<
		ItemNone,
		ItemFood
	>;
}
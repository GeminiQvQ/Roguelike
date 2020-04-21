// Local Includes
#include <RL/Model/Component/Item.h>

// Project Includes
#include <GXLib/StdExt/Random.h>
#include <RL/Game/Function/FunctionPlayer.h>
#include <RL/Game/State.h>

// Stdlib Includes
#include <sstream>

namespace RL
{
	//-----------------------------------------------------------------------------------------------------
	// None
	//-----------------------------------------------------------------------------------------------------

	std::string ItemNone::name() const
	{
		return std::string{};
	}

	std::string ItemNone::description() const
	{
		return std::string{};
	}

	void ItemNone::use(State& /*state*/) const
	{
	}

	bool ItemNone::operator==(ItemNone /*rhs*/) const
	{
		return true;
	}

	//-----------------------------------------------------------------------------------------------------
	// Food
	//-----------------------------------------------------------------------------------------------------

	ItemFood::ItemFood(RNG& rng)
		: m_value {GX::random(1, 4, rng)}
	{
	}

	std::string ItemFood::name() const
	{
		return "Food";
	}

	std::string ItemFood::description() const
	{
		return (std::stringstream{} << "Restores " << m_value << " hunger.").str();
	}

	void ItemFood::use(State& state) const
	{
		const int value = std::min(state.model.player.hunger + m_value, state.model.player.hunger_max);
		player_modify_stat(PlayerStat::Hunger, value, state);
	}

	bool ItemFood::operator==(ItemFood rhs) const
	{
		return (m_value == rhs.m_value);
	}
}
// Local Includes
#include <RLConsole/Event/Spec/EventPlayer.h>

// Project Includes
#include <RL/Model/Component/Player.h>

// Stdlib Includes
#include <iostream>

namespace RLConsole
{
	//-----------------------------------------------------------------------------------------------------
	// Player
	//-----------------------------------------------------------------------------------------------------

	void event_player_item_change(RL::EventPlayerItemChange event, const RL::State& /*state*/)
	{
		std::string action_text;
		switch (event.type)
		{
		case RL::EventPlayerItemChange::Type::Add: action_text = "Obtained"; break;
		case RL::EventPlayerItemChange::Type::Remove: action_text = "Lost"; break;
		case RL::EventPlayerItemChange::Type::Use: action_text = "Used"; break;
		}

		std::cout << action_text << " item: " << std::visit([] (auto&& item) { return item.name(); }, event.item) << "." << std::endl;
	}

	void event_player_stat_change(RL::EventPlayerStatChange event, const RL::State& /*state*/)
	{
		std::cout << GX::EnumReflection<RL::PlayerStat>::info(event.stat).display_name << " stat changed from " << event.value_old << " to " << event.value << "." << std::endl;
	}
}
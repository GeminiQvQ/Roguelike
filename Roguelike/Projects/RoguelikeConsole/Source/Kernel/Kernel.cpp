// Local Includes
#include <RLConsole/Kernel/Kernel.h>

// Project Includes
#include <GXLib/StdExt/Console.h>
#include <RL/Game/State.h>
#include <RL/Model/Utility/MapGenerator.h>
#include <RLConsole/Command/CommandHandler.h>
#include <RLConsole/Event/EventHandler.h>
#include <RLConsole/Kernel/KernelState.h>

// Stdlib Includes
#include <iostream>

namespace RLConsole
{
	//-----------------------------------------------------------------------------------------------------
	// Internal
	//-----------------------------------------------------------------------------------------------------

	struct Kernel::Internal
	{
		CommandHandler	command_handler;
		EventHandler	event_handler;
		RL::State		rl_state;
		bool			running;

		Internal()
			: command_handler {}
			, event_handler {}
			, rl_state {}
			, running {false}
		{
		}
	};

	//-----------------------------------------------------------------------------------------------------
	// Construction & Destruction
	//-----------------------------------------------------------------------------------------------------

	Kernel::Kernel()
		: m {std::make_unique<Internal>()}
	{
		RL::generate_map(m->rl_state.model.map, m->rl_state.rng, RL::MapGenerateParameters{});
	}

	Kernel::~Kernel()
	{
	}

	//-----------------------------------------------------------------------------------------------------
	// State
	//-----------------------------------------------------------------------------------------------------

	void Kernel::run()
	{
		m->running = true;
		
		while (m->running)
		{
			KernelState kernel_state;

			std::cout << GX::ConsoleWeightFG::Intense << ">> " << GX::ConsoleWeightFG::Default;

			std::string input;
			std::getline(std::cin, input);

			const auto result = m->command_handler.run_command(input, m->rl_state, kernel_state);

			switch (result)
			{
			case CommandResult::InvalidCommand:
				std::cout << "Invalid command." << std::endl;
				break;
			case CommandResult::InvalidArgumentFormat:
				std::cout << "Invalid argument format." << std::endl;
				break;
			case CommandResult::InvalidArgumentCount:
				std::cout << "Invalid argument count." << std::endl;
				break;
			}

			m->event_handler.handle_events(m->rl_state);

			if (kernel_state.cls)
			{
				system("cls");
				kernel_state.cls = false;
			}
			else
			{
				std::cout << std::endl;
			}

			m->running = !kernel_state.quit;
		}
	}
}
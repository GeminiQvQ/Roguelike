#pragma once

// Forward Declarations
namespace RL
{
	struct State;
}

namespace RLConsole
{
	struct KernelState;
}

namespace RLConsole
{
	//-----------------------------------------------------------------------------------------------------
	// Local
	//-----------------------------------------------------------------------------------------------------

	void cmd_local_cls	(const RL::State& state, KernelState& kernel_state);
	void cmd_local_quit	(const RL::State& state, KernelState& kernel_state);
	void cmd_local_map	(const RL::State& state, KernelState& kernel_state);
}
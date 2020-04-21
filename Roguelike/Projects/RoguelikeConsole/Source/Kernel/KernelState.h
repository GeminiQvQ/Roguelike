#pragma once

namespace RLConsole
{
	struct KernelState
	{
		bool cls;
		bool quit;

		KernelState()
			: cls {false}
			, quit {false}
		{
		}
	};
}
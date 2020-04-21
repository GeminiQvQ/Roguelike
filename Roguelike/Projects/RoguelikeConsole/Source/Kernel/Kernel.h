#pragma once

// Project Includes
#include <RLConsole/API.h>

// Stdlib Includes
#include <memory>

namespace RLConsole
{
	class Kernel
	{
	public:
		// Construction & Destruction
				Kernel	();
				~Kernel	();

		// Loop
		void	run		();

	private:
		struct Internal;
		const UPtr<Internal> m;
	};
}
#pragma once

namespace GX
{
	template <class Engine>
	typename Engine::result_type random(Engine& engine);

	template <class T, class Engine>
	T random(T min, T max, Engine& engine);
}

// Inline Includes
#include <GXLib/StdExt/Random.inl>
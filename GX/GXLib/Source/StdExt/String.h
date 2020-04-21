#pragma once

// Stdlib Includes
#include <string_view>
#include <vector>

namespace GX
{
	std::vector<std::string_view> split_string(std::string_view string, char delimiter);
}

// Inline Includes
#include <GXLib/StdExt/String.inl>
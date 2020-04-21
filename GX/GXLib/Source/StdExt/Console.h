#pragma once

// Project Includes
#include <GXLib/Core/EnumReflection.h>
#include <GXLib/API.h>

// Stdlib Includes
#include <iostream>

// Third-Party Includes
#ifdef _WIN32
#include <windows.h>
#endif

namespace GX
{
	//-----------------------------------------------------------------------------------------------------
	// Common Types
	//-----------------------------------------------------------------------------------------------------

	template <class T>
	struct ConsoleAttributeTypeTraits;

	template <class T>
	struct ConsoleAttributeTypeInfo : EnumReflectionInfo<T>
	{
		unsigned int value_win32;
	};

	//-----------------------------------------------------------------------------------------------------
	// Attributes
	//-----------------------------------------------------------------------------------------------------

	enum class ConsoleColorFG
	{
		Black,
		White,
		Red,
		Green,
		Blue,
		Yellow,
		Magenta,
		Cyan,

		Default = White
	};

	template <>
	struct ConsoleAttributeTypeTraits<ConsoleColorFG>
	{
		static constexpr unsigned int mask_win32 = 0b00000111;
	};

	//-----------------------------------------------------------------------------------------------------

	enum class ConsoleColorBG
	{
		Black,
		White,
		Red,
		Green,
		Blue,
		Yellow,
		Magenta,
		Cyan,

		Default = Black
	};

	template <>
	struct ConsoleAttributeTypeTraits<ConsoleColorBG>
	{
		static constexpr unsigned int mask_win32 = 0b01110000;
	};

	//-----------------------------------------------------------------------------------------------------

	enum class ConsoleWeightFG
	{
		Default,
		Intense
	};

	template <>
	struct ConsoleAttributeTypeTraits<ConsoleWeightFG>
	{
		static constexpr unsigned int mask_win32 = 0b00001000;
	};
	
	//-----------------------------------------------------------------------------------------------------

	enum class ConsoleWeightBG
	{
		Default,
		Intense
	};

	template <>
	struct ConsoleAttributeTypeTraits<ConsoleWeightBG>
	{
		static constexpr unsigned int mask_win32 = 0b10000000;
	};

	//-----------------------------------------------------------------------------------------------------
	// Stream Overloads
	//-----------------------------------------------------------------------------------------------------

	template <class CharT, class Traits, class ConsoleAttribute>
	std::enable_if_t<std::is_same_v<ConsoleAttribute, ConsoleColorFG> ||
					 std::is_same_v<ConsoleAttribute, ConsoleColorBG> ||
					 std::is_same_v<ConsoleAttribute, ConsoleWeightFG> ||
					 std::is_same_v<ConsoleAttribute, ConsoleWeightBG>,
					 std::basic_ostream<CharT, Traits>&>
	operator << (std::basic_ostream<CharT, Traits>& stream, ConsoleAttribute attribute)
	{
#ifdef _WIN32
		const auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO info {};
		GetConsoleScreenBufferInfo(handle, &info);
		const auto attributes = (info.wAttributes & ~ConsoleAttributeTypeTraits<ConsoleAttribute>::mask_win32) | EnumReflection<ConsoleAttribute>::info(attribute).value_win32;
		SetConsoleTextAttribute(handle, (WORD)attributes);
		return stream;
#else
		return stream;
#endif
	}
}

// Enum Reflection
DECL_ENUM_REFLECTION_INFO_EXPORT(GX::ConsoleColorFG, GX::ConsoleAttributeTypeInfo<GX::ConsoleColorFG>, GXLIBS_API)
DECL_ENUM_REFLECTION_INFO_EXPORT(GX::ConsoleColorBG, GX::ConsoleAttributeTypeInfo<GX::ConsoleColorBG>, GXLIBS_API)
DECL_ENUM_REFLECTION_INFO_EXPORT(GX::ConsoleWeightFG, GX::ConsoleAttributeTypeInfo<GX::ConsoleWeightFG>, GXLIBS_API)
DECL_ENUM_REFLECTION_INFO_EXPORT(GX::ConsoleWeightBG, GX::ConsoleAttributeTypeInfo<GX::ConsoleWeightBG>, GXLIBS_API)
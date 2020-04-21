// Local Includes
#include <GXLib/StdExt/Console.h>

//-----------------------------------------------------------------------------------------------------
// Enum Reflection
//-----------------------------------------------------------------------------------------------------

DEF_ENUM_REFLECTION_INFO(GX::ConsoleColorFG, GX::ConsoleAttributeTypeInfo<GX::ConsoleColorFG>)
{
	{ GX::ConsoleColorFG::Black,   "", "", 0x00 },
	{ GX::ConsoleColorFG::White,   "", "", 0x07 },
	{ GX::ConsoleColorFG::Red,	   "", "", 0x04 },
	{ GX::ConsoleColorFG::Green,   "", "", 0x02 },
	{ GX::ConsoleColorFG::Blue,	   "", "", 0x01 },
	{ GX::ConsoleColorFG::Yellow,  "", "", 0x06 },
	{ GX::ConsoleColorFG::Magenta, "", "", 0x05 },
	{ GX::ConsoleColorFG::Cyan,	   "", "", 0x03 }
};

DEF_ENUM_REFLECTION_INFO(GX::ConsoleColorBG, GX::ConsoleAttributeTypeInfo<GX::ConsoleColorBG>)
{
	{ GX::ConsoleColorBG::Black,   "", "", 0x00 },
	{ GX::ConsoleColorBG::White,   "", "", 0x70 },
	{ GX::ConsoleColorBG::Red,	   "", "", 0x40 },
	{ GX::ConsoleColorBG::Green,   "", "", 0x20 },
	{ GX::ConsoleColorBG::Blue,	   "", "", 0x10 },
	{ GX::ConsoleColorBG::Yellow,  "", "", 0x60 },
	{ GX::ConsoleColorBG::Magenta, "", "", 0x50 },
	{ GX::ConsoleColorBG::Cyan,	   "", "", 0x30 }
};

DEF_ENUM_REFLECTION_INFO(GX::ConsoleWeightFG, GX::ConsoleAttributeTypeInfo<GX::ConsoleWeightFG>)
{
	{ GX::ConsoleWeightFG::Default, "", "", 0x00 },
	{ GX::ConsoleWeightFG::Intense, "", "", 0x08 }
};

DEF_ENUM_REFLECTION_INFO(GX::ConsoleWeightBG, GX::ConsoleAttributeTypeInfo<GX::ConsoleWeightBG>)
{
	{ GX::ConsoleWeightBG::Default, "", "", 0x00 },
	{ GX::ConsoleWeightBG::Intense, "", "", 0x80 }
};
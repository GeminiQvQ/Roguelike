----------------------------------------------------------------------------------
-- Includes
----------------------------------------------------------------------------------

include "../../GX/GXLua/Premake.lua"

----------------------------------------------------------------------------------
-- Project
----------------------------------------------------------------------------------

project "RoguelikeConsole"
	GX.Premake.project("RoguelikeConsole", {GX.Premake.Kind.ExeStatic, GX.Premake.Kind.Exe})
	GX.Premake.import_gx("../../../../GX", {"GXLib"})
	GX.Premake.import("Roguelike", "../../Roguelike", "Include", "Lib", GX.Premake.Link.Dynamic)
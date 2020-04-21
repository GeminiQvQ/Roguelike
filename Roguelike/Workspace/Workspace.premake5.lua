----------------------------------------------------------------------------------
-- Includes
----------------------------------------------------------------------------------

include "../../GX/GXLua/Premake.lua"

----------------------------------------------------------------------------------
-- Workspace
----------------------------------------------------------------------------------

workspace "Roguelike"
	GX.Premake.workspace({GX.Premake.Kind.ExeStatic, GX.Premake.Kind.Static, GX.Premake.Kind.Exe, GX.Premake.Kind.DLL})
	GX.Premake.set_dll_output_dir("../../Projects/RoguelikeConsole/Bin")
	
	startproject "RoguelikeConsole"

	group "GX"
		project "GXLib"
		
	group ""
		project "Roguelike"
		project "RoguelikeConsole"
	
----------------------------------------------------------------------------------
-- Projects
----------------------------------------------------------------------------------
	
dofile("../../GX/GXLib/Platform/GXLib.premake5.lua")
dofile("../Projects/Roguelike/Platform/Roguelike.premake5.lua")
dofile("../Projects/RoguelikeConsole/Platform/RoguelikeConsole.premake5.lua")
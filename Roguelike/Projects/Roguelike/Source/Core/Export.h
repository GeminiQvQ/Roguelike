#pragma once

#if defined Roguelike_EXPORT_DLL
#define RL_API __declspec(dllexport)
#elif defined Roguelike_IMPORT_DLL
#define RL_API __declspec(dllimport)
#else
#define RL_API
#endif
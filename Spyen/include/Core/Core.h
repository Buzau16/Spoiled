#pragma once

#ifdef SPYEN_DLL_BUILD
#define SPYEN_API __declspec(dllexport)
#else
#define SPYEN_API __declspec(dllimport)
#endif


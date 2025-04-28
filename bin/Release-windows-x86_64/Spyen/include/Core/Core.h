#pragma once

#ifdef SPYEN_DLL_BUILD
#define SPYEN_API __declspec(dllexport)
#else
#define SPYEN_API __declspec(dllimport)
#endif

// Core log macros

#ifndef SPY_DISABLE_LOGGING
#define SPY_CORE_TRACE(...)    ::Spyen::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SPY_CORE_INFO(...)     ::Spyen::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SPY_CORE_WARN(...)     ::Spyen::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SPY_CORE_ERROR(...)    ::Spyen::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SPY_CORE_CRITICAL(...) ::Spyen::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define SPY_TRACE(...)			 ::Spyen::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SPY_INFO(...)			 ::Spyen::Log::GetClientLogger()->info(__VA_ARGS__)
#define SPY_WARN(...)			 ::Spyen::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SPY_ERROR(...)			 ::Spyen::Log::GetClientLogger()->error(__VA_ARGS__)
#define SPY_CRITICAL(...)		 ::Spyen::Log::GetClientLogger()->critical(__VA_ARGS__)
#else
#define SPY_CORE_TRACE(...)
#define SPY_CORE_INFO(...)
#define SPY_CORE_WARN(...)
#define SPY_CORE_ERROR(...)    
#define SPY_CORE_CRITICAL(...)

// Client log macros
#define SPY_TRACE(...)		
#define SPY_INFO(...)
#define SPY_WARN(...)	
#define SPY_ERROR(...)	
#define SPY_CRITICAL(...)

#endif

#ifdef SP_DEBUG
#define SPY_ASSERT(x, ...) { if(!(x)) { SPY_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define SPY_CORE_ASSERT(x, ...) { if(!(x)) { SPY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define SPY_ASSERT(x, ...)
#define SPY_CORE_ASSERT(x, ...)
#endif
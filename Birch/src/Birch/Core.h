#pragma once

#ifdef BC_PLATFORM_WINDOWS
	#ifdef BC_BUILD_DLL
		#define BIRCH_API __declspec(dllexport)
	#else 
		#define BIRCH_API __declspec(dllimport)
	#endif
#else
	#error Birch only support Windows!
#endif

#ifdef BC_ENABLE_ASSERTS
	#define BC_ASSERTS(x, ...) { if(!(x)) { BC_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define BC_CORE_ASSERTS(x, ...) { if(!(x)) { BC_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define BC_ASSERTS(x, ...)
	#define BC_CORE_ASSERTS(x, ...)
#endif

#define BIT(x) (1 << x)
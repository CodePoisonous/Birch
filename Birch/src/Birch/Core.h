#pragma once

#ifdef BC_PLATFORM_WINDOWS
#if BC_DYNAMIC_LINK
	#ifdef BC_BUILD_DLL
		#define BIRCH_API __declspec(dllexport)
	#else 
		#define BIRCH_API __declspec(dllimport)
	#endif
#else
	#define BIRCH_API
#endif
#else
	#error Birch only support Windows!
#endif

#ifdef BC_DEBUG
	#define BC_ENABLE_ASSERTS
#endif

#ifdef BC_ENABLE_ASSERTS
	#define BC_ASSERTS(x, ...) { if(!(x)) { BC_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define BC_CORE_ASSERTS(x, ...) { if(!(x)) { BC_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define BC_ASSERTS(x, ...)
	#define BC_CORE_ASSERTS(x, ...)
#endif

#define BIT(x) (1 << x)

#define BC_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
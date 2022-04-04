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

#define BIT(x) (1 << x)
#pragma once

#ifdef ZP_PLATFORM_WINDOWS
	#ifdef ZP_BUILD_DLL
		#define ZEPHYR_API __declspec(dllexport)
	#else
		#define ZEPHYR_API __declspec(dllimport)
	#endif
#else

#endif
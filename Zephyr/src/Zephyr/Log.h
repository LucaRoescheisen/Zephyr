#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
namespace Zephyr {

	class ZEPHYR_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger>  s_CoreLogger; 
		static std::shared_ptr < spdlog::logger> s_ClientLogger;
	};


}

//Core Log Macros
#define ZP_CORE_TRACE(...) ::Zephyr::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ZP_CORE_INFO(...)  ::Zephyr::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ZP_CORE_WARN(...)  ::Zephyr::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ZP_CORE_ERROR(...) ::Zephyr::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ZP_CORE_FATAL(...) ::Zephyr::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client Log Macros
#define ZP_CLIENT_TRACE(...) ::Zephyr::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ZP_CLIENT_INFO(...)  ::Zephyr::Log::GetClientLogger()->info(__VA_ARGS__)
#define ZP_CLIENT_WARN(...)  ::Zephyr::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ZP_CLIENT_ERROR(...) ::Zephyr::Log::GetClientLogger()->error(__VA_ARGS__)
#define ZP_CLIENT_FATAL(...) ::Zephyr::Log::GetClientLogger()->fatal(__VA_ARGS__)